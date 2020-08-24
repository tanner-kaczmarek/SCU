#include <cstdlib>
#include <string>
#include <cassert>
#include <algorithm>
#include <cmath>
#include <cctype>
#include <iostream>

#include "keyed_bag.h"

//code written mainly by Tanner Kaczmarek with assist of Nick Luckenbach

using namespace std;
namespace coen79_lab4
{
	
	//CONSTRUCTOR
	keyed_bag::keyed_bag(){
		used = 0;
	}

	//MEMBER FUNCTIONS
	void keyed_bag::erase(){
		used = 0;
	}
		

	bool keyed_bag::erase(const key_type& key){
		size_type i = 0;
		if(!has_key(key)) return false;  //does not have the key
		for(i = 0; i < used; i++){
			if(keys[i] == key){ //has the key at location i
				data[i] = data[used - 1];
				keys[i] = keys[used - 1];
				used--;
				return true;
			}
		}
		return false;
	}

	void keyed_bag::insert(const value_type& entry, const key_type& key){
		assert(used < CAPACITY);
		if(!has_key(key)){  //does not have the key in the bag so go ahead and add it
			keys[used] = key;
			data[used] = entry;
			used++;
		}
	}

	void keyed_bag::operator+=(const keyed_bag& addend){
		assert(size() + addend.size() <= CAPACITY);  //check the capacity
		assert(!hasDuplicateKey(addend)); 	     //check to make sure no duplicates

		copy(addend.data, addend.data + addend.used, data + used);
		copy(addend.keys, addend.keys + addend.used, keys + used);

		used += addend.used;
	}

	//CONSTANT MEMBER FUNCTIONS
	bool keyed_bag::has_key(const key_type& key) const{
		size_type i = 0;
		for(i = 0; i < used; i++){
			if(keys[i] == key)  //key is found
				return true;
		}
		return false;
	}

	keyed_bag::value_type keyed_bag::get(const key_type& key) const{
		assert(has_key(key));
		size_type i = 0;
		size_type value = -1;
		for(i = 0; i < used; i++){
			if(keys[i] == key)
				value = i;  //found the location
		}
		return data[value];
	}

	keyed_bag::size_type keyed_bag::size() const{
		return used;
	}

	keyed_bag::size_type keyed_bag::count(const value_type& target) const{
		size_type counter = 0;
		size_type i = 0;
		for(i = 0; i < used; i++){
			if(data[i] == target)
				counter++;  //found target so add it
		}
		return counter;
	}

	bool keyed_bag::hasDuplicateKey(const keyed_bag& otherBag) const{
		size_type i;
		for(i = 0; i < otherBag.used; i++)
			if(has_key(otherBag.keys[i])) return true;
		return false;
	}

	void keyed_bag::print( ) const{
		std::cout << "data		keys" << endl;
		for(size_type i = 0; i < used; i++)
			std::cout << data[i] << "		" << keys[i] << endl;
		std::cout << endl;
	}

	//NONMEMBER FUNCTION
	keyed_bag operator +(const keyed_bag& b1, const keyed_bag& b2){
		keyed_bag answer;
		assert(b1.size() + b2.size() <= keyed_bag::CAPACITY);  //make sure capacity isn't met
		answer += b1;
		answer += b2;
		return answer;
	}





}
