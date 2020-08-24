/*
#Name: Tanner Kaczmarek
#Date: 8 June 2020
#Title: lab 9 - Step 4
#Description: This program reads buffer size of 100, 1000, 10000, and 10000 to a buffer
*/
 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[]){
    int SIZE = atoi(argv[2]);
    char buffer[SIZE];
    FILE *in = fopen(argv[1], "rb");
    FILE *out = fopen("output.txt", "wb");
    while(fread(buffer, SIZE, 1, in)){
        fwrite(buffer, SIZE, 1, out);
    }
    fclose(in);
    fclose(out);
    return 0;
}
