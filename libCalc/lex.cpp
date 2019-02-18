/* Generated by re2c 1.1.1 on Mon Feb 18 15:09:19 2019 */
#line 1 "lex.re2c"
#line 4 "lex.cpp"
enum YYCONDTYPE {
	yycINITIAL,
	yyccomment,
	yyccomments,
};
#line 1 "lex.re2c"


int scan(scanner& s)
{
	for(;;)
	{
		if (s.cur >= s.end) {s.start++;return TOK_END;}
		s.start = s.cur;
		s.marker = nullptr;
		int c = yycINITIAL;
		
#line 22 "lex.cpp"
{
	wchar_t yych;
	unsigned int yyaccept = 0;
	if (c < 1) {
		goto yyc_INITIAL;
	} else {
		if (c < 2) {
			goto yyc_comment;
		} else {
			goto yyc_comments;
		}
	}
/* *********************************** */
yyc_INITIAL:
	yych = *s.cur;
	if (yych <= '+') {
		if (yych <= '\r') {
			if (yych <= '\t') {
				if (yych <= 0x0000) goto yy3;
				if (yych <= 0x0008) goto yy5;
				goto yy7;
			} else {
				if (yych <= '\n') goto yy10;
				if (yych <= '\f') goto yy5;
				goto yy12;
			}
		} else {
			if (yych <= '\'') {
				if (yych == ' ') goto yy7;
				goto yy5;
			} else {
				if (yych <= '(') goto yy13;
				if (yych <= ')') goto yy15;
				if (yych <= '*') goto yy17;
				goto yy19;
			}
		}
	} else {
		if (yych <= '9') {
			if (yych <= '.') {
				if (yych == '-') goto yy21;
				goto yy5;
			} else {
				if (yych <= '/') goto yy23;
				if (yych <= '0') goto yy25;
				goto yy27;
			}
		} else {
			if (yych <= ']') {
				if (yych <= '@') goto yy5;
				if (yych <= 'Z') goto yy29;
				goto yy5;
			} else {
				if (yych <= '^') goto yy32;
				if (yych <= '`') goto yy5;
				if (yych <= 'z') goto yy29;
				goto yy5;
			}
		}
	}
yy3:
	++s.cur;
#line 75 "lex.re2c"
	{ s.start++;return TOK_END; }
#line 87 "lex.cpp"
yy5:
	++s.cur;
yy6:
#line 78 "lex.re2c"
	{  return TOK_ERROR; }
#line 93 "lex.cpp"
yy7:
	yych = *++s.cur;
	if (yych == '\t') goto yy7;
	if (yych == ' ') goto yy7;
#line 27 "lex.re2c"
	{ continue; }
#line 100 "lex.cpp"
yy10:
	++s.cur;
#line 30 "lex.re2c"
	{ s.line++; s.begin = s.cur; continue; }
#line 105 "lex.cpp"
yy12:
	yych = *++s.cur;
	if (yych == '\n') goto yy10;
	goto yy6;
yy13:
	++s.cur;
#line 46 "lex.re2c"
	{ return TOK_LPAR; }
#line 114 "lex.cpp"
yy15:
	++s.cur;
#line 47 "lex.re2c"
	{ return TOK_RPAR; }
#line 119 "lex.cpp"
yy17:
	++s.cur;
#line 43 "lex.re2c"
	{ return TOK_TIMES; }
#line 124 "lex.cpp"
yy19:
	++s.cur;
#line 41 "lex.re2c"
	{ return TOK_PLUS; }
#line 129 "lex.cpp"
yy21:
	yyaccept = 0;
	yych = *(s.marker = ++s.cur);
	if (yych == '0') goto yy34;
yy22:
#line 42 "lex.re2c"
	{ return TOK_MINUS; }
#line 137 "lex.cpp"
yy23:
	yych = *++s.cur;
	if (yych == '*') goto yy36;
	if (yych == '/') goto yy38;
#line 44 "lex.re2c"
	{ return TOK_DIVIDE; }
#line 144 "lex.cpp"
yy25:
	yyaccept = 1;
	yych = *(s.marker = ++s.cur);
	if (yych <= '9') {
		if (yych == '.') goto yy40;
		if (yych >= '0') goto yy41;
	} else {
		if (yych <= 'E') {
			if (yych >= 'E') goto yy44;
		} else {
			if (yych == 'e') goto yy44;
		}
	}
yy26:
#line 64 "lex.re2c"
	{ return TOK_NUMBER; }
#line 161 "lex.cpp"
yy27:
	yyaccept = 1;
	yych = *(s.marker = ++s.cur);
	if (yych <= '9') {
		if (yych == '.') goto yy40;
		if (yych <= '/') goto yy26;
		goto yy27;
	} else {
		if (yych <= 'E') {
			if (yych <= 'D') goto yy26;
			goto yy44;
		} else {
			if (yych == 'e') goto yy44;
			goto yy26;
		}
	}
yy29:
	yych = *++s.cur;
	if (yych <= 'Z') {
		if (yych <= '/') goto yy31;
		if (yych <= '9') goto yy29;
		if (yych >= 'A') goto yy29;
	} else {
		if (yych <= '_') {
			if (yych >= '_') goto yy29;
		} else {
			if (yych <= '`') goto yy31;
			if (yych <= 'z') goto yy29;
		}
	}
yy31:
#line 72 "lex.re2c"
	{ return TOK_IDENTITY; }
#line 195 "lex.cpp"
yy32:
	++s.cur;
#line 45 "lex.re2c"
	{ return TOK_POW; }
#line 200 "lex.cpp"
yy34:
	yych = *++s.cur;
	if (yych <= '/') goto yy35;
	if (yych <= '9') goto yy41;
yy35:
	s.cur = s.marker;
	if (yyaccept <= 1) {
		if (yyaccept == 0) {
			goto yy22;
		} else {
			goto yy26;
		}
	} else {
		goto yy47;
	}
yy36:
	++s.cur;
	c = yyccomments;
	goto yyc_comments;
yy38:
	++s.cur;
	c = yyccomment;
	goto yyc_comment;
yy40:
	yych = *++s.cur;
	if (yych <= '/') goto yy35;
	if (yych <= '9') goto yy45;
	goto yy35;
yy41:
	yych = *++s.cur;
	if (yych <= '/') goto yy43;
	if (yych <= '9') goto yy41;
yy43:
#line 62 "lex.re2c"
	{ return TOK_ERROR; }
#line 236 "lex.cpp"
yy44:
	yych = *++s.cur;
	if (yych <= ',') {
		if (yych == '+') goto yy48;
		goto yy35;
	} else {
		if (yych <= '-') goto yy48;
		if (yych <= '/') goto yy35;
		if (yych <= '9') goto yy49;
		goto yy35;
	}
yy45:
	yyaccept = 2;
	yych = *(s.marker = ++s.cur);
	if (yych <= 'D') {
		if (yych <= '/') goto yy47;
		if (yych <= '9') goto yy45;
	} else {
		if (yych <= 'E') goto yy44;
		if (yych == 'e') goto yy44;
	}
yy47:
#line 68 "lex.re2c"
	{ return TOK_NUMBER; }
#line 261 "lex.cpp"
yy48:
	yych = *++s.cur;
	if (yych <= '/') goto yy35;
	if (yych >= ':') goto yy35;
yy49:
	yych = *++s.cur;
	if (yych <= '/') goto yy47;
	if (yych <= '9') goto yy49;
	goto yy47;
/* *********************************** */
yyc_comment:
	yych = *s.cur;
	if (yych <= '\n') {
		if (yych <= 0x0000) goto yy53;
		if (yych <= '\t') goto yy55;
		goto yy57;
	} else {
		if (yych == '\r') goto yy59;
		goto yy55;
	}
yy53:
	++s.cur;
#line 75 "lex.re2c"
	{ s.start++;return TOK_END; }
#line 286 "lex.cpp"
yy55:
	++s.cur;
yy56:
#line 81 "lex.re2c"
	{ goto yyc_comment; }
#line 292 "lex.cpp"
yy57:
	++s.cur;
#line 80 "lex.re2c"
	{ s.line++; s.begin = s.cur; continue; }
#line 297 "lex.cpp"
yy59:
	yych = *++s.cur;
	if (yych == '\n') goto yy57;
	goto yy56;
/* *********************************** */
yyc_comments:
	yych = *s.cur;
	if (yych <= '\f') {
		if (yych <= 0x0000) goto yy62;
		if (yych == '\n') goto yy66;
		goto yy64;
	} else {
		if (yych <= '\r') goto yy68;
		if (yych == '*') goto yy69;
		goto yy64;
	}
yy62:
	++s.cur;
#line 75 "lex.re2c"
	{ s.start++;return TOK_END; }
#line 318 "lex.cpp"
yy64:
	++s.cur;
yy65:
#line 85 "lex.re2c"
	{ goto yyc_comments; }
#line 324 "lex.cpp"
yy66:
	++s.cur;
#line 84 "lex.re2c"
	{ s.line++; s.begin = s.cur; goto yyc_comments; }
#line 329 "lex.cpp"
yy68:
	yych = *++s.cur;
	if (yych == '\n') goto yy66;
	goto yy65;
yy69:
	yych = *++s.cur;
	if (yych != '/') goto yy65;
	++s.cur;
#line 83 "lex.re2c"
	{ continue; }
#line 340 "lex.cpp"
}
#line 86 "lex.re2c"

	}
}
