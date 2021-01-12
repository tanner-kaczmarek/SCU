/*
# Name: Tanner Kaczmarek
# Date: 10/08/20
# Title: Lab3 - Part 4 - Server
# Description: This code uses UDP connection to copy from one text file to another on the client side
*/

//UDP Client
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <fcntl.h>
#include <arpa/inet.h>

int main(int argc, char* argv[]){
 //Declare socket file descriptor. All  Unix  I/O  streams  are  referenced  by  descriptors
 int sockfd; 

 //Declare sending buffer of size 1k bytes
 char sbuf[1024]; 
 
 //Declare server address
 struct sockaddr_in servAddr, clienAddr; 
socklen_t addrLen = sizeof(struct sockaddr);


 //Converts  domain  names   into  numerical  IP  addresses  via  DNS
 struct hostent *host;
 host = (struct hostent *)gethostbyname("localhost"); //Local host runs the server. You may use "127.0.0.1": loopback IP address
 
 //Open a socket, if successful, returns  a descriptor  associated  with  an endpoint 
 if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
    perror("Failure to setup an endpoint socket");
    exit(1);
 }

 //Set the server address to send using socket addressing structure
 servAddr.sin_family = AF_INET;
 servAddr.sin_port = htons(5000);
 servAddr.sin_addr = *((struct in_addr *)host->h_addr);

 //Client to send messages to the server continuously using UDP socket 


/*
 FILE *fileSource = fopen(argv[1], "r");
   if(fileSource == NULL){
        printf("Cannot open the source file");
        exit(1);
    }

char buf[100];
int bytes = 0;

while(!feof(fileSource)){
   bytes = fread(&buf, 1, sizeof(buf), fileSource);
   sendto(sockfd, buf, strlen(buf), 0, (struct sockaddr *)&servAddr, sizeof(struct sockaddr));
   }

fclose(fileSource);
*/

   printf("Enter source file to request from other peer\n");
      scanf("%s", sbuf);
      //sends source file name to the client
      sendto(sockfd, sbuf, strlen(sbuf), 0, (struct sockaddr *)&servAddr, sizeof(struct sockaddr));
      while (1){
         int bytes;
         int fileDest = open(argv[1], O_RDWR);
         //receives from the server the source file data and writes it to destination file
         while((bytes = recvfrom(sockfd, sbuf, 1024, 0, (struct sockaddr *)&clienAddr, &addrLen))>0){
               write(fileDest, sbuf, bytes);
               printf("%s", sbuf);
         }
         close(fileDest);
         break;
      }

   return 0;

}
