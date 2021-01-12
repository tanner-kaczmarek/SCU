/*
#Name: Tanner Kaczmarek
#Date: 10/15/2020
#Title: Lab 4 - Step 2
#Description: This program runs client-server file distribution
*/

//TCP Server
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <fcntl.h>
#include <string.h>

#define N 1024
pthread_t threads[N];
int fileReceiver;

//Declare socket file descriptor. All  Unix  I/O  streams  are  referenced  by  descriptors
int sockfd, connfd, rb, sin_size;

//Declare receiving and sending buffers of size 1k bytes
//char rbuf[1024], sbuf[1024];

//Declare server address to which to bind for receiving messages and client address to fill in sending address
 struct sockaddr_in servAddr, clienAddr;

void* serverWrite (void *x){
    char rbuf[1024], sbuf[1024];
    int bytes; 
    int i = (int)x;
    //printf("%d\n", i);
    //printf("Connection Established with client: IP %s and Port %d\n", inet_ntoa(clienAddr.sin_addr), ntohs(clienAddr.sin_port));
    //receiving the file name from the cleint
    rb = recv(i, rbuf, 1024, 0);
	rbuf[rb] = '\0';
	fileReceiver = open(rbuf, O_RDWR);
    //printf("%s\n", rbuf);
    memset(rbuf,0,strlen(rbuf)); 

    
    //sends to the client the data from the source file
    while((bytes = read(fileReceiver, sbuf, 1024))>0){
        write(i, &sbuf, 1024);
        //printf("%s\n", sbuf);
        memset(sbuf,0,strlen(sbuf)); 

    } 

    close(i);
}
    


int main(int argc, char* argv[]){

 

 //Open a TCP socket, if successful, returns  a descriptor  associated  with  an endpoint
 if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    perror("Failure to setup an endpoint socket");
    exit(1);
 }

 //Setup the server address to bind using socket addressing structure
 servAddr.sin_family = AF_INET;
 servAddr.sin_port = htons(5000);
 servAddr.sin_addr.s_addr = INADDR_ANY;

 //Set address/port of server endpoint for socket socket descriptor
 if ((bind(sockfd, (struct sockaddr *)&servAddr, sizeof(struct sockaddr))) < 0){
    perror("Failure to bind server address to the endpoint socket");
    exit(1);
 }

 printf("Server waiting for client at port 5000\n");

 // Server listening to the socket endpoint, and can queue 5 client requests
 listen(sockfd, 5);
 sin_size = sizeof(struct sockaddr_in);

//int bytes;
//char buf[1024];


int i = 0;

while (1){
 //Server accepting to establish a connection with a connecting client, if successful, returns a connection descriptor  
    
    if ((connfd = accept(sockfd, (struct sockaddr *)&clienAddr, (socklen_t *)&sin_size)) < 0){
        perror("Failure to accept connection to the client");
        exit(1);
    }
    //creates a new thread for the connection with the client
    pthread_create(&threads[i], NULL, serverWrite, (void *)(size_t)connfd);
    i++;
    //printf("%d \n", connfd);


 /*
 //Connection established, server begins to read and write to the connecting client
 FILE *fileReceiver = fopen(argv[1], "a");
 while ((bytes = read(connfd, buf, 1024))>0)
   fwrite(&buf, bytes, 1, fileReceiver);

fclose(fileReceiver);
*/

}

int j =0;
for (j = 0; j<i; j++){
    pthread_join(threads[j], NULL);
}

close(connfd);
close(sockfd);
return 0;
}
