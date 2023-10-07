/* Generated by re2c 3.0 */
#line 1 "../src/codegen/syntax_lexer.re"
#include <stdint.h>

#include "src/codegen/syntax.h"
#include "src/codegen/syntax_parser.h"
#include "src/msg/msg.h"
#include "src/util/string_utils.h"

#line 20 "../src/codegen/syntax_lexer.re"


namespace re2c {

int SyntaxConfig::lex_token(YYSTYPE* yylval) {
    const uint8_t* YYMARKER, *p;
    
#line 19 "src/codegen/syntax_lexer.cc"
const uint8_t* yyt1;
#line 26 "../src/codegen/syntax_lexer.re"


start:
    tok = cur;

#line 27 "src/codegen/syntax_lexer.cc"
{
	uint8_t yych;
	unsigned int yyaccept = 0;
	static const unsigned char yybm[] = {
		  0, 160, 160, 160, 160, 160, 160, 160, 
		160, 164,   0, 160, 160, 160, 160, 160, 
		160, 160, 160, 160, 160, 160, 160, 160, 
		160, 160, 160, 160, 160, 160, 160, 160, 
		164, 160, 128, 160, 160, 160, 160, 160, 
		160, 160, 160, 160, 160, 176, 160, 160, 
		184, 184, 184, 184, 184, 184, 184, 184, 
		184, 184, 160, 160, 160, 160, 160, 160, 
		160, 176, 176, 176, 176, 176, 176, 176, 
		176, 176, 176, 176, 176, 176, 176, 176, 
		176, 176, 176, 176, 176, 176, 176, 176, 
		176, 176, 176, 160, 192, 160, 160, 176, 
		160, 176, 176, 176, 176, 176, 176, 176, 
		176, 176, 176, 176, 176, 176, 176, 176, 
		176, 176, 176, 176, 176, 176, 176, 176, 
		176, 176, 176, 160, 160, 160, 160, 160, 
		160, 160, 160, 160, 160, 160, 160, 160, 
		160, 160, 160, 160, 160, 160, 160, 160, 
		160, 160, 160, 160, 160, 160, 160, 160, 
		160, 160, 160, 160, 160, 160, 160, 160, 
		160, 160, 160, 160, 160, 160, 160, 160, 
		160, 160, 160, 160, 160, 160, 160, 160, 
		160, 160, 160, 160, 160, 160, 160, 160, 
		160, 160, 160, 160, 160, 160, 160, 160, 
		160, 160, 160, 160, 160, 160, 160, 160, 
		160, 160, 160, 160, 160, 160, 160, 160, 
		160, 160, 160, 160, 160, 160, 160, 160, 
		160, 160, 160, 160, 160, 160, 160, 160, 
		160, 160, 160, 160, 160, 160, 160, 160, 
		160, 160, 160, 160, 160, 160, 160, 160, 
		160, 160, 160, 160, 160, 160, 160, 160, 
		160, 160, 160, 160, 160, 160, 160, 160, 
	};
	yych = *cur;
	if (yybm[0+yych] & 4) {
		goto yy4;
	}
	if (yych <= '=') {
		if (yych <= ')') {
			if (yych <= '\n') {
				if (yych <= 0x00) goto yy1;
				if (yych <= 0x08) goto yy2;
				goto yy5;
			} else {
				if (yych == '"') goto yy6;
				if (yych <= '\'') goto yy2;
				goto yy7;
			}
		} else {
			if (yych <= '/') {
				if (yych == '-') goto yy8;
				if (yych <= '.') goto yy2;
				goto yy9;
			} else {
				if (yych <= '9') goto yy10;
				if (yych == '<') goto yy2;
				goto yy7;
			}
		}
	} else {
		if (yych <= ']') {
			if (yych <= '@') {
				if (yych == '?') goto yy7;
				goto yy2;
			} else {
				if (yych <= 'Z') goto yy11;
				if (yych == '\\') goto yy2;
				goto yy7;
			}
		} else {
			if (yych <= 'z') {
				if (yych == '_') goto yy11;
				if (yych <= '`') goto yy2;
				goto yy11;
			} else {
				if (yych == '|') goto yy2;
				if (yych <= '}') goto yy7;
				goto yy2;
			}
		}
	}
yy1:
	++cur;
#line 31 "../src/codegen/syntax_lexer.re"
	{
        return YYEOF;
    }
#line 119 "src/codegen/syntax_lexer.cc"
yy2:
	++cur;
yy3:
#line 65 "../src/codegen/syntax_lexer.re"
	{
        msg.error(tok_loc(), "unexpected character: '%c'", cur[-1]);
        return YYerror;
    }
#line 128 "src/codegen/syntax_lexer.cc"
yy4:
	yych = *++cur;
	if (yybm[0+yych] & 4) {
		goto yy4;
	}
#line 39 "../src/codegen/syntax_lexer.re"
	{
        goto start;
    }
#line 138 "src/codegen/syntax_lexer.cc"
yy5:
	++cur;
#line 34 "../src/codegen/syntax_lexer.re"
	{
        ++loc.line;
        pos = cur;
        goto start;
    }
#line 147 "src/codegen/syntax_lexer.cc"
yy6:
	yyaccept = 0;
	yych = *(YYMARKER = ++cur);
	if (yych <= 0x00) goto yy3;
	if (yych == '\n') goto yy3;
	goto yy14;
yy7:
	++cur;
#line 62 "../src/codegen/syntax_lexer.re"
	{
        return cur[-1];
    }
#line 160 "src/codegen/syntax_lexer.cc"
yy8:
	yych = *++cur;
	if (yybm[0+yych] & 8) {
		goto yy10;
	}
	goto yy3;
yy9:
	yyaccept = 0;
	yych = *(YYMARKER = ++cur);
	if (yych == '/') goto yy19;
	goto yy3;
yy10:
	yych = *++cur;
	if (yybm[0+yych] & 8) {
		goto yy10;
	}
#line 50 "../src/codegen/syntax_lexer.re"
	{
        if (s_to_i32_unsafe(tok, cur, yylval->num)) {
            return TOKEN_NUMBER;
        } else {
            msg.error(tok_loc(), "configuration value overflow");
            return YYerror;
        }
    }
#line 186 "src/codegen/syntax_lexer.cc"
yy11:
	yyaccept = 1;
	yych = *(YYMARKER = ++cur);
	if (yybm[0+yych] & 16) {
		goto yy11;
	}
	if (yych <= 0x1F) {
		if (yych == '\t') {
			yyt1 = cur;
			goto yy20;
		}
	} else {
		if (yych <= ' ') {
			yyt1 = cur;
			goto yy20;
		}
		if (yych == '=') {
			yyt1 = cur;
			goto yy21;
		}
	}
yy12:
#line 46 "../src/codegen/syntax_lexer.re"
	{
        yylval->str = newcstr(tok, cur, alc);
        return TOKEN_NAME;
    }
#line 214 "src/codegen/syntax_lexer.cc"
yy13:
	yych = *++cur;
yy14:
	if (yybm[0+yych] & 32) {
		goto yy13;
	}
	if (yych <= '\n') goto yy15;
	if (yych <= '"') goto yy16;
	goto yy18;
yy15:
	cur = YYMARKER;
	if (yyaccept <= 1) {
		if (yyaccept == 0) {
			goto yy3;
		} else {
			goto yy12;
		}
	} else {
		goto yy17;
	}
yy16:
	++cur;
yy17:
#line 58 "../src/codegen/syntax_lexer.re"
	{
        yylval->str = newcstr(tok + 1, cur - 1, alc);
        return TOKEN_STRING;
    }
#line 243 "src/codegen/syntax_lexer.cc"
yy18:
	yych = *++cur;
	if (yybm[0+yych] & 32) {
		goto yy13;
	}
	if (yych <= '\n') goto yy15;
	if (yych <= '"') goto yy22;
	goto yy18;
yy19:
	yych = *++cur;
	if (yybm[0+yych] & 128) {
		goto yy19;
	}
	if (yych <= 0x00) goto yy15;
	goto yy5;
yy20:
	yych = *++cur;
	if (yych <= 0x1F) {
		if (yych == '\t') goto yy20;
		goto yy15;
	} else {
		if (yych <= ' ') goto yy20;
		if (yych != '=') goto yy15;
	}
yy21:
	++cur;
	p = yyt1;
#line 42 "../src/codegen/syntax_lexer.re"
	{
        yylval->str = newcstr(tok, p, alc);
        return TOKEN_CONFIG;
    }
#line 276 "src/codegen/syntax_lexer.cc"
yy22:
	yyaccept = 2;
	yych = *(YYMARKER = ++cur);
	if (yybm[0+yych] & 32) {
		goto yy13;
	}
	if (yych <= '\n') goto yy17;
	if (yych <= '"') goto yy16;
	goto yy18;
}
#line 69 "../src/codegen/syntax_lexer.re"


    return YYerror; // unreachable
}

} // namespace re2c
