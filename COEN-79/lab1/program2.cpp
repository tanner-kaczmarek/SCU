#include <fstream>
#include <iostream>
using namespace std;

int main(){
    //precondition: test.txt is a file that has words with 10+ characters in it
    string test = "test.txt";
    ifstream input;
    input.open(test); //opens up text file
    
    string wordOG = ""; //noncapatlized string
    string wordBIG = ""; //capatalized string
    
    while (input >> wordOG){  //words exist in the input file
        if(wordOG.length() > 9) { //10+characters
            for(int i = 0; i < wordOG.length(); i++){ //iterate through word
                if(isalnum(wordOG[i]))  //check if it is alphanumeric
                    wordBIG.push_back(toupper(wordOG[i])); //capatilize the word and make it big
            }
        }
	//postcondition: prints out words in text file that are 10+ characters 
        cout <<wordBIG << endl;
        wordBIG = "";
    }
    return 0;
    
}
