#include <iostream>
#include <iomanip>
using namespace std;

int main (){
    string input = "0123456789";
    int window1 = 5; //window that seperates the strings
    int window2 = 1; //window that pushes first string out
    string reversed = input; 
    reverse(reversed.begin(), reversed.end());  //reverse the string
    
    for (int i = 0; i < 5; i++){  //print out the staircase
        cout << input;
        cout << setw(window1);
        cout << reversed << endl;
        cout << setw(window2);
        window1 += 2;
        window2++;
    }
    
    return 0;
} 
    
