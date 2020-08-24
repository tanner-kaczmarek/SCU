#include <iostream>
using namespace std;

int main(){
    string input;
    int alNum = 0;
    int nonAlNum = 0;
    int space= 0;

    //precondition: enters any strings from user    
    cout << "Enter a string: ";
    getline(cin, input);
    
    for(int i = 0; i < input.length(); i++){ //as long as the string is still going
        if(input[i] == ' ') 
	    space++;
        else if(isalnum(input[i]))  //alphanumeric character found
            alNum++; 
        else nonAlNum++;  //nonalphanumeric character found
    }
    
    //postcondition: Prints out how many characters that are alphanumeric and how many are not
    cout << input << " has " << alNum << " alphanumeric characters and " << nonAlNum << " non alphanumeric characters. ";

    return 0;
}
