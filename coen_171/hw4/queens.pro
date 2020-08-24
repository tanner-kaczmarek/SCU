isSafe(_,[]).
isSafe(R1/C1,[R2/C2|T]) :-
	C1 =\= C2,
	C1-C2 =\= R1-R2,
	C1-C2 =\= R1 - R2,
	isSafe(R1/C1,T).

solve([],_).
solve([R/C|T,V):-
	solve(T,V),
	member(C,V),
	isSafe(R/C,T).

build(0,[]).
build(X, [X|T]) :- X > 0, Y is X-1, build(Y,T).

board(0, []).
board(X, [X/_|T]) :- X > 0, Y is X-1, board(Y,T).

queens(N,B) :- board(N,B), build(N,V), solve(B,V).
queens(B) :- queens(8,B). 