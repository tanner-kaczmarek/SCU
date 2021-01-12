/*
# Name: Tanner Kaczmarek
# Date: 10/08/20
# Title: Lab3 - Part 5 - Server
# Description: This code uses TCP connection to copy from one text file to another on the server side
*/

//TCP Server
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <netdb.h>
#include <string.h>

int main(int argc, char* argv[]){
 //Declare socket file descriptor. All  Unix  I/O  streams  are  referenced  by  descriptors
 int sockfd, connfd, rb, sin_size;

 //Declare receiving and sending buffers of size 1k bytes
 char rbuf[1024], sbuf[1024];

 //Declare server address to which to bind for receiving messages and client address to fill in sending address
 struct sockaddr_in servAddr, clienAddr;

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

 int bytes;
 char buf[1024];

while (1){
 //Server accepting to establish a connection with a connecting client, if successful, returns a connection descriptor  
 if ((connfd = accept(sockfd, (struct sockaddr *)&clienAddr, (socklen_t *)&sin_size)) < 0){
	perror("Failure to accept connection to the client");
    exit(1);
 }
 //Connection established, server begins to read and write to the connecting client
 /*FILE *fileReceiver = fopen(argv[1], "a");
 while ((bytes = read(connfd, buf, 1024))>0)
   fwrite(&buf, bytes, 1, fileReceiver);
   */
  rb = recv(connfd, rbuf, 1024, 0);
	rbuf[rb] = '\0';
	int fileReceiver = open(rbuf, O_RDWR);
    //printf("%s\n", rbuf);
   memset(rbuf,0,strlen(rbuf)); 

    
    //sends to the client the data from the source file
   while((bytes = read(fileReceiver, sbuf, 1024))>0){
      write(connfd, &sbuf, 1024);
        //printf("%s\n", sbuf);
        memset(sbuf,0,strlen(sbuf)); 

    } 

close(fileReceiver);
break;
}
close(sockfd);
return 0;
}
