% insert into a list in sorted order
 
insert1(X, [], [X]).
insert1(X, [H|T], [X,H|T]) :- X < H.
insert1(X, [H|T], [H|L]) :- X >= H, insert1(X, T, L).
 
 
% insert using a green cut
 
insert2(X, [], [X]).
insert2(X, [H|T], [X,H|T]) :- X < H, !.
insert2(X, [H|T], [H|L]) :- X >= H, insert2(X, T, L).
 
 
% insert using a red cut
 
insert3(X, [], [X]).
insert3(X, [H|T], [X,H|T]) :- X < H, !.
insert3(X, [H|T], [H|L]) :- insert3(X, T, L).
 
 
% insert using both a green cut and a red cut
 
insert4(X, [], [X]) :- !.
insert4(X, [H|T], [X,H|T]) :- X < H, !.
insert4(X, [H|T], [H|L]) :- insert4(X, T, L).
 
