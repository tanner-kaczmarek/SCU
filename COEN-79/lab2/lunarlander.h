//Constructor for lunar lander class
//lunarlander();
//	Postconditon: All variables which are double have been initialzed to numbers
//
//Public Modification
//void setFlowRate(double newRate)
//	Postcondition: New flow rate has been set given by the user
//void timePassage(double t)
//	Postcondition: current flow rate, vertical speed, altitude, amount of fuel all are changed by some calculations involving the given time
//
//Public Constant
//double getFlowRate()
//	Postcondition: Returned value is the current flow rate
//double getVelocity()
//	Postcondition: Returned value of vertical speed 
//double getAltitude()
//	Postcondition: Returns value of altitude of lunar lander
//double getFuel()
//	Postcondition: Returns value of amount of fuel in lunar lander
//double getMass()
//	Postcondition: Returns value of mass of the lander when it has no fuel
//double getMaxFuelRate()
//	Postcondition: Returns max fuel consumption rate of lunar lander
//double getMaxThrust()
//	Postcondition: Returns max thrust of lunar lander's engine


using namespace std;
#include<iostream>
  
class lunarlander
{
public:
	//constant member functions
        double getFlowRate() const {return current_fuel_flow_rate;}
        double getVelocity() const {return vertical_speed;}
        double getAltitude() const {return altitude;}
        double getFuel() const {return amount_of_fuel;}
        double getMass() const {return mass_of_lander_with_no_fuel; }
        double getMaxFuelRate() const {return max_fuel_consumption_rate;}
        double getMaxThrust() const {return max_thrust;}

	//modification member functions
        void setFlowRate(double newRate);
        void timePassage(double t);

	//constructor
	lunarlander();


private:
        double current_fuel_flow_rate;  //the rate as a fraction of the max fuel flow
        double vertical_speed; //in meters/second
        double altitude;  //in meters
        double amount_of_fuel;  //in kg
        double mass_of_lander_with_no_fuel; //in kg
        double max_fuel_consumption_rate;  //in kg/sec
        double max_thrust;  //in newtons

};
