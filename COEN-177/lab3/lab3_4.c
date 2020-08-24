/*
 #Name: Tanner Kaczmarek
 #Date: 4/14/20
 #Title: Lab3 - Part 4
 Description: A program to run the shell command: cat /etc/passwd | grep root
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[]){
    int fds[2];
    char buff[60];
    int count;
    int i;
    pipe(fds);
    if(fork()==0){
        printf("\nWriter on the upstream end of the pipe -> %d arguments \n",argc);
        close(fds[0]);
        dup2(fds[1], 1); //stdout
        execlp("cat", "cat", "/etc/passwd", 0);  //passing cat to command line then /etc/passwd
        exit(0);  //end child process
    }
    else if(fork()==0){
        printf("\nReader on the downstream end of the pipe \n");
        close(fds[1]);
        dup2(fds[0],0); //stdin
        execlp("grep", "grep", "root", 0);  //passes grep then root to command line
        exit(0);  //end child process
    }
    else{
        close(fds[0]);
        close(fds[1]);
        wait(0);  //wait for children to terminate to avoid orphan processes
        wait(0);
    }
    return 0;
}
