/*
# Name: Tanner Kaczmarek
# Date: 10/08/20
# Title: Lab3 - Part 1 - system calls
# Description: This program uses system calls to copy a text file to another text file
*/

#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

int main(int argc, char* argv[]){
    if(argc < 3){
        exit(1);
    }

    int fileSource = open(argv[1], O_RDWR);
    int fileReceiver = open(argv[2], O_RDWR);

    char buf[100];
    int bytes;

    while(read(fileSource, &buf, sizeof(buf))){
        write(fileReceiver, &buf, strlen(buf));
        memset(buf,0,strlen(buf)); 
    }

    close(fileSource);
    close(fileReceiver);

    return 0;
}