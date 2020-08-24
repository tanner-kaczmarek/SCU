#include <iostream>
#include "lunarlander.h"
using namespace std;


//constructor
lunarlander::lunarlander()
{
        current_fuel_flow_rate = 0;
        vertical_speed = 0;
        altitude = 1000;
        amount_of_fuel = 1700;
        mass_of_lander_with_no_fuel = 900;
        max_fuel_consumption_rate = 10;
        max_thrust = 5000;
}

//sets new current flow rate
void lunarlander::setFlowRate(double newRate){
	//double newRate = (rand() % 11)/10;
	current_fuel_flow_rate = newRate;
	return;
}

//takes passage of time and edits amount of fuel, current fuel flow rat, vertical speed, and altitude
void lunarlander::timePassage(double t){
	if(amount_of_fuel == 0)
		current_fuel_flow_rate = 0;
	double f = current_fuel_flow_rate*max_thrust;
	vertical_speed = t*((f/mass_of_lander_with_no_fuel) - 1.62);
	altitude =t*vertical_speed;
	amount_of_fuel = t*current_fuel_flow_rate*max_fuel_consumption_rate;
	if(altitude <= 0){
		altitude = 0;
		vertical_speed = 0;
	}
	if(amount_of_fuel <= 0)
		amount_of_fuel = 0;


} 
