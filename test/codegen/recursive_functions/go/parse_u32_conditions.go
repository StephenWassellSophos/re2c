// Code generated by re2c, DO NOT EDIT.
//go:generate re2go -c $INPUT -o $OUTPUT --recursive-functions -i
package main

import "errors"

var (
	eSyntax   = errors.New("syntax error")
	eOverflow = errors.New("overflow error")
)

const (
	yycinit = 1
	yycbin = 11
	yycdec = 15
	yychex = 19
	yycoct = 25
)


const u32Limit uint64 = 1<<32

type State struct {
	str    string
	cur    int
	mar    int
	cond   uint
	result uint64
}

func add(st *State, base uint64, offset byte) {
	st.result = st.result * base + uint64(st.str[st.cur-1] - offset)
	if st.result >= u32Limit {
		st.result = u32Limit
	}
}


func yy1(st *State) (uint32, error) {
	yych := st.str[st.cur]
	st.cur += 1
	switch (yych) {
	case '0':
		return yy3(st)
	case '1','2','3','4','5','6','7','8','9':
		return yy5(st)
	default:
		return yy2(st)
	}
}

func yy2(st *State) (uint32, error) {
	{ return 0, eSyntax }
}

func yy3(st *State) (uint32, error) {
	st.mar = st.cur
	yych := st.str[st.cur]
	switch (yych) {
	case 'B':
		fallthrough
	case 'b':
		st.cur += 1
		return yy6(st)
	case 'X':
		fallthrough
	case 'x':
		st.cur += 1
		return yy8(st)
	default:
		return yy4(st)
	}
}

func yy4(st *State) (uint32, error) {
	st.cond = yycoct
	return yyfnoct(st)
}

func yy5(st *State) (uint32, error) {
	st.cur += -1
	st.cond = yycdec
	return yyfndec(st)
}

func yy6(st *State) (uint32, error) {
	yych := st.str[st.cur]
	switch (yych) {
	case '0','1':
		st.cur += 1
		return yy9(st)
	default:
		return yy7(st)
	}
}

func yy7(st *State) (uint32, error) {
	st.cur = st.mar
	return yy4(st)
}

func yy8(st *State) (uint32, error) {
	yych := st.str[st.cur]
	switch (yych) {
	case '0','1','2','3','4','5','6','7','8','9':
		fallthrough
	case 'A','B','C','D','E','F':
		fallthrough
	case 'a','b','c','d','e','f':
		st.cur += 1
		return yy10(st)
	default:
		return yy7(st)
	}
}

func yy9(st *State) (uint32, error) {
	st.cur += -1
	st.cond = yycbin
	return yyfnbin(st)
}

func yy10(st *State) (uint32, error) {
	st.cur += -1
	st.cond = yychex
	return yyfnhex(st)
}

func yyfninit(st *State) (uint32, error) {
	return yy1(st)
}

func yy11(st *State) (uint32, error) {
	yych := st.str[st.cur]
	st.cur += 1
	switch (yych) {
	case 0x00:
		return yy12(st)
	case '0','1':
		return yy14(st)
	default:
		return yy13(st)
	}
}

func yy12(st *State) (uint32, error) {
	{
		if st.result < u32Limit {
			return uint32(st.result), nil
		} else {
			return 0, eOverflow
		}
	}
}

func yy13(st *State) (uint32, error) {
	{ return 0, eSyntax }
}

func yy14(st *State) (uint32, error) {
	{ add(st, 2, '0');     return yyfnbin(st) }
}

func yyfnbin(st *State) (uint32, error) {
	return yy11(st)
}

func yy15(st *State) (uint32, error) {
	yych := st.str[st.cur]
	st.cur += 1
	switch (yych) {
	case 0x00:
		return yy16(st)
	case '0','1','2','3','4','5','6','7','8','9':
		return yy18(st)
	default:
		return yy17(st)
	}
}

func yy16(st *State) (uint32, error) {
	{
		if st.result < u32Limit {
			return uint32(st.result), nil
		} else {
			return 0, eOverflow
		}
	}
}

func yy17(st *State) (uint32, error) {
	{ return 0, eSyntax }
}

func yy18(st *State) (uint32, error) {
	{ add(st, 10, '0');    return yyfndec(st) }
}

func yyfndec(st *State) (uint32, error) {
	return yy15(st)
}

func yy19(st *State) (uint32, error) {
	yych := st.str[st.cur]
	st.cur += 1
	switch (yych) {
	case 0x00:
		return yy20(st)
	case '0','1','2','3','4','5','6','7','8','9':
		return yy22(st)
	case 'A','B','C','D','E','F':
		return yy23(st)
	case 'a','b','c','d','e','f':
		return yy24(st)
	default:
		return yy21(st)
	}
}

func yy20(st *State) (uint32, error) {
	{
		if st.result < u32Limit {
			return uint32(st.result), nil
		} else {
			return 0, eOverflow
		}
	}
}

func yy21(st *State) (uint32, error) {
	{ return 0, eSyntax }
}

func yy22(st *State) (uint32, error) {
	{ add(st, 16, '0');    return yyfnhex(st) }
}

func yy23(st *State) (uint32, error) {
	{ add(st, 16, 'A'-10); return yyfnhex(st) }
}

func yy24(st *State) (uint32, error) {
	{ add(st, 16, 'a'-10); return yyfnhex(st) }
}

func yyfnhex(st *State) (uint32, error) {
	return yy19(st)
}

func yy25(st *State) (uint32, error) {
	yych := st.str[st.cur]
	st.cur += 1
	switch (yych) {
	case 0x00:
		return yy26(st)
	case '0','1','2','3','4','5','6','7':
		return yy28(st)
	default:
		return yy27(st)
	}
}

func yy26(st *State) (uint32, error) {
	{
		if st.result < u32Limit {
			return uint32(st.result), nil
		} else {
			return 0, eOverflow
		}
	}
}

func yy27(st *State) (uint32, error) {
	{ return 0, eSyntax }
}

func yy28(st *State) (uint32, error) {
	{ add(st, 8, '0');     return yyfnoct(st) }
}

func yyfnoct(st *State) (uint32, error) {
	return yy25(st)
}

func yy0(st *State) (uint32, error) {
	switch (st.cond) {
	case yycinit:
		return yyfninit(st)
	case yycbin:
		return yyfnbin(st)
	case yycdec:
		return yyfndec(st)
	case yychex:
		return yyfnhex(st)
	case yycoct:
		return yyfnoct(st)
	default:
		panic("internal lexer error")
	}
}

func lex(st *State) (uint32, error) {
	return yy0(st)
}



func parse_u32(str string) (uint32, error) {
	st := &State{
		str:    str,
		cur:    0,
		mar:    0,
		cond:   yycinit,
		result: uint64(0),
	}
	return lex(st)
}

func main() {
	test := func(num uint32, str string, err error) {
		if n, e := parse_u32(str); !(n == num && e == err) {
			panic("error")
		}
	}
	test(1234567890, "1234567890\000", nil)
	test(13, "0b1101\000", nil)
	test(0x7fe, "0x007Fe\000", nil)
	test(0644, "0644\000", nil)
	test(0, "9999999999\000", eOverflow)
	test(0, "123??\000", eSyntax)
}
