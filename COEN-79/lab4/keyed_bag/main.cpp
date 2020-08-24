#include <cctype>
#include <iostream>
#include <cstdlib>
#include "keyed_bag.h"

using namespace std;
using namespace coen79_lab4;

//compile as follows:
//g++ - c main.cpp
//g++ -c keyed_bag.cpp
//g++ -o main main.o keyed_bag.o
// ./main

//coded mainly by Tanner Kaczmarek with assist from Nick Luckenbach


//create a function to test count in the keyed bag class
void test_count(int test, keyed_bag baglet){
	cout << test << " appears in the bag " << baglet.count(test) << " times" << endl;
}



int main(){
	//create keyed bags
	keyed_bag k1, k2, k3;

	//insert into the first keyed bag
	k1.insert(3, "one");
	k1.insert(2, "two");
	k1.insert(5, "three"); 
	k1.insert(1, "four");
	k1.insert(3, "five");

	cout << "Bag1" << endl;
	k1.print();

	//test erase and cout function in keyed bag
	k1.erase("three");
	cout << "Bag1" <<endl;
	k1.print();
	test_count(3,k1);
	test_count(1,k1);

	//insert into the second keyed bag
	k2.insert(4, "six");
	k2.insert(7, "seven");
	k2.insert(3, "eight");
	cout << "Bag2" << endl;
	k2.print();

	//check the + operator
	k3 = k1 + k2;
	cout << "Bag3" <<endl;
	k3.print();

	//check the += operator
	k2+=k1;
	cout << "Bag2" <<endl;
	k2.print();
	cout << "Bag1" <<endl;
	k1.print();

	//check erase again with second keyed bag
	k2.erase("two");
	k2.erase("seven");
	cout << "Bag2" <<endl;
	k2.print();
}
