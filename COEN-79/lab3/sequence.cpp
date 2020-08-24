#include <cassert>
#include "sequence1.h"
#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <cmath>
using namespace coen79_lab3;


//CONSTRUCTOR
sequence::sequence(){
	for(int i = 0; i++; i<30)
		data[i] = 0;
	current_index = 0;
	used = 0;
}

//MODIFICATION MEMBER FUNCTIONS
void sequence::start(){
	current_index = 0;
}

void sequence::end(){
	current_index = used - 1;
}

void sequence::last(){
	current_index = CAPACITY - 1;
}

void sequence::advance(){
	if(current_index == CAPACITY - 1)
		current_index = CAPACITY - 1;
	else if(current_index < used)
		current_index++;
}

void sequence::retreat(){
	if(current_index == 0)
		current_index = 0;
	else
		current_index = current_index - 1;
}

void sequence::insert(const value_type& entry){
	assert(1 + used <= CAPACITY);
	for(size_type i = used; i > current_index; i--){
		data[i] = data[i-1];
		}
	data[current_index] = entry;
	used++;
}

void sequence::attach(const value_type& entry){
	assert(1 + used <= CAPACITY);
	assert(is_item());
	for(size_type i = used; i > current_index; i--)
		data[i] = data[i-1];
	data[current_index+1] = entry;
	used++;
}
void sequence::remove_current(){
	assert(used > 0);
	for(size_type i = current_index; i < size()-1; i++)
		data[i] = data[i+1];
	used--;
}

void sequence::insert_front(const value_type& entry){
	assert(used + 1 <= CAPACITY);
	for(size_type i = size(); i > 0; i--)
		data[i] = data[i-1];
	data[0] = entry;
	used++;
}

void sequence::attach_back(const value_type& entry){
	assert(used + 1 <= CAPACITY);
	data[used] = entry;
	used++;
}

void sequence::remove_front(){
	assert(is_item());
	for(size_type i = 0; i < size()-1; i++)
		data[i] = data[i+1];
	used--;
}

void sequence::operator +=(const sequence& rhs){
	assert(size() + rhs.size() <= CAPACITY);
	value_type hold = current_index;
	current_index = used;
	sequence temp = rhs;
	temp.start();
	for(size_type i = 0; i < rhs.size(); i++)
	{
		attach(rhs.current());
		temp.advance();
	}
	
}

//CONSTANT MEMBER FUNCTIONS
bool sequence::is_item( ) const{
	if(current_index < used)
		return true;
	return false;
}

sequence::value_type sequence::current() const{
	return data[current_index];	
}

sequence::value_type sequence::operator[](int index) const{
	return data[index];
}

double sequence::mean() const{
	double sum = 0;
	for(int i = 0; i < used; i++)
		sum += data[i];
	return (sum/used);
}

double sequence::standardDeviation() const
{
	double standardDeviation = 0.0;
	double mean = sequence::mean();
	for(int i = 0; i < used; i++)
		standardDeviation += pow(data[i]-mean,2);
	return sqrt(standardDeviation/used);	

}


//NONMEMBER FUNCTIONS
sequence operator+(const sequence& lhs, const sequence& rhs){
	sequence answer;
	assert(lhs.size() + rhs.size() <= sequence::CAPACITY);
	answer += lhs;
	answer += rhs;
	return answer;
}

sequence::value_type summation(const sequence &s){
	coen79_lab3::sequence::value_type summation;
	summation = 0;
	for(int i = 0; i < s.size(); i++)
		summation += s[i];
	return summation;
}



