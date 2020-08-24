#include <iostream>
#include <cassert>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <stdio.h>
#include "mystring.h"


namespace coen79_lab5
{

//CONSTRUCTOR, COPY CONSTRUCTOR, AND DESTRUCTOR
string::string(const char str[]){
	current_length = 0;
	allocated = 0;
	size_t size = (strlen(str));
	characters = NULL;
	reserve(size);
	for(size_t i = 0; i < size; i++){
		characters[i] = str[i];
	}
	current_length = size;
	characters[current_length] = '\0';
}

string::string(char c){
	current_length = 0;
	allocated = 0;
	reserve(1);
	current_length = 1;
	characters[0] = c;
	characters[current_length] = '\0';
}

string::string(const string& source){
	current_length = 0;
	allocated = 0;
	size_t size = source.length();
	characters = NULL;
	reserve(size);
	strncpy(characters, source.characters, size);
	current_length = size;
	characters[current_length] = '\0';
}

string::~string(){
	delete [] characters;
}




//MODIFICATION MEMBER FUNCTIONS
void string::operator +=(const string& source){
	if(current_length + source.length() > allocated)
		reserve(current_length + source.length() );
	strncat(characters, source.characters, source.length() );
	current_length = current_length + source.length();
}

void string::operator +=(const char addend[]){
	if(current_length + strlen(addend) > allocated)
		reserve(current_length+strlen(addend) );
	strncat(characters, addend, strlen(addend));
	current_length = current_length + strlen(addend);
}

void string::operator +=(char addend){
	if(current_length + 2 > allocated)
		reserve(allocated + 1);
	current_length++;
	characters[current_length - 1] = '\0';
	characters[current_length] = addend;
}

void string::reserve(size_t n){
	if(allocated >= n + 1) return;
	char* use = new char[n+1];
	strncpy(use, characters, current_length);
	use[current_length] = '\0';
	delete [] characters;
	characters = use;
	allocated = n;
	//delete [] use;
}

string& string::operator =(const string& source){
	reserve(source.allocated);
	strncpy(characters, source.characters, source.allocated);
	current_length = source.length();
	return * this;
}

void string::insert(const string& source, unsigned int position){
	assert(position <= current_length);
	char *use = new char[current_length + 1 + source. length() ];
	strncat(use, characters, position);
	strncat(use, source.characters, source.length() );
	strncat(use, characters + position, allocated);
	delete [] characters;
	characters = use;
	current_length++;
	delete [] use;
}

void string::dlt(unsigned int position, unsigned int num){
	assert(position + num <= current_length);
	strncpy(characters + position, characters + position + num, allocated);	
	current_length -= num;
}

void string::replace(char c, unsigned int position){
	assert(position < current_length);
	characters[position] = c;
}

void string::replace(const string& source, unsigned int position){
	assert(position + source.length() <= current_length);
	char * use = new char[allocated];
	strncat(use, characters, position);
	strncat(use, source.characters, source.length());
	strncat(use, characters + position + source.length(), allocated);
}




//CONSTANT MEMBER FUNCTIONS
char string::operator [](size_t position) const{
	//assert(position < current_length);
	return characters[position];
}

int string::search(char c) const{
	int index = -1;
	size_t i;
	for(i = 0; i < current_length; i++){
		if(characters[i] == c){
			index = i;
			break;
		}
	}
	return index;
}

int string::search(const string& substring) const{
	int index = -1;
	size_t i;
	for(i = 0; i < current_length; i++){
		if(strncmp(characters + 1, substring.characters, substring.length()) == 0){
			index = i;
			break;
		}
	}
	return index;
}

unsigned int string::count(char c) const{
	unsigned int counter = 0;
	size_t i;
	for(i = 0; i < current_length; i++)
		if(characters[i] == c) counter++;
	return counter;
}




//FRIEND FUNCTIONS
std::ostream& operator <<(std::ostream& outs, const string& source){
	size_t i = 0;
	while(source.characters[i] != '\0'){
		outs << source.characters[i];
		i++;
	}	
	return outs;
}

bool operator ==(const string& s1, const string& s2){
	size_t i;
	//if(s1.length() != s2.length()) return false;
	//for(i = 0; i<s1.length(); i++)
		//if(s1.characters[i] != s2.characters[i]) return false;
	//return true;
	return (strcmp(s1.characters, s2.characters) == 0);
}

bool operator !=(const string& s1, const string&s2){
	size_t i;
	if(s1.length() != s2.length()) return true;
	for(i = 0; i <s1.length(); i++)
		if(s1.characters[i] != s2.characters[i]) return true;
	return false;
}

bool operator >(const string& s1, const string& s2){
	int test = strcmp(s1.characters, s2.characters);
	if(test > 0) return true;
	return false;
}

bool operator <(const string& s1, const string& s2){
	int test = strcmp(s1.characters, s2.characters);
	if(test < 0) return true;
	return false;
}

bool operator >=(const string& s1, const string& s2){
	int test = strcmp(s1.characters, s2.characters);
	if(test >= 0) return true;
	return false; 
}

bool operator <=(const string& s1, const string& s2){
	int test = strcmp(s1.characters, s2.characters);
	if(test <= 0)return true;
	return false; 
}


//NON-MEMBER FUNCTIONS
string operator +(const string& s1, const string& s2){
	string temp(s1);
	temp += s2;
	return temp;
}

string operator +(const string& s1, const char addend[]){
	string temp(s1);
	temp += addend;
	return temp;
}

std::istream& operator >> (std::istream& ins, string& target){
	char input;
	target = "";
	while(ins && isspace(ins.peek()))
		ins.ignore();
	while(!ins.eof() && !isspace(ins.peek())){
		ins >> input;
		target += input;
	}
	return ins;
}




}
