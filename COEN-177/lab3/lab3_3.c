/*
 # Name: Tanner Kaczmarek
 # Date: 4/13/20
 # Title: Lab 3 - Part 2
 # Description: Program prints out the last command in the terminal with spaces between each of the characters
 */

/*Sample C program for Lab assignment 3*/
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
// main
int main(int argc,char *argv[]){
    int fds[2];
    char buff[60];
    int count;
    int i;
    pipe(fds);
    if (fork()==0){
        printf("\nWriter on the upstream end of the pipe -> %d arguments \n",argc);
        close(fds[0]);
        for(i=0;i<argc;i++){
            dup2(fds[1],1);  //sends to stdout side of the pipe we created
            execlp("ls", "ls", 0);  //sends ls to command line
        }
        exit(0);
    }
      else if(fork()==0){
          printf("\nReader on the downstream end of the pipe \n");
          close(fds[1]);
          while((count=read(fds[0],buff,60))>0){  //gets the values from stdin side of pipe we created.
              for(i=0;i<count;i++){
                  write(1,buff+i,1); //get one character at a time
                  write(1," ",1);
              }
              printf("\n");
              
          }
          exit(0);
          
      }
    else{
        close(fds[0]);
        close(fds[1]);
        wait(0);  //avoiding having parent process finish before children. 
        wait(0);
    }
    return 0;
}
