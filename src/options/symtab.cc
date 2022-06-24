#include <stdlib.h>

#include "src/msg/location.h"
#include "src/msg/msg.h"
#include "src/options/symtab.h"

namespace re2c {

const AstNode* find_def(const symtab_t& symtab, const char* name, const loc_t& loc, Msg& msg) {
    symtab_t::const_iterator i = symtab.find(name);
    if (i == symtab.end()) {
        msg.error(loc, "undefined symbol '%s'", name);
        exit(1);
    }
    return i->second;
}

void add_named_def(
        symtab_t& symtab, const char* name, const AstNode* ast, const loc_t& loc, Msg& msg) {
    symtab_t::iterator i = symtab.find(name);
    if (i == symtab.end()) {
        // Ok, a new named definition, add it.
        symtab.insert(i, {name, ast});
    } else if (ast == i->second) {
        // Ok, an existing name with the same definition (note that we compare for pointer equality
        // of the AST, meaning that it is the same AST as before, not and identical one). Just skip
        // and do nothing (no error).
        //
        // This may happen if a name is defined in global scope and inherited by a `rules:re2c`
        // block that is followed by another block that uses the rules block with a `!use`
        // directive. At the time when symtab from the rules block is merged with the inherited one,
        // there is a collision on the global names that are present in both symtabs. It's harmless.
    } else {
        // Fail, as the same name is redefined to a different AST (don't bother checking if the ASTs
        // are identical, as there is no known valid use case for that).
        msg.error(loc, "name '%s' is already defined", name);
        exit(1);
    }
}

void merge_symtab(symtab_t& symtab, const symtab_t& other, const loc_t& loc, Msg& msg) {
    for (const auto& i : other) {
        add_named_def(symtab, i.first, i.second, loc, msg);
    }
}

} // namespace re2c
