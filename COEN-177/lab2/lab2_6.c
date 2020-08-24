/*
#Tanner Kaczmarek
#Date: 4/7/20
#Title: Lab 2 Part 6
#This program runs two threads that print whether it is the parent or child process 100 times.
*/

#include <stdio.h>      /* printf, stderr */
#include <sys/types.h>  /* pid_t */
#include <unistd.h>     /* fork */
#include <stdlib.h>     /* atoi */
#include <errno.h>      /* errno */
#include <pthread.h>

void *process(void *ptr){  //process needs to return void and must be a pointer itself for pthread_create function
    int n;
    for (n = 0; n<100; n++){
        printf("Second thread %d \n",n);
        usleep(3000);  //needs a usleep to give other part of the thread a chacne
    }
}

int main(){
    pthread_t newThread;
    if(pthread_create(&newThread, NULL, &process, NULL) != 0){
        exit(1);  //error so we exit
    }
    int n;
    //the first thread
    for (n=0; n<100; n++){
        printf("\t First Thread %d \n", n);
        usleep(3000);
    }
    return 0;
}
