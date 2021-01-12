/*
# Name: Tanner Kaczmarek
# Date: 10/08/20
# Title: Lab3 - Part 1 - functions
# Description: This code uses functions to copy a text file to another file
*/

#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

int main (int argc, char *argv[]){
    if(argc < 3){
        exit(1);
    }

    FILE *fileSource = fopen(argv[1], "r");
    FILE *fileReceiver = fopen(argv[2], "w");

    if(fileSource == NULL || fileReceiver == NULL){
        printf("Cannot open the source or destination file");
        exit(1);
    }

    char buf[100];
    int bytes = 0;

    while(!feof(fileSource)){
        bytes = fread(&buf, 1, sizeof(buf), fileSource);
        fwrite(&buf, 1, bytes, fileReceiver);
    }
    fclose(fileSource);
    fclose(fileReceiver);

    return 0; 
}
