//FILE: sequence.cpp
//CLASS IMPLEMENTED: sequence (see sequence.h for documentation)
//
//
//  COEN 79
//  --- Farokh Eskafi, COEN, SCU ---
//
//
//INVARIANT for the sequence class
//  1. The number of items in the sequence is stored in the member variable "many_nodes"
//
//  2. For an empty sequence, we do not care what is stored in any of data and head_ptr
//      and tail_ptr point to NULL; for a non-empty sequence, the items stored in the
//      sequence can be accessed using head_ptr and tail_ptr and we don't care what is
//      stored in the rest of the data.
//
//  3. If there is a current item, then it lies in *cursor; if there is no
//     current item, then cursor* equals NULL.
//
//  4. If there is a previous item, then it lies in precursor*.  If there is no previous
//       item, then precursor equals NULL.


#include <iostream>
#include <algorithm> //provides copy function
#include <cassert> //for assert function
#include "sequence.h" //header file for class
#include "node.h" // provides node class

using namespace std; //For copy function

namespace coen79_lab6
{
    // Default private member variable initialization function.
    void sequence::init()
    {
        //Initializing pointers to NULL
        head_ptr = NULL;
        tail_ptr = NULL;
        cursor = NULL;
        precursor = NULL;
        //Initializiing many_nodes (or our counter) to 0
        many_nodes = 0;
    }

    //CONSTRUCTOR IMPLEMENTATION for default constructor
    sequence :: sequence()
    {
        init();
    }

    //Copy Constructor
    sequence :: sequence(const sequence& source)
    {
        init();
        *this = source;
    }

   //Destructor
   sequence::~sequence(){
	list_clear(head_ptr);
	many_nodes = 0;
   }


	//MODIFCATION MEMBER FUNCTIONS
	void sequence::start(){
		this->cursor = head_ptr;
		this->precursor = head_ptr;
	}

	void sequence::end(){
		while(precursor->link() != tail_ptr)
			precursor = precursor->link();
		cursor = tail_ptr;
	}

	void sequence::advance(){
		if(is_item()){
			if(cursor == tail_ptr){
				precursor = tail_ptr;
				cursor = NULL;
			}
			else{
				precursor = cursor;
				cursor = cursor->link();
			}
		}
	}

	//inserting before current item
	void sequence::insert(const node::value_type& entry){
		//Empty insert becasue:
		//1. There is not a current value so put it in the front
		//2. The sequence is empty
		if(!is_item()){
			if(head_ptr == NULL){
				list_head_insert(head_ptr, entry);
				cursor = head_ptr;
				precursor = NULL;
				tail_ptr = NULL;
			}
			else {
				list_head_insert(head_ptr, entry);
				cursor = head_ptr;
				precursor = NULL;
			}
		}
		//NON-NULL because:
		//1. somewhere in the list between the beginning of the list and the end
		//2. When precursor == NULL
		else{
			if(precursor != NULL){
				list_insert(precursor, entry);
				cursor = precursor->link();
			}
			if(precursor == NULL){
				list_head_insert(head_ptr, entry);
				cursor = head_ptr;
			}	
		}
		++many_nodes;
	}

	//attaching after current item
	void sequence::attach(const value_type& entry){
		//Empty attach because:
		//1. There is not a current value so put it in the front
		//2. The sequence is empty
		if(!is_item()){
			if(head_ptr == NULL){
				list_head_insert(head_ptr, entry);
				cursor = head_ptr;
				precursor = NULL;
				tail_ptr = NULL;
			}
			else{
				//list_insert(tail_ptr, entry);
				cursor = tail_ptr;
				//tail_ptr = tail_ptr->link();
				
			}
		}
		//NON-NULL because:
		//1. Somewheere in the list between the beginning of the list and the end
		//2. When precursor == NULL
		else{
			list_insert(cursor, entry);
			precursor = cursor;
			if(cursor == tail_ptr)
				 tail_ptr = cursor->link();
			cursor = cursor->link();
		}
		many_nodes++;
	}

	void sequence::operator =(const sequence& source){
		if(head_ptr != NULL){
			list_clear(head_ptr);
			head_ptr = NULL;
			tail_ptr = NULL;
			cursor = NULL;
			precursor = NULL;
			many_nodes = 0;
		}
		if(source.head_ptr == NULL) return;
		node* tracker= source.head_ptr;
		node* temp = NULL;
		//need to check for precursor and cursor while tracking
		while(tracker!= NULL){
			if(head_ptr == NULL){
				temp = new node(source.head_ptr->data());
				head_ptr = temp;
			}
			else{
				temp->set_link(new node(tracker->data()));
				temp = temp->link();
			}
			if(tracker == source.precursor)
				precursor = temp;
			else if(tracker == source.cursor)
				cursor = temp;
			tracker = tracker->link();
		}
		tail_ptr = tracker;
		many_nodes = source.many_nodes;
	}

	void sequence::remove_current(){
		assert(is_item());
		//3 cases:
		//1. cursor at head
		//2. cursor in between tail and head
		//3. cursor at tail
		if(cursor == head_ptr){
			precursor = head_ptr->link();
			list_head_remove(head_ptr);
			cursor = head_ptr;
		}
		else {
			if(cursor != tail_ptr)
				cursor = cursor->link();
			else{
				tail_ptr = precursor;
				cursor = NULL;
			}
			list_remove(precursor);
		}
		many_nodes--;
	}

	//CONSTANT MEMBER FUNCTIONS
	sequence::size_type sequence::size() const{
		return many_nodes;
	}

	bool sequence::is_item() const {
		if(cursor != NULL)
			return true;
		return false;
	}

	node::value_type sequence::current() const{
		if(is_item())
			return cursor->data();
		return 0;
	}
}
