
datatype 'a tree = empty | node of 'a * 'a tree * 'a tree;

(*
fun insert(i, empty) = node(i, empty, empty)
   | insert(i, node(v, left, right)) =
	 if (i < v) then node(v, insert(i, left), right)
	 else if (i > v) then node(v, left, insert(i, right))	
         else node(v, left, right) 
*)

fun insert empty x = node(x,empty,empty)
   | insert (node(v, left, right)) x =
	if x < v then (node(v, insert left x, right))
	else (node(v,left, insert right x));

fun member empty x = false
   | member (node(v, left, right)) x =
	if (x < v) then member left x
	else if (x > v) then member right x
	else true;


(* build = fn : int list ->; tree
   Returns a tree that is result of inserting all integers in the given list *)

val build = foldl (fn (v,t) => insert t v) empty;


(* inorder = fn : tree ->; int list
   Returns a list that is contains all integers in the tree in order *)

fun inorder empty = []
  | inorder (node(d, l, r)) = inorder l @ d :: inorder r;


