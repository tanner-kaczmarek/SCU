#include <iostream>
using namespace std;

int main(){
    int guesses = 0;
    int correct = 0;

    //Let user think of a number
    cout << "Think of a number between 1 and 20. Push enter when ready." << endl;
    cin.ignore();  //ignore user button press
    //precondition: User needs to think of a number between 1 and 20

    string input;
    string Y ("Y");
    string Yes("Yes");
    string N ("N");
    string No ("No");    

    int i = 1;
    int steps = 1;

    
    while(i<21){ //Use successive guesses counting up from 1 to 20
	cout << "Is the number " << i << "? Y or N" << endl;  
	cin >> input;
        if(input.compare(Y) == 0 || input.compare(Yes) ==0){  //If user found it
	    cout << "I found the number in " << steps << " steps";
	    i = 21;
	}    
	else if(input.compare(N) == 0 || input.compare(No) == 0){ //If user did not it
            steps++;
            i++;
        }
	else
	     cout << "only enter Y or N" << endl;  //If user did not enter yes or no
    }
//postcondition: outputs they found the users numbers
    
}
