/*
#Tanner Kaczmarek
#Date: 4/7/20
#Title: Lab 2 Part 5
#Description: This program outputs 7 processes, starting with the parent process. Each process either has two children or none at all.
*/

#include <stdio.h>      /* printf, stderr */
#include <sys/types.h>  /* pid_t */
#include <unistd.h>     /* fork */
#include <stdlib.h>     /* atoi */
#include <errno.h>      /* errno */
/*main function with command-line arguments to pass */

int main(){
    pid_t pid1, pid2, pid3, pid4, pid5, pid6;  //an additional 6 processes originated from the original one making 7.
    printf("Original Process with Parent: %d\n", getpid());  
    pid1 = fork();  //first branch fork from original parent
    if(pid1 == 0){  //this is the child of the original parent
        printf("Process 1 - Child with id: %d   Parent's id: %d \n", getpid(), getppid());
        pid3= fork(); //forking from pid1
        if (pid3==0)
            printf("Process 3 - Child with id: %d   Parent's id: %d \n", getpid(), getppid());
        if(pid3 > 0){
            pid6 = fork();  //forking from pid1
            if(pid6 == 0)
                printf("Process 6 - Child with id: %d   Parent's id: %d \n", getpid(), getppid());
        }

    }
    else if(pid1>0){  //original parent process still
        pid2 = fork();  //another branch fork from the orignal parent
        if(pid2==0){  //child so go on as done with original parent
            printf("Process 2 - Child with id: %d   Parent's id: %d \n", getpid(), getppid());
            pid4 = fork();  //forking from pid2
            if(pid4==0)
                printf("Process 4 - Child with id: %d   Parent's id: %d \n", getpid(), getppid());
            if(pid4 > 0){
                pid5 = fork();  //forking from pid2
                if(pid5 == 0)
                    printf("Process 5 - Child with id: %d   Parent's id: %d \n", getpid(), getppid());
            }
        }
            wait(3000);  //needs
    }
}
