const char* DEFAULT_SYNTAX_RUST =
    "api = [generic];\n"
    "api_style = [freeform, functions];\n"
    "jump_model = [loop_switch];\n"
    "target = [code, dot];\n"
    "\n"
    "computed_goto = unsupported;\n"
    "case_ranges = unsupported;\n"
    "constants = upper_case;\n"
    "char_literals = hexadecimal;\n"
    "semicolons = yes;\n"
    "abort_requires_include = no;\n"
    "implicit_bool_conversion = no;\n"
    "backtick_quoted_strings = no;\n"
    "standalone_single_quotes = yes;\n"
    "\n"
    "code:var =\n"
    "    // In Rust uninitialized variable is an error, but if the compiler is able to see\n"
    "    // that all paths overwrite the initial value, it warns about unused assignments.\n"
    "    (have_init? \"\" : topindent \"#[allow(unused_assignments)]\" nl)\n"
    "    topindent \"let mut \" name \" : \" type \" = \" (have_init? init : \"0\") \";\" nl;\n"
    "\n"
    "code:const = topindent \"const \" name \": \" type \" = \" init \";\" nl;\n"
    "\n"
    "// code:array\n"
    "\n"
    "code:type_int = \"isize\";\n"
    "code:type_uint = \"usize\";\n"
    "code:type_cond_enum = (storable_state? \"isize\" : \"usize\");\n"
    "// code:type_yybm\n"
    "// code:type_yytarget\n"
    "\n"
    "code:if_then_else =\n"
    "    topindent \"if \" then_cond \" {\" nl\n"
    "        indent [then_stmt: then_stmt] dedent\n"
    "    (have_else_part? topindent \"} else \" (have_else_cond? \"if \" else_cond \" \") \"{\" nl\n"
    "        indent [else_stmt: else_stmt] dedent)\n"
    "    topindent \"}\" nl;\n"
    "\n"
    "code:switch =\n"
    "    topindent \"match \" expr \" {\" nl\n"
    "        indent [case: case] dedent\n"
    "    topindent \"}\" nl;\n"
    "\n"
    "code:switch_cases =\n"
    "    [case{0:-2}: topindent case \" |\" nl]\n"
    "    [case{-1}:   topindent case \" => {\" nl\n"
    "        indent [stmt: stmt] dedent\n"
    "    topindent \"}\" nl];\n"
    "\n"
    "code:switch_cases_oneline =\n"
    "    [case{0:-2}: topindent case \" |\" nl]\n"
    "    [case{-1}:   topindent case \" => \" [stmt: stmt]];\n"
    "\n"
    "code:switch_case_range = [val{0}: val] (multival ? \" ..= \" [val{-1}: val]);\n"
    "\n"
    "code:switch_case_default = \"_\";\n"
    "\n"
    "code:loop =\n"
    "    topindent (have_label? label \": \") \"loop {\" nl\n"
    "        indent [stmt: stmt] dedent\n"
    "    topindent \"}\" nl;\n"
    "\n"
    "// In Rust `continue` statements have labels, use it to avoid ambiguity.\n"
    "code:loop_label = \"'yyl\";\n"
    "\n"
    "code:enum = [elem: topindent \"const \" elem \": \" type \" = \" init \";\" nl];\n"
    "\n"
    "code:fingerprint =\n"
    "    \"/* Generated by re2c\" (have_version? \" \" version) (have_date? \" on \" date) \" */\" nl;\n"
    "\n"
    "// No line directives in Rust: https://github.com/rust-lang/rfcs/issues/1862.\n"
    "//code:line_info\n"
    "\n"
    "code:abort = topindent \"panic!(\\\"internal lexer error\\\");\" nl;\n"
    "\n"
    "code:yypeek_expr = (unsafe? \"unsafe {\" peek \"}\" : peek) (api_style.functions ? \"()\");\n"
    ;
