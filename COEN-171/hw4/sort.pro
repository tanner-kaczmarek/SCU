partition(_,[],[],[]).
partition(P,[H|T],X,[H|Y]) :- 
	H >= P, partition(P,T,X,Y).
partition(P,[H|T],[H|X],Y) :-
	H<P, partition(P,T,X,Y).

quicksort([],[]).
quicksort([H|T],X) :-
	partition(H,T,L,U), 
	quicksort(L,J),
	quicksort(U,K),
	append(J,[H|K],X). 
