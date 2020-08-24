#include "mystring.h"

using namespace coen79_lab5;

int main() {
	std::cout << "lets test" << std::endl;
	//use all 3 constructors
	string test1;
	string test2('T');
	string test3("testing");
	string test4(test3);

	//test insert
	std::cout << "Insertion Testing" << std::endl;
	test2.insert(" ", 0);
	//test2.insert("ab", 0);
	
	//test replace
	std::cout << "replace test" << std::endl;
	test4.replace("tester", 0);
	std::cout << test4 << std::endl;
	
	//test printing the string
	std::cout << "Cout testing" << std::endl;
	std::cout << test3 << std::endl;

	//test += function
	std::cout << "n+= test" << std::endl;
	test3 += test2;

        //test addition operator
        std::cout << "Testing + operator " << std::endl;
        string longest(test3 + test4);
        std::cout << longest << std::endl;

	//test = function
	std::cout << "= test" << std::endl;
	test1 = test3;
	std::cout << test1 << " should now be " << test3 << std::endl;

	//test delete function
	std::cout <<"dlt test: deleting first 3 instances in test" << std::endl;
	test3.dlt(0,3);
	std::cout << test3 << std::endl;

	//test search for a character
	std::cout <<"searching for r in" << test4 << std::endl;
	char r = 'r';
	int i = test4.search(r);
	std::cout << i << std::endl;

	//teest search for a string
	std::cout << "searching for est in " << test4 << std::endl;
	i = test4.search("est");
	std::cout << i << std::endl;
	
	//test count function
	std::cout << "Testing count of t in " <<test4 << std::endl;
	i = test4.count('t');
	std::cout << i<< std::endl;

	//check the compare operators:
	std::cout << "comapring " << test1 << " to " << test4 << std::endl;
	std::cout << "==: " << (test1 == test4) << std::endl;
	std::cout << "!=: " << (test1 != test4) << std::endl;
	std::cout << "<: " << (test1 < test4) << std::endl;
	std::cout << "<=: " << (test1 <= test4) << std::endl;
	std::cout << ">: " << (test1 > test4) << std::endl;
	std::cout << ">=: " << (test1 >= test4) << std::endl; 

	return 0;
	
}
