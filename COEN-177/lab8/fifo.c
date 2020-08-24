
/*
Name: Tanner Kaczmarek
Date: June 1st 2020
Title: Lab Assignment 8 - FIFO
Description: Implementing the FIFO algorithm for page replacement

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


typedef struct {//to 
    int pageno;
} ref_page;


int main(int argc, char *argv[]){
	int C_SIZE = atoi(argv[1]); // Size of Cache passed by user 
    ref_page cache[C_SIZE]; // Cache that stores pages 
    char pageCache[100]; // Cache that holds the input from test file
    int counter;
    int i;
    int totalFaults = 0; // keeps track of the total page faults
    
    for (i = 0; i < C_SIZE; i++){//initialise cache array
         cache[i].pageno = -1;
    }

    while (fgets(pageCache, 100, stdin)){
    	int page_num = atoi(pageCache); // Stores number read from file as an int
        for(i = 0; i < C_SIZE; i++){
            if(cache[i].pageno == page_num)
                break;
            else if(i == C_SIZE - 1){
                printf("Page fault at page %d \n", page_num);
                totalFaults++;
                cache[counter].pageno = page_num;
                if(counter + 1 != C_SIZE)
                    counter++;
                else
                    counter = 0;
            }
        }
        
    }
    printf("%d Total Page Faults", totalFaults);
    return 0;

}
