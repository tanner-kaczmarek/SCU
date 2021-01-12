/*
#Name: Tanner Kaczmarek
#Date: 10/15/2020
#Title: Lab 4 - Step 2
#Description: This program runs client-server file distribution
*/

//TCP Client
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char* argv[]){
//Declare socket file descriptor. All  Unix  I/O  streams  are  referenced  by  descriptors. nr is a declaration of the number of recieved bytes.
int sockfd, nr;

//Declare sending and recieving buffers of size 1k bytes
char sbuf[1024], rbuf[1024];

//Declare server address to connect to
struct sockaddr_in servAddr;
struct hostent *host;

//Converts  domain  names   into  numerical  IP  addresses  via  DNS
host = (struct hostent *)gethostbyname("localhost");

//Open a socket, if successful, returns  a descriptor  associated  with  an endpoint
 if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    perror("Failure to setup an endpoint socket");
    exit(1);
 }

//Set the server address to send using socket addressing structure
servAddr.sin_family = AF_INET;
servAddr.sin_port = htons(5000);
servAddr.sin_addr = *((struct in_addr *)host->h_addr);

//Connect to the server
if (connect(sockfd, (struct sockaddr *)&servAddr, sizeof(struct sockaddr))){
    perror("Failure to connect to the server");
    exit(1);
}

 //Client begins to write and read from the server
 while(1){
    //sends a filename to the server
    printf("Client: Type a filename to send to Server\n");
    scanf("%s", sbuf);
    write(sockfd, sbuf, strlen(sbuf));
    int fileC = open(argv[1], O_RDWR);
    
    int bytes;
    //receives data from the file and writes it to destination file
    while((bytes = recv(sockfd, rbuf, 1024, 0)) > 0)
      write(fileC, &rbuf, 1024);
      //printf("%s\n", rbuf);
 }

 //Close socket descriptor
 close(sockfd);
 return 0;
}