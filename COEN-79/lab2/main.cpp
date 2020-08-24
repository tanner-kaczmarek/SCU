#include "lunarlander.h"
#include <iostream>
using namespace std;

//compile as follows: 
// g++ -c main.cpp
// g++ -c lunarlander.cpp
// g++ -o main main.o lunarlander.o 
// ./main


//Helper function to print lunar lander info
void print(lunarlander &l){
	cout << "Current fuel flow rate: " <<  l.getFlowRate() << endl;
	cout << "Vertical Speed of the lander: " << l.getVelocity() << "meters/sec" <<  endl;
	cout << "Altitude: " << l.getAltitude() << "meters" << endl;
	cout << "Fuel: " << l.getFuel() << "kg" << endl;
	cout << "Mass of lander: " << l.getMass() << "kg" <<  endl;
	cout << "Max fuel consumption rate: " << l.getMaxFuelRate() << "kg/sec" << endl;
	cout << "Max thrust: " << l.getMaxThrust() << "newtowns" << endl;
	cout << endl;
}

//main function testing success of setFlowRate and timePassage
int main(){
	lunarlander test;
	print(test);
	test.setFlowRate(.5);
	test.timePassage(.1);
	print(test);
	test.timePassage(.5);
	print(test);
	test.setFlowRate(.3);
	test.timePassage(.5);
	print(test);
	return 1;
}
