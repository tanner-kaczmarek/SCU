% add1 does not work properly
 
add1(X, L, L) :- member(X, L).
add1(X, L, [X|L]).
 
 
% add2 uses a red cut
 
add2(X, L, L) :- member(X, L), !.
add2(X, L, [X|L]).
 
 
% add3 uses \+ (which is still a red cut)
 
add3(X, L, L) :- member(X, L).
add3(X, L, [X|L]) :- \+ member(X, L).
 
 
% add4 also uses ! as a green cut
 
add4(X, L, L) :- member(X, L), !.
add4(X, L, [X|L]) :- \+ member(X, L).
