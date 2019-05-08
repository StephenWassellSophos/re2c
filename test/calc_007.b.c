/* Generated by re2c */
#line 1 "calc_007.b.re"
/* re2c lesson 001_upn_calculator, calc_007, (c) M. Boerger 2006 - 2007 */
#line 8 "calc_007.b.re"


#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define DEBUG(stmt) stmt

int  stack[4];
int  depth = 0;

int push_num(const unsigned char *t, const unsigned char *l, int radix)
{
	int num = 0;
	
	if (depth >= sizeof(stack))
	{
		return 3;
	}

	--t;
	while(++t < l)
	{
		num = num * radix + (*t - (unsigned char)'0');
	}
	DEBUG(printf("Num: %d\n", num));

	stack[depth++] = num;
	return 0;
}

int stack_add()
{
	if (depth < 2) return 4;
	
	--depth;
	stack[depth-1] = stack[depth-1] + stack[depth];
	DEBUG(printf("+\n"));
	return 0;
}

int stack_sub()
{
	if (depth < 2) return 4;

	--depth;
	stack[depth-1] = stack[depth-1] - stack[depth];
	DEBUG(printf("+\n"));
	return 0;
}

int scan(char *s)
{
	unsigned char *p = (unsigned char*)s;
	unsigned char *t;
	int res = 0;
	
#define YYCTYPE         unsigned char
#define YYCURSOR        p
	
	while(!res)
	{
		t = p;

#line 70 "calc_007.b.c"
		{
			YYCTYPE yych;
			static const unsigned char yybm[] = {
				  0,   0,   0,   0,   0,   0,   0,   0, 
				  0,  64,   0,   0,   0,   0,   0,   0, 
				  0,   0,   0,   0,   0,   0,   0,   0, 
				  0,   0,   0,   0,   0,   0,   0,   0, 
				 64,   0,   0,   0,   0,   0,   0,   0, 
				  0,   0,   0,   0,   0,   0,   0,   0, 
				128, 128, 128, 128, 128, 128, 128, 128, 
				128, 128,   0,   0,   0,   0,   0,   0, 
				  0,   0,   0,   0,   0,   0,   0,   0, 
				  0,   0,   0,   0,   0,   0,   0,   0, 
				  0,   0,   0,   0,   0,   0,   0,   0, 
				  0,   0,   0,   0,   0,   0,   0,   0, 
				  0,   0,   0,   0,   0,   0,   0,   0, 
				  0,   0,   0,   0,   0,   0,   0,   0, 
				  0,   0,   0,   0,   0,   0,   0,   0, 
				  0,   0,   0,   0,   0,   0,   0,   0, 
				  0,   0,   0,   0,   0,   0,   0,   0, 
				  0,   0,   0,   0,   0,   0,   0,   0, 
				  0,   0,   0,   0,   0,   0,   0,   0, 
				  0,   0,   0,   0,   0,   0,   0,   0, 
				  0,   0,   0,   0,   0,   0,   0,   0, 
				  0,   0,   0,   0,   0,   0,   0,   0, 
				  0,   0,   0,   0,   0,   0,   0,   0, 
				  0,   0,   0,   0,   0,   0,   0,   0, 
				  0,   0,   0,   0,   0,   0,   0,   0, 
				  0,   0,   0,   0,   0,   0,   0,   0, 
				  0,   0,   0,   0,   0,   0,   0,   0, 
				  0,   0,   0,   0,   0,   0,   0,   0, 
				  0,   0,   0,   0,   0,   0,   0,   0, 
				  0,   0,   0,   0,   0,   0,   0,   0, 
				  0,   0,   0,   0,   0,   0,   0,   0, 
				  0,   0,   0,   0,   0,   0,   0,   0, 
			};
			yych = *YYCURSOR;
			if (yybm[0+yych] & 64) {
				goto yy6;
			}
			if (yych <= ',') {
				if (yych <= 0x00) goto yy2;
				if (yych == '+') goto yy9;
				goto yy4;
			} else {
				if (yych <= '/') {
					if (yych <= '-') goto yy11;
					goto yy4;
				} else {
					if (yych <= '0') goto yy13;
					if (yych <= '9') goto yy15;
					goto yy4;
				}
			}
yy2:
			++YYCURSOR;
#line 85 "calc_007.b.re"
			{ res = depth == 1 ? 0 : 2;	break; }
#line 129 "calc_007.b.c"
yy4:
			++YYCURSOR;
#line 86 "calc_007.b.re"
			{ res = 1; 					continue; }
#line 134 "calc_007.b.c"
yy6:
			yych = *++YYCURSOR;
			if (yybm[0+yych] & 64) {
				goto yy6;
			}
#line 80 "calc_007.b.re"
			{ continue; }
#line 142 "calc_007.b.c"
yy9:
			++YYCURSOR;
#line 83 "calc_007.b.re"
			{ res = stack_add();		continue; }
#line 147 "calc_007.b.c"
yy11:
			++YYCURSOR;
#line 84 "calc_007.b.re"
			{ res = stack_sub();		continue; }
#line 152 "calc_007.b.c"
yy13:
			yych = *++YYCURSOR;
			if (yych <= '/') goto yy14;
			if (yych <= '9') goto yy17;
yy14:
#line 82 "calc_007.b.re"
			{ res = push_num(t, p, 10); continue; }
#line 160 "calc_007.b.c"
yy15:
			yych = *++YYCURSOR;
			if (yybm[0+yych] & 128) {
				goto yy15;
			}
			goto yy14;
yy17:
			yych = *++YYCURSOR;
			if (yych <= '/') goto yy19;
			if (yych <= '9') goto yy17;
yy19:
#line 81 "calc_007.b.re"
			{ res = push_num(t, p, 8);	continue; }
#line 174 "calc_007.b.c"
		}
#line 87 "calc_007.b.re"

	}
	return res;
}

int main(int argc, char **argv)
{
	if (argc > 1)
	{
		char *inp;
		int res = 0, argp = 0, len;
		
		while(!res && ++argp < argc)
		{
			inp = strdup(argv[argp]);
			len = strlen(inp);
			if (inp[0] == '\"' && inp[len-1] == '\"')
			{
				inp[len - 1] = '\0';
				++inp;
			}
			res = scan(inp);
			free(inp);
		}
		switch(res)
		{
		case 0:
			printf("Result: %d\n", stack[0]);
			return 0;
		case 1:
			fprintf(stderr, "Illegal character in input.\n");
			return 1;
		case 2:
			fprintf(stderr, "Premature end of input.\n");
			return 2;
		case 3:
			fprintf(stderr, "Stack overflow.\n");
			return 3;
		case 4:
			fprintf(stderr, "Stack underflow.\n");
			return 4;
		}
	}
	else
	{
		fprintf(stderr, "%s <expr>\n", argv[0]);
		return 0;
	}
}