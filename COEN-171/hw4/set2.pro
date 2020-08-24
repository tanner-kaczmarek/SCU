% add1 does not work properly
 
add1(X, [], [X]).
add1(X, [X|T], [X|T]).
add1(X, [H|T], [H|L]) :- add1(X, T, L).
 
 
% add2 uses a red cut
 
add2(X, [], [X]).
add2(X, [X|T], [X|T]) :- !.
add2(X, [H|T], [H|L]) :- add2(X, T, L).
 
 
% add3 adds a green cut
 
add3(X, [], [X]) :- !.
add3(X, [X|T], [X|T]) :- !.
add3(X, [H|T], [H|L]) :- add3(X, T, L).
