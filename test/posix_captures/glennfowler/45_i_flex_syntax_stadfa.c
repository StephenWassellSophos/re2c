/* Generated by re2c */
// re2c $INPUT -o $OUTPUT -i --flex-syntax --stadfa

{
	YYCTYPE yych;
	if ((YYLIMIT - YYCURSOR) < 4) YYFILL(4);
	yych = *(YYMARKER = YYCURSOR);
	if (yych >= 0x01) goto yy3;
	yyt3 = yyt4 = yyt5 = yyt15 = NULL;
	yyt1 = yyt2 = yyt16 = YYCURSOR;
yy2:
	yynmatch = 4;
	yypmatch[0] = yyt1;
	yypmatch[2] = yyt2;
	yypmatch[3] = yyt16;
	yypmatch[4] = yyt3;
	yypmatch[5] = yyt4;
	yypmatch[6] = yyt5;
	yypmatch[7] = yyt15;
	yypmatch[1] = YYCURSOR;
	{}
yy3:
	yych = *++YYCURSOR;
	yyt8 = yyt13 = NULL;
	yyt6 = yyt7 = yyt9 = yyt15 = yyt16 = YYCURSOR - 1;
	if (yych >= 0x01) goto yy5;
	YYCURSOR = YYMARKER;
	yyt3 = yyt4 = yyt5 = yyt15 = NULL;
	yyt1 = yyt2 = yyt16 = YYCURSOR;
	goto yy2;
yy5:
	yych = *++YYCURSOR;
	yyt14 = yyt9;
	yyt12 = yyt8;
	yyt3 = yyt9;
	yyt11 = yyt7;
	yyt2 = yyt15;
	yyt10 = yyt6;
	yyt1 = yyt16;
	if (yych <= 0x00) {
		yyt5 = yyt15 = NULL;
		yyt4 = yyt16 = YYCURSOR;
		goto yy2;
	}
	yych = *++YYCURSOR;
	yyt5 = yyt9;
	yyt4 = yyt13;
	yyt8 = yyt14;
	yyt3 = yyt12;
	yyt7 = yyt15;
	yyt2 = yyt11;
	yyt6 = yyt16;
	yyt1 = yyt10;
	yyt9 = yyt13 = YYCURSOR - 1;
	if (yych <= 0x00) {
		yyt15 = yyt16 = YYCURSOR;
		goto yy2;
	}
yy7:
	++YYCURSOR;
	if (YYLIMIT <= YYCURSOR) YYFILL(1);
	yych = *YYCURSOR;
	yyt12 = yyt8;
	yyt3 = yyt9;
	yyt11 = yyt7;
	yyt2 = yyt15;
	yyt10 = yyt6;
	yyt1 = yyt16;
	yyt14 = yyt9;
	if (yych <= 0x00) {
		yyt5 = yyt15 = NULL;
		yyt4 = yyt16 = YYCURSOR;
		goto yy2;
	}
	++YYCURSOR;
	if (YYLIMIT <= YYCURSOR) YYFILL(1);
	yych = *YYCURSOR;
	yyt5 = yyt9;
	yyt4 = yyt13;
	yyt3 = yyt12;
	yyt2 = yyt11;
	yyt1 = yyt10;
	yyt9 = yyt13 = YYCURSOR - 1;
	yyt8 = yyt14;
	yyt7 = yyt15;
	yyt6 = yyt16;
	if (yych <= 0x00) {
		yyt15 = yyt16 = YYCURSOR;
		goto yy2;
	}
	goto yy7;
}

posix_captures/glennfowler/45_i_flex_syntax_stadfa.re:6:4: warning: rule matches empty string [-Wmatch-empty-string]
posix_captures/glennfowler/45_i_flex_syntax_stadfa.re:7:7: warning: rule matches empty string [-Wmatch-empty-string]
posix_captures/glennfowler/45_i_flex_syntax_stadfa.re:7:7: warning: unreachable rule (shadowed by rule at line 6) [-Wunreachable-rules]