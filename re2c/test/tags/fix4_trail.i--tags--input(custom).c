/* Generated by re2c */
#include <stddef.h>
#include <stdio.h>

static void lex(const char *YYCURSOR)
{
    const char *YYMARKER;
    const char *YYCTXMARKER;
    
{
	char yych;
	long yyt0p1;
	long yyt0p3;
	YYBACKUPCTX ();
	yych = YYPEEK ();
	switch (yych) {
	case '0':	goto yy4;
	default:	goto yy2;
	}
yy2:
	YYSKIP ();
yy3:
	{ printf("error\n"); return; }
yy4:
	YYSKIP ();
	YYBACKUP ();
	yych = YYPEEK ();
	switch (yych) {
	case '1':
		yyt0p1 = YYDIST();
		goto yy5;
	case '2':
		yyt0p1 = YYDIST();
		goto yy8;
	default:	goto yy3;
	}
yy5:
	YYSKIP ();
	yych = YYPEEK ();
	switch (yych) {
	case '1':	goto yy5;
	case '2':	goto yy8;
	default:	goto yy7;
	}
yy7:
	YYRESTORE ();
	goto yy3;
yy8:
	YYSKIP ();
	yych = YYPEEK ();
	switch (yych) {
	case '3':
		yyt0p3 = YYDIST();
		goto yy9;
	case '4':
		yyt0p3 = YYDIST();
		goto yy11;
	default:	goto yy7;
	}
yy9:
	YYSKIP ();
	yych = YYPEEK ();
	switch (yych) {
	case '3':	goto yy9;
	case '4':	goto yy11;
	default:	goto yy7;
	}
yy11:
	YYSKIP ();
	YYRESTORECTX (YYDIST() - 1);
	{
            printf("'%.*s', '%.*s', '%.*s', '%.*s', '%s'\n",
                YYTAG(yyt0p1) - YYCTXMARKER, YYCTXMARKER,
                YYTAG((yyt0p3 - 1)) - YYTAG(yyt0p1), YYTAG(yyt0p1),
                YYTAG(yyt0p3) - YYTAG((yyt0p3 - 1)), YYTAG((yyt0p3 - 1)),
                YYCURSOR - YYTAG(yyt0p3), YYTAG(yyt0p3),
                YYCURSOR);
                return;
        }
}

}

int main(int argc, char **argv)
{
    for (int i = 1; i < argc; ++i) {
        lex(argv[i]);
    }
    return 0;
}
