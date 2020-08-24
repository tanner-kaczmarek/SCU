exists(V, node(_, V, _)).
exists(V, node(L, J, _)) :- V < J, exists(V, L).
exists(V, node(_, J, R)) :- V > J, exists(V, R).

insert(V, empty, node(empty, V, empty)).
insert(V, node(L, V, R), node(L, V, R)).
insert(V, node(L, J, R), node(L, J, X)) :- V > J, insert(V, R, X).
insert(V, node(L, J, R), node(X, J, R)) :- V < J, insert(V, L, X). 

foldr([], empty).
foldr([H|T], X) :- foldr(T, Y), insert(H, Y, X).

build(X, Z) :- reverse(X, Y), foldr(Y, Z).

inorder(empty, []).
inorder(node(L, K, R), Z) :- inorder(L, X), inorder(R, Y), append(X, [K|Y], Z).
