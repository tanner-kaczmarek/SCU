#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

#define N 100    //Nthreads 
pthread_t thread_id[N]; 
enum pstate {idle, want_in, in_cs};
enum pstate flag[N];
int turn;
int j;  //index

