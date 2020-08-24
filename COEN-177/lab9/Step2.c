/*
Name: Tanner Kaczmarek
Date: 8 June 2020
#Title: Lab 9 - Step 2
#Description: This will read from 100k, 1M, 10M, and 100M files to a 10000 byte buffer
*/

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
    char *buffer[10000];
    FILE *fp;
    fp = fopen(argv[1], "rb");
    while(fread(buffer, 10000, 1, fp)){}
    fclose(fp);
    return 0; 
}
