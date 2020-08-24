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
            write(fds[1],argv[i],strlen(argv[i]));
        }
        exit(0);
    }
      else if(fork()==0){
          printf("\nReader on the downstream end of the pipe \n");
          close(fds[1]);
          while((count=read(fds[0],buff,60))>0){
              for(i=0;i<count;i++){
                  write(1,buff+i,1);
                  write(1," ",1);
              }
              printf("\n");
              
          }
          exit(0);
          
      }
    else{
        close(fds[0]);
        close(fds[1]);
        wait(0);
        wait(0);
    }
    return 0;
}
