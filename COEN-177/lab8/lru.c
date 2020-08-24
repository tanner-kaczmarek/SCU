/*
Name: Tanner Kaczmarek
Date: June 1st 2020
Title: Lab Assignment 8 - lru
Description: Implementing the lru algorithm for page replacement

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


typedef struct {//to 
    int pageno;
    int index;
} ref_page;


int main(int argc, char *argv[]){
	int C_SIZE = atoi(argv[1]); // Size of Cache passed by user 
    ref_page cache[C_SIZE]; // Cache that stores pages 
    char pageCache[100]; // Cache that holds the input from test file

    int i, j, temp, oldest;
    int totalFaults = 0; // keeps track of the total page faults
    
    for (i = 0; i < C_SIZE; i++){//initialise cache array  
         cache[i].pageno = -1;
         cache[i].index = 1;
    }

    while (fgets(pageCache, 100, stdin)){
    	int page_num = atoi(pageCache); // Stores number read from file as an int
        for(i = 0; i < C_SIZE; i++){
            temp = 0;
            oldest = cache[i].index;
            if(page_num == cache[i].pageno){
                for(j = 0; j < C_SIZE; j++){
                    if(cache[j].index < cache[i].index)
                        cache[j].index++;
                }
                cache[i].index = 0;
                break;
            }
            for(j = 0; j < C_SIZE; j++){
                cache[j].index++;
            }
            if(i == C_SIZE - 1){
                for(j = 0; j < C_SIZE; j++){
                    if(oldest < cache[j].index){
                        temp = j;
                        oldest = cache[j].index;
                    }
                }
                printf("Page fault at page %d \n", page_num);
                cache[temp].pageno = page_num;
                cache[temp].index = 0;
                totalFaults++;
            }
        }
    }

    printf("%d Total Page Faults", totalFaults);
    return 0;



}
