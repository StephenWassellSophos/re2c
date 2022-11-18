#include <ctype.h>
#include <stdio.h>
#include <time.h>
#include <iomanip>

#include "config.h"
#include "src/adfa/adfa.h"
#include "src/codegen/output.h"
#include "src/codegen/helpers.h"
#include "src/encoding/enc.h"
#include "src/msg/msg.h"
#include "src/msg/warn.h"
#include "src/options/opt.h"
#include "src/skeleton/skeleton.h"
#include "src/util/check.h"
#include "src/util/file_utils.h"
#include "src/util/string_utils.h"

namespace re2c {

static uint32_t write_converting_newlines(const std::string& str, FILE* f) {
    const char* s = str.c_str(), *e = s + str.length();
    uint32_t lines = 0;

    // In order to maintain consistency we convert all newlines to LF when writing output to file.
    // Some newlines originate in user-defined code (including semantic actions and code fragments
    // in configurations and directives), and some are generated by re2c itself.
    for (const char* p = s;; ++p) {
        size_t l = static_cast<size_t>(p - s);
        if (p == e) {
            fwrite(s, 1, l, f);
            break;
        } else if (*p == '\n') {
            ++lines;
            if (p > s && p[-1] == '\r') --l;
            fwrite(s, 1, l, f);
            s = p;
        }
    }

    return lines;
}

OutputBlock::OutputBlock(InputBlock kind, const std::string& name, const loc_t& loc)
    : kind(kind),
      name(name),
      loc(loc),
      code(nullptr),
      used_yyaccept(false),
      have_user_code(false),
      conds(),
      stags(),
      mtags(),
      opts(nullptr),
      dfas(),
      max_fill(1),
      max_nmatch(1),
      start_label(nullptr),
      fill_goto() {}

OutputBlock::~OutputBlock() {
    delete opts;
}

Output::Output(Msg& msg)
    : cblocks(),
      hblocks(),
      pblocks(&cblocks),
      tmpblocks(),
      label_counter(0),
      fill_label_counter(0),
      state_goto(false),
      cond_enum_autogen(true),
      warn_condition_order(true),
      need_header(false),
      done_mtag_defs(false),
      msg(msg),
      skeletons(),
      allocator(),
      scratchbuf(allocator),
      current_block(nullptr),
      total_opts(nullptr) {}

Output::~Output() {
    for (OutputBlock* b : cblocks) delete b;
    for (OutputBlock* b : hblocks) delete b;
}

void Output::header_mode(bool on) {
    pblocks = on ? &hblocks : &cblocks;
}

bool Output::in_header() const {
    return pblocks == &hblocks;
}

OutputBlock& Output::block() {
    return current_block == nullptr ? *pblocks->back() : *current_block;
}

void Output::set_current_block(OutputBlock* block) {
    current_block = block;
}

void Output::gen_raw(const uint8_t* s, const uint8_t* e, bool newline) {
    if (s != e && block().opts->target == Target::CODE) {
        // scan for non-whitespace characters
        bool& code = block().have_user_code;
        for (const uint8_t* p = s; !code && p < e; ++p) {
            code = !isspace(*p);
        }
        gen_stmt(code_raw(allocator, s, static_cast<size_t>(e - s)));
    }
    if (newline && e > s && e[-1] != '\n') {
        // Insert newline unless the block ends in a newline.
        gen_stmt(code_newline(allocator));
    }
}

void Output::gen_stmt(Code* stmt) {
    append(block().code, stmt);
}

Ret Output::new_block(Opt& opts, InputBlock kind, std::string name, const loc_t& loc) {
    // Prefix autogenerated names with a special symbol to avoid collision with user-defined names.
    // Embed line information in the autogenerated name to make it easier to correlate names with
    // source code.
    if (kind == InputBlock::USE) {
        // `use:re2c` blocks have autogenerated names that differ from the name of the `rules:re2c`
        // block that they are using, so the user cannot reference a `use:re2c` block in any way.
        // (They can easily achieve the same goal with the help of the `!use` directive in a normal
        // block.)
        name = "#line_" + to_string(loc.line) + "_block_use_" + name;
    } else if (name.empty()) {
        // Append block number, as the line may be non-unique (it is possible to have multiple
        // blocks on the same line, included files may define blocks at the same line, and line
        // directives may reset line number).
        name = "#line_" + to_string(loc.line) + "_block_" + to_string(pblocks->size());
    }

    // Check that the new block has a unique name.
    for (const OutputBlock* b : *pblocks) {
        if (b->name == name) {
            RET_FAIL(msg.error(loc,
                               "block named '%s' is already defined on line %u",
                               name.c_str(), b->loc.line));
        }
    }

    OutputBlock* block = new OutputBlock(kind, name, loc);
    pblocks->push_back(block);

    block->code = code_list(allocator);

    CHECK_RET(opts.snapshot(&block->opts));

    // start label hapens to be the only option that must be reset for each new block
    opts.reset_group_label_start();

    return Ret::OK;
}

Ret Output::emit_blocks(const std::string& fname, const CodegenCtxGlobal& globalctx) {
    const blocks_t& blocks = *globalctx.pblocks;

    FILE* file = nullptr, *temp = nullptr;
    std::string filename = fname, tempname = fname;

    if (filename.empty()) {
        filename = "<stdout>";
        file = stdout;
    } else if ((temp = temp_file(tempname))) {
        file = temp;
    } else if (!(file = fopen(filename.c_str(), "w"))) {
        RET_FAIL(error("cannot open output file %s", filename.c_str()));
    }
    filename = escape_backslashes(filename);

    // Second code generation pass: expand labels, combine/simplify statements, convert newlines,
    // write the generated code to a file.
    RenderContext rctx(msg, filename);
    for (const OutputBlock* b : blocks) {
        codegen_fixup(b);
        codegen_render(b, rctx);
    }
    write_converting_newlines(rctx.os.str(), file);

    fclose(file);
    if (temp && !overwrite_file(tempname.c_str(), fname.c_str())) {
        error("cannot rename or write temporary file %s to output file %s",
              tempname.c_str(),
              fname.c_str());
        remove(tempname.c_str());
        return Ret::FAIL;
    }
    return Ret::OK;
}

void fix_first_block_opts(const blocks_t& blocks) {
    // If the initial block contains only whitespace and no user code, then re2c options specified
    // in the first re2c block are also applied to the initial block.
    if (blocks.size() >= 2) {
        const OutputBlock* fst = blocks[0], *snd = blocks[1];
        if (!fst->have_user_code) {
            *const_cast<opt_t*>(fst->opts) = *snd->opts;
        }
    }
}

Ret Output::emit() {
    CHECK_RET(msg.warn.check());

    CodegenCtxGlobal ctx = {allocator,
                            scratchbuf,
                            msg,
                            total_opts,
                            cblocks,
                            hblocks,
                            /*pblocks*/ nullptr,
                            /*tmpblocks*/ blocks_t(),
                            warn_condition_order};

    // global options are last block's options
    const opt_t* opts = block().opts;

    // Emit header file.
    if (!opts->header_file.empty() || need_header) {
        ctx.pblocks = &hblocks;
        CHECK_RET(emit_blocks(opts->header_file, ctx));
    }

    // Emit output file.
    ctx.pblocks = &cblocks;
    return emit_blocks(opts->output_file, ctx);
}

void Output::gen_version_time() {
    const opt_t* opts = block().opts;

    scratchbuf.cstr(opts->lang == Lang::GO ? "// Code generated" : "/* Generated").cstr(" by re2c");
    if (opts->version) {
        scratchbuf.cstr(" " PACKAGE_VERSION);
    }
    if (opts->date) {
        scratchbuf.cstr(" on ");
        time_t now = time(nullptr);
        scratchbuf.stream().write(ctime(&now), 24);
    }
    scratchbuf.cstr(opts->lang == Lang::GO ? ", DO NOT EDIT." : " */");

    gen_stmt(code_textraw(allocator, scratchbuf.flush()));
}

Ret Output::gen_prolog(Opt& opts, const loc_t& loc) {
    header_mode(true);
    CHECK_RET(new_block(opts, InputBlock::GLOBAL, "", loc));
    gen_version_time();

    header_mode(false);
    CHECK_RET(new_block(opts, InputBlock::GLOBAL, "", loc));
    gen_version_time();
    gen_stmt(code_line_info_input(allocator, block().opts->lang, loc));

    if (block().opts->target == Target::SKELETON) {
        gen_stmt(emit_skeleton_prolog(*this));
    }

    return Ret::OK;
}

void Output::gen_epilog() {
    const opt_t* opts = block().opts;

    // For special targets (skeleton and .dot) merge header into the output file.
    if (opts->target != Target::CODE && need_header) {
        need_header = false;
        cblocks.insert(cblocks.end(), hblocks.begin(), hblocks.end());
        hblocks.clear();
    }

    if (opts->target == Target::SKELETON) {
        gen_stmt(emit_skeleton_epilog(*this));
    }
}

Scratchbuf& Scratchbuf::unchecked_label(const Label& l) {
    CHECK(l.index != Label::NONE);
    os << l.index;
    return *this;
}

Scratchbuf& Scratchbuf::label(const Label& l) {
    CHECK(l.used);
    return unchecked_label(l);
}

Scratchbuf& Scratchbuf::yybm_char(uint32_t u, const opt_t* opts, int width) {
    if (opts->bitmaps_hex) {
        print_hex(os, u, opts->encoding.cunit_size());
    } else {
        u32_width(u, width);
    }
    return *this;
}

Scratchbuf& Scratchbuf::u32_width(uint32_t u, int width) {
    os << std::setw(width);
    os << u;
    return *this;
}

Scratchbuf& Scratchbuf::exact_uint(size_t width) {
    if (width == sizeof(char)) {
        os << "unsigned char";
    } else if (width == sizeof(short)) {
        os << "unsigned short";
    } else if (width == sizeof(int)) {
        os << "unsigned int";
    } else if (width == sizeof(long)) {
        os << "unsigned long";
    } else {
        os << "uint" << width * 8 << "_t";
    }
    return *this;
}

const char* Scratchbuf::flush() {
    const size_t len = os.str().length();
    char* e = alc.alloct<char>(len + 1);
    memcpy(e, os.str().c_str(), len);
    e[len] = 0;
    os.str("");
    return e;
}

} // namespace re2c
