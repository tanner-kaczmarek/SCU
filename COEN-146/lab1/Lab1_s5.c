/*
# Name: Tanner Kaczmarek
# Date: 9/24/20
# Title: Lab1 - Section 5
# Description: The code is a simple example that uses pthreads with an inputted delay between them. 
*/

/*COEN 146L : Lab1 */
#include <stdio.h>      /* printf, stderr */
#include <sys/types.h>  /* pid_t */
#include <unistd.h>     /* fork */
#include <stdlib.h>     /* atoi */
#include <errno.h>      /* errno */ 
#include <pthread.h>

// go function works when the threads are created and prints out the process for the given thread
void* go(void *arg){
    int p = (int) arg;
    for(int i = 0; i<100; i++){
        printf("Thread with ID %d is printing ititeration %d\n", (int)pthread_self(), i);
        usleep(p);
    }
    return 0;
}

/* main function with command-line arguments to pass */
int main(int argc, char *argv[]) {
    pthread_t thread1, thread2;
    int i, n = atoi(argv[1]); // n microseconds to input from keyboard for delay

    pthread_create(&thread1, NULL, go, (void *)(size_t)n);
    pthread_create(&thread2, NULL, go, (void *)(size_t)n);

    pthread_join(thread1, NULL);  //waiting for the thread to end to finish the program
    pthread_join(thread2, NULL);  //waiting for the thread to end to finish the program
    return 0;
}

