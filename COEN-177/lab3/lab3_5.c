/*
 #Name: Tanner Kaczmarek
 #Date: 4/14/20
 #Title: Lab 3 - Part 5
 #Description: The program implements the producer-consumer message communication using pipes.
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
        write(fds[1], "Producer", strlen("Producer"));  //sending into buffer of stdout Producer 1
        exit(0); //exit out of this child process
    }
    else if(fork()==0){
        printf("\nReader on the downstream end of the pipe \n");
        close(fds[1]);
        while((count = read(fds[0], buff, 60))>0){  //read to buff from the pipe
            for(i=0; i < count; i++){
                write(1,buff+i,1);  //one byte at a time
            }
        }
        printf("\n");
    }
    else{
        close(fds[0]);
        close(fds[1]);
        wait(0);  //wait for child processes to end to avoid orphan processes
        wait(0);
    }
    return 0;
}
