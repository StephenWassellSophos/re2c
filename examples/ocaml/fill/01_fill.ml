(* Generated by re2c *)
#1 "ocaml/fill/01_fill.re"
(* re2ocaml $INPUT -o $OUTPUT *)

let bufsize = 4096

type state = {
    file: in_channel;
    buf: bytes;
    mutable cur: int;
    mutable mar: int;
    mutable tok: int;
    mutable lim: int;
    mutable eof: bool;
}

type status = Ok | Eof | LongLexeme

let fill(st: state) : status =
    if st.eof then Eof else

    (* Error: lexeme too long. In real life could reallocate a larger buffer. *)
    if st.tok < 1 then LongLexeme else (

    (* Shift buffer contents (discard everything up to the current token). *)
    Bytes.blit st.buf st.tok st.buf 0 (st.lim - st.tok);
    st.cur <- st.cur - st.tok;
    st.mar <- st.mar - st.tok;
    st.lim <- st.lim - st.tok;
    st.tok <- 0;

    (* Fill free space at the end of buffer with new data from file. *)
    let n = input st.file st.buf st.lim (bufsize - st.lim - 1) in (* -1 for sentinel *)
    st.lim <- st.lim + n;
    if n = 0 then
        st.eof <- true; (* end of file *)
        Bytes.set st.buf st.lim '\x00'; (* append sentinel *)

    Ok)


#43 "ocaml/fill/01_fill.ml"
let rec yy0 (st : state) (count : int) : int =
	let yych = Char.code (Bytes.get st.buf st.cur) in
	match yych with
		| 0x20 ->
			st.cur <- st.cur + 1;
			(yy3 [@tailcall]) st count
		| 0x27 ->
			st.cur <- st.cur + 1;
			(yy5 [@tailcall]) st count
		| _ ->
			if (st.cur >= st.lim) then (
				if (fill st = Ok) then (yy0 [@tailcall]) st count
				else (yy10 [@tailcall]) st count
			) else (
				st.cur <- st.cur + 1;
				(yy1 [@tailcall]) st count
			)

and yy1 (st : state) (count : int) : int =
	(yy2 [@tailcall]) st count

and yy2 (st : state) (count : int) : int =
#52 "ocaml/fill/01_fill.re"
	-1
#68 "ocaml/fill/01_fill.ml"

and yy3 (st : state) (count : int) : int =
	let yych = Char.code (Bytes.get st.buf st.cur) in
	match yych with
		| 0x20 ->
			st.cur <- st.cur + 1;
			(yy3 [@tailcall]) st count
		| _ ->
			if (st.cur >= st.lim) then (
				if (fill st = Ok) then (yy3 [@tailcall]) st count
				else (yy4 [@tailcall]) st count
			) else (
				(yy4 [@tailcall]) st count
			)

and yy4 (st : state) (count : int) : int =
#55 "ocaml/fill/01_fill.re"
	lex_loop st count
#87 "ocaml/fill/01_fill.ml"

and yy5 (st : state) (count : int) : int =
	st.mar <- st.cur;
	let yych = Char.code (Bytes.get st.buf st.cur) in
	if (yych <= 0x00) then (
		if (st.cur >= st.lim) then (
			if (fill st = Ok) then (yy5 [@tailcall]) st count
			else (yy2 [@tailcall]) st count
		) else (
			st.cur <- st.cur + 1;
			(yy6 [@tailcall]) st count
		)
	) else (
		(yy7 [@tailcall]) st count yych
	)

and yy6 (st : state) (count : int) : int =
	let yych = Char.code (Bytes.get st.buf st.cur) in
	(yy7 [@tailcall]) st count yych

and yy7 (st : state) (count : int) (yych : int) : int =
	match yych with
		| 0x27 ->
			st.cur <- st.cur + 1;
			(yy8 [@tailcall]) st count
		| 0x5C ->
			st.cur <- st.cur + 1;
			(yy9 [@tailcall]) st count
		| _ ->
			if (st.cur >= st.lim) then (
				if (fill st = Ok) then (yy6 [@tailcall]) st count
				else (yy11 [@tailcall]) st count
			) else (
				st.cur <- st.cur + 1;
				(yy6 [@tailcall]) st count
			)

and yy8 (st : state) (count : int) : int =
#54 "ocaml/fill/01_fill.re"
	lex_loop st (count + 1)
#128 "ocaml/fill/01_fill.ml"

and yy9 (st : state) (count : int) : int =
	let yych = Char.code (Bytes.get st.buf st.cur) in
	if (yych <= 0x00) then (
		if (st.cur >= st.lim) then (
			if (fill st = Ok) then (yy9 [@tailcall]) st count
			else (yy11 [@tailcall]) st count
		) else (
			st.cur <- st.cur + 1;
			(yy6 [@tailcall]) st count
		)
	) else (
		st.cur <- st.cur + 1;
		(yy6 [@tailcall]) st count
	)

and yy10 (st : state) (count : int) : int =
#53 "ocaml/fill/01_fill.re"
	count
#148 "ocaml/fill/01_fill.ml"

and yy11 (st : state) (count : int) : int =
	st.cur <- st.mar;
	(yy2 [@tailcall]) st count

and lex (st : state) (count : int) : int =
	(yy0 [@tailcall]) st count

#56 "ocaml/fill/01_fill.re"


and lex_loop st count =
    st.tok <- st.cur;
    lex st count

let main () =
    let fname = "input" in

    (* Prepare input file. *)
    Out_channel.with_open_bin fname
        (fun oc -> for i = 1 to bufsize do
            output_string oc "'qu\x00tes' 'are' 'fine: \\'' "
        done);

    (* Run lexer on the prepared file. *)
    In_channel.with_open_bin fname
        (fun ic ->
            let lim = bufsize - 1 in
            let st = {
                file = ic;
                buf = Bytes.create bufsize;
                cur = lim;
                mar = lim;
                tok = lim;
                lim = lim;
                eof = false;
            } in if not (lex_loop st 0 = 3 * bufsize) then
                raise (Failure "error"));

    (* Cleanup. *)
    Sys.remove fname

let _ = main ()
