/*
 Name: Tanner Kaczmarek
 Date: June 1st 2020
 Title: Lab Assignment 8 - second chance
 Description: Implementing the second chance algorithm for page replacement
 
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

    int i,j;
    int totalFaults = 0; // keeps track of the total page faults
    int schance = 0;
    int replace = 0;
    
    for (i = 0; i < C_SIZE; i++){//initialise cache array
        cache[i].pageno = -1;
        cache[i].index = 0;
    }

    while (fgets(pageCache, 100, stdin)){
    	int page_num = atoi(pageCache); // Stores number read from file as an int
        for(i = 0; i < C_SIZE; i++){
            if(page_num == cache[i].pageno){
                cache[i].index = 1;
                schance=0;
                break;
            }
            if(i == C_SIZE - 1)
                schance = 1;
        }
        if(schance== 1){
            for(j = replace; j < C_SIZE; j++){
                if(cache[j].index == 1){ 
                    cache[j].index = 0;
                    replace++;
                    if(replace == C_SIZE){
                        replace = 0;
                        j = -1;
                    }
                }
                else{
                    cache[j].pageno = page_num;
                    cache[j].index = 0;
                    totalFaults++;
                    if(replace + 1 != C_SIZE)
                        replace++;
                    else
                        replace = 0;
                    printf("Page fault at page %d \n", page_num);
                    break;
                }
            }
        }
    }

    printf("%d Total Page Faults", totalFaults);
    return 0;



}
