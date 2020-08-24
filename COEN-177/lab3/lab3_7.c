/*
 #Name: Tanner Kaczmarek
 #Date: 4/14/2020
 #Title: Lab3 - Part 6
 #Description:
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *go(void *);
#define NTHREADS 10
pthread_t threads[NTHREADS];
int main() {
    int i;
    for (i = 0; i < NTHREADS; i++)
        pthread_create(&threads[i], NULL, go, (void *) i);  //switched to (void *)i to get from actual value instead of address
    for (i = 0; i < NTHREADS; i++) {
        printf("Thread %d returned\n", i);
        pthread_join(threads[i],NULL);
    }
    printf("Main thread done.\n");
    return 0;
}
void *go(void *arg) {
    char *message;
    message = (char *) arg;
    printf("Hello from thread %d with iteration %d\n",  (int)pthread_self(), (int)(size_t *)arg);
    return 0;
}
