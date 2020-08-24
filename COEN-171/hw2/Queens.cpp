//#Name: Tanner Kaczmarek

/*
                2          4          6           8          10
 
 Knight        6           412        257318    379978716   1120204619108
 
 Bishops       4           260        53744    22522960     15915225216
 
 Rooks         2           24         720       40320        3628800
 
 Queens        0           2          4          92           724
 
 Amazons       0           0          0          0             4

 
 */



#include <iostream>
#include <cstdlib>
#include "Queens.h"


#ifndef PIECE
#define PIECE Queen
#endif

//declaring global variables
int numsolns = 0;
int N = 0;
PIECE **pieces;





void solve(int row, int col, int current);
bool isSafe(int current);


 
int main(){
    std::cout << "Number of rows and Cols?" << std::endl;
    std::cin >> N;   //N x N board from the user
    pieces = new PIECE*[N];
    for(int i = 0; i < N; i++)
        pieces[i]= new PIECE;
    solve(0,0,0);
    std::cout << numsolns << std::endl;
    return 1;
}



void solve(int row, int col, int current){
    for(int r = row; r < N; r++){
        for(int c = col; c < N; c++){
            pieces[current]->place(r,c); //placing current on the board
            //std::cout << r << " " << c << " " << current << " " << isSafe(current) << std::endl;
            if(isSafe(current)==true){    //we got a fair placement on the board!
                if(current +1 != N)
                    solve(r,c+1,current+1);   //recursive for next queen
                else
                    numsolns++;
            
            }
        }
        col = 0;
    }
}


bool isSafe(int current){
    for(int i = current - 1; i >= 0; i--){  //checks if it is a menace
        if (pieces[i]->menaces(pieces[current]) == true)
            return false;
    }
    /*
    for(int j = current; j < N; j++){
            if(pieces[current]->menaces(pieces[j]) == true)
                return false;
    }
     */
    
    return true;
}




