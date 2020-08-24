// FILE: node.cpp
//
//
//  COEN 79
//  --- Farokh Eskafi, COEN, SCU ---
//
//
// IMPLEMENTS: The functions of the node class and the
// linked list toolkit (see node1.h for documentation).
//
// INVARIANT for the node class:
//   The data of a node is stored in data_field
//   and the link to the next node is stored in link_field.

#include "node.h"
#include <cassert>    // Provides assert
#include <cstdlib>    // Provides NULL and size_t
#include <iostream>


using namespace std;

namespace coen79_lab6
{
    size_t list_length(const node* head_ptr)
    // Library facilities used: cstdlib
    {
	const node *cursor;
	size_t answer;

	answer = 0;
	for (cursor = head_ptr; cursor != NULL; cursor = cursor->link( ))
	    ++answer;

	return answer;
    }

    void list_head_insert(node*& head_ptr, const node::value_type& entry)
    {
    	head_ptr = new node(entry, head_ptr);
    }

    void list_insert(node* previous_ptr, const node::value_type& entry)
    {
    	node *insert_ptr;

    	insert_ptr = new node(entry, previous_ptr->link( ));
    	previous_ptr->set_link(insert_ptr);
    }

    node* list_search(node* head_ptr, const node::value_type& target)
    // Library facilities used: cstdlib
    {
    	node *cursor;

    	for (cursor = head_ptr; cursor != NULL; cursor = cursor->link( ))
    	    if (target == cursor->data( ))
        		return cursor;

    	return NULL;
    }

    const node* list_search(const node* head_ptr, const node::value_type& target)
    // Library facilities used: cstdlib
    {
    	const node *cursor;

    	for (cursor = head_ptr; cursor != NULL; cursor = cursor->link( ))
    	    if (target == cursor->data( ))
        		return cursor;

    	return NULL;
    }

    node* list_locate(node* head_ptr, size_t position)
    // Library facilities used: cassert, cstdlib
    {
    	node *cursor;
    	size_t i;

    	assert (0 < position);
    	cursor = head_ptr;
    	for (i = 1; (i < position) && (cursor != NULL); i++)
    	    cursor = cursor->link( );

    	return cursor;
    }

    const node* list_locate(const node* head_ptr, size_t position)
    // Library facilities used: cassert, cstdlib
    {
    	const node *cursor;
    	size_t i;

    	assert (0 < position);
    	cursor = head_ptr;
    	for (i = 1; (i < position) && (cursor != NULL); i++)
    	    cursor = cursor->link( );

    	return cursor;
    }

    void list_head_remove(node*& head_ptr)
    {
    	node *remove_ptr;

    	remove_ptr = head_ptr;
    	head_ptr = head_ptr->link( );
    	delete remove_ptr;
    }

    void list_remove(node* previous_ptr)
    {
    	node *remove_ptr;

    	remove_ptr = previous_ptr->link( );
    	previous_ptr->set_link( remove_ptr->link( ) );
    	delete remove_ptr;
    }

    void list_clear(node*& head_ptr)
    // Library facilities used: cstdlib
    {
    	while (head_ptr != NULL)
    	    list_head_remove(head_ptr);
    }

    void list_copy(const node* source_ptr, node*& head_ptr, node*& tail_ptr)
    // Library facilities used: cstdlib
    {
    	head_ptr = NULL;
    	tail_ptr = NULL;

    	// Handle the case of the empty list.
    	if (source_ptr == NULL)
    	    return;

    	// Make the head node for the newly created list, and put data in it.
    	list_head_insert(head_ptr, source_ptr->data( ));
    	tail_ptr = head_ptr;

    	// Copy the rest of the nodes one at a time, adding at the tail of new list.
    	source_ptr = source_ptr->link( );
    	while (source_ptr != NULL)
    	{
    	    list_insert(tail_ptr, source_ptr->data( ));
    	    tail_ptr = tail_ptr->link( );
    	    source_ptr = source_ptr->link( );
    	}
    }

    void list_piece(node* start_ptr, node* end_ptr, node*& head_ptr, node*& tail_ptr){
	head_ptr = NULL;
	tail_ptr = NULL;
	if (start_ptr == NULL || start_ptr == head_ptr) return;

	list_head_insert(head_ptr, start_ptr->data());
	tail_ptr = head_ptr;

	node* cursor = start_ptr;
	//cursor = cursor->link();
	while(cursor != end_ptr){
		list_insert(tail_ptr, cursor->data());
		tail_ptr = tail_ptr->link();
		cursor = cursor->link();
	}
    }

    size_t list_occurrences(node* head_ptr, const node::value_type& target){
	node* cursor = head_ptr;
	size_t counter = 0;
	while(cursor != NULL){
		if(cursor->data() == target) counter++;
		cursor = cursor->link();
	}
	return counter;
    }

    void list_insert_at(node*& head_ptr, const node::value_type& entry, size_t position){
	assert(position > 0 && position <= list_length(head_ptr)+1);
	size_t index = 1;
	node* cursor = head_ptr;
	//cursor= cursor->link();

	if(position == 1) list_head_insert(head_ptr, entry);
	else{ 
		for(index = 1; index + 1 < position && cursor != NULL; index++){
			cursor = cursor->link();
		}
		list_insert(cursor, entry);
	}
    }

    node::value_type list_remove_at(node*& head_ptr, size_t position){
	assert(position > 0 && position <= list_length(head_ptr));
	size_t index = 1;
	node* cursor = head_ptr;
	cursor = cursor->link();
	node* temp;
	
	if(position == 1){
		list_head_remove(head_ptr);
		return cursor->data();
	}	
	else{
		while(index + 2 < position){
			cursor = cursor->link();
			index++;
		}
		temp = cursor->link();
		list_remove(cursor);
		return temp->data();
	}
    }

    node* list_copy_segment(node* head_ptr, size_t start, size_t finish){
	assert(1 <= start && start <= finish && finish <= list_length(head_ptr));
	node* new_head_ptr = NULL;
	node* cursor = head_ptr;
	size_t i; 
	node* new_list;

	if(head_ptr == NULL) return NULL;
	
	for(i = 1; i < start; i++)
		cursor = cursor->link();
	
	new_list = new node(cursor->data());
	new_head_ptr = new_list;
	i = start;
	while(i < finish){
		cursor = cursor->link();
		new_list->set_link(new node(cursor->data()));;
		new_list = new_list->link();	
		i++;
	}
	return new_head_ptr;
    }

    void list_print (const node* head_ptr){
	const node* cursor = head_ptr;
	while(cursor != NULL){
		std::cout << cursor->data() << std::endl;
		cursor = cursor->link();
	}
    }

    void list_remove_dups(node* head_ptr){
	assert(head_ptr != NULL);
	node* temp = head_ptr;
	node* tracker;
	node* removed;
	while(temp != NULL){
		tracker = temp;
		while(tracker->link() != NULL){
			if(temp->data() == tracker->link()->data()){
				removed=tracker->link();
				tracker->set_link(removed->link());
				delete removed;
			}
			else 
				tracker = tracker->link();
		}
		temp = temp->link();
	}
    }

    node* list_detect_loop (node* head_ptr){
	//use Floyds's cycle finding algorith
	//have a fast and slow pointer that both point to head of the list
	//slow pointer will move one at a time but fast pointer will move two steps at a time
	//return null if the pointers did not meet
	//then move both one step at a time

	node* fast_p = head_ptr->link()->link();
	node* slow_p = head_ptr;
	while(fast_p != NULL && fast_p->link() != NULL && slow_p != fast_p){
		slow_p = slow_p->link();
		fast_p = fast_p->link()->link();	
	}

	if(fast_p == NULL || fast_p->link() == NULL)
		return NULL;

	while(slow_p != fast_p){
		fast_p = fast_p->link();
		slow_p = slow_p->link();
	}
	return slow_p;
    }
	    
    
}
