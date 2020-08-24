/*
#Tanner Kaczmarek
#Date: 4/7/20
#Title: Lab 2 Part 7
#This program runs two different processes and prints whether if it is the parent or the child process. The child process also runs the ls command.
*/

#include <stdio.h>      /* printf, stderr */
#include <sys/types.h>  /* pid_t */
#include <unistd.h>     /* fork */
#include <stdlib.h>     /* atoi */
#include <errno.h>      /* errno */
/*main function with command-line arguments to pass */

int main(int argc, char *argv[]) {
    pid_t  pid;
    int i, n = atoi(argv[1]); // n microseconds to input from keyboard for delay
    printf("\n Before forking.\n");
    pid = fork();//forking
    if (pid == -1) {//error if it doesn't fork
        fprintf(stderr, "can't fork, error %d\n", errno);
    }
    else if (pid == 0){
        // Parent process
        execlp("/bin/ls", "ls", NULL);
        }
    else{
        // Child process
        wait(NULL);
        printf("Child Complete \n");
        exit(0);
    }
    return 0;
}
