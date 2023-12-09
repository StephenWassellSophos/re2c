/* Generated by re2c */
// re2c $INPUT -o $OUTPUT --input-encoding utf8 --loop-switch -i

// This example supports multiple input encodings: UTF-8 and UTF-32.
// Both lexers are generated from the same rules block, and the use
// blocks add only encoding-specific configurations.

#include <assert.h>
#include <stdint.h>



static int lex_utf8(const uint8_t *YYCURSOR)
{
    const uint8_t *YYMARKER;
    
{
	uint8_t yych;
	unsigned int yystate = 0;
	for (;;) {
		switch (yystate) {
			case 0:
				yych = *YYCURSOR;
				++YYCURSOR;
				switch (yych) {
					case 0xE2:
						yystate = 3;
						continue;
					default:
						yystate = 1;
						continue;
				}
			case 1:
				yystate = 2;
				continue;
			case 2: { return 1; }
			case 3:
				YYMARKER = YYCURSOR;
				yych = *YYCURSOR;
				switch (yych) {
					case 0x88:
						++YYCURSOR;
						yystate = 4;
						continue;
					default:
						yystate = 2;
						continue;
				}
			case 4:
				yych = *YYCURSOR;
				switch (yych) {
					case 0x80:
						++YYCURSOR;
						yystate = 6;
						continue;
					default:
						yystate = 5;
						continue;
				}
			case 5:
				YYCURSOR = YYMARKER;
				yystate = 2;
				continue;
			case 6:
				yych = *YYCURSOR;
				switch (yych) {
					case 'x':
						++YYCURSOR;
						yystate = 7;
						continue;
					default:
						yystate = 5;
						continue;
				}
			case 7:
				yych = *YYCURSOR;
				switch (yych) {
					case ' ':
						++YYCURSOR;
						yystate = 8;
						continue;
					default:
						yystate = 5;
						continue;
				}
			case 8:
				yych = *YYCURSOR;
				switch (yych) {
					case 0xE2:
						++YYCURSOR;
						yystate = 9;
						continue;
					default:
						yystate = 5;
						continue;
				}
			case 9:
				yych = *YYCURSOR;
				switch (yych) {
					case 0x88:
						++YYCURSOR;
						yystate = 10;
						continue;
					default:
						yystate = 5;
						continue;
				}
			case 10:
				yych = *YYCURSOR;
				switch (yych) {
					case 0x83:
						++YYCURSOR;
						yystate = 11;
						continue;
					default:
						yystate = 5;
						continue;
				}
			case 11:
				yych = *YYCURSOR;
				switch (yych) {
					case 'y':
						++YYCURSOR;
						yystate = 12;
						continue;
					default:
						yystate = 5;
						continue;
				}
			case 12: { return 0; }
		}
	}
}

}

static int lex_utf32(const uint32_t *YYCURSOR)
{
    const uint32_t *YYMARKER;
    
{
	uint32_t yych;
	unsigned int yystate = 0;
	for (;;) {
		switch (yystate) {
			case 0:
				yych = *YYCURSOR;
				++YYCURSOR;
				if (yych == 0x00002200) {
					yystate = 2;
					continue;
				}
				yystate = 1;
				continue;
			case 1: { return 1; }
			case 2:
				YYMARKER = YYCURSOR;
				yych = *YYCURSOR;
				if (yych != 'x') {
					yystate = 1;
					continue;
				}
				++YYCURSOR;
				yych = *YYCURSOR;
				if (yych == ' ') {
					++YYCURSOR;
					yystate = 4;
					continue;
				}
				yystate = 3;
				continue;
			case 3:
				YYCURSOR = YYMARKER;
				yystate = 1;
				continue;
			case 4:
				yych = *YYCURSOR;
				if (yych != 0x00002203) {
					yystate = 3;
					continue;
				}
				++YYCURSOR;
				yych = *YYCURSOR;
				if (yych != 'y') {
					yystate = 3;
					continue;
				}
				++YYCURSOR;
				{ return 0; }
		}
	}
}

}

int main()
{
    static const uint8_t s8[] = // UTF-8
        { 0xe2, 0x88, 0x80, 0x78, 0x20, 0xe2, 0x88, 0x83, 0x79 };

    static const uint32_t s32[] = // UTF32
        { 0x00002200, 0x00000078, 0x00000020, 0x00002203, 0x00000079 };

    assert(lex_utf8(s8) == 0);
    assert(lex_utf32(s32) == 0);
    return 0;
}

