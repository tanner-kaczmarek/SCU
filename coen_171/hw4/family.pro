parent(pam,bob).
parent(tom,bob).
parent(tom,liz).
parent(bob,ann).
parent(bob,pat).
parent(bob,jim).
 
male(tom).
male(bob).
male(jim).
%female(pam).
female(liz).
female(ann).
female(pat).
 
child(X,Y) :- parent(Y,X).
 
mother(X,Y) :- parent(X,Y), female(X).
 
grandparent(X,Z) :- parent(X,Y), parent(Y,Z).
 
sister(X,Y) :- parent(Z,X), parent(Z,Y), female(X).
 
predecessor(X,Z) :- parent(X,Z).
predecessor(X,Z) :- parent(X,Y), predecessor(Y,Z).
 
not(X) :- X, !, fail.
not(_).
 
sister2(X,Y) :- parent(Z,X), parent(Z,Y), female(X), not(X = Y).
 
