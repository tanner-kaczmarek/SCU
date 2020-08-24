/*
#Name: Tanner Kaczmarek
#Date: 8 June 2020
#Title: lab 9 - Step 3
#Description: This program reads buffer size of 100, 1000, 10000, and 10000 to a buffer
*/
 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[]){
    int SIZE = atoi(argv[2]);
    char *buffer[SIZE];
    FILE *fp;
    fp = fopen(argv[1], "rb");
    while(fread(buffer, SIZE, 1, fp)){}
    fclose(fp);
    return 0;
}
