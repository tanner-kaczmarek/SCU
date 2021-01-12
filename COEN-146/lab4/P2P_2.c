/*
#Name: Tanner Kaczmarek
#Date: 10/15/2020
#Title: Lab 4 - Step 2
#Description: This program runs P2P file distribution
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <fcntl.h>
#include <arpa/inet.h>


//Declare socket file descriptor. All  Unix  I/O  streams  are  referenced  by  descriptors
 int sockfd; 

 //Declare sending buffer of size 1k bytes
 char srbuf[1024]; 
 
 //Declare server address
 struct sockaddr_in servAddr, clienAddr;
 socklen_t addrLen = sizeof(struct sockaddr);


 //Converts  domain  names   into  numerical  IP  addresses  via  DNS
 //struct hostent *host;
 void openSocketServ(){
    
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Failure to setup an endpoint socket");
        exit(1);
    }

    //Setup the server address to bind using socket addressing structure
    servAddr.sin_family = AF_INET;
    servAddr.sin_port = htons(5001); //Port 5000 is assigned
    servAddr.sin_addr.s_addr = INADDR_ANY; //Local IP address of any interface is assigned (generally one interface IP address)
 }

void openSocketClient(){
     struct hostent *host;
     host = (struct hostent *)gethostbyname("localhost"); //Local host runs the server. You may use "127.0.0.1": loopback IP address

    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Failure to setup an endpoint socket");
        exit(1);
    }

    servAddr.sin_family = AF_INET;
    servAddr.sin_port = htons(5000); //Port 5000 is assigned
    servAddr.sin_addr = *((struct in_addr *)host->h_addr);

 }

void server(){
    openSocketServ();
    if ((bind(sockfd, (struct sockaddr *)&servAddr, sizeof(struct sockaddr))) < 0){
        perror("Failure to bind server address to the endpoint socket");
        exit(1);
    }
 
    //Sever continuously waits for messages from client, then prints incoming messages.
    while (1){
        
        printf("Server waiting for messages from client: \n"); //server waiting for file name from the client peer
        int nr = recvfrom(sockfd, srbuf, 1024, 0, (struct sockaddr *)&clienAddr, &addrLen);
        
        //srbuf[nr] = '\0';
        printf("Client with IP: %s and Port: %d sent message: %s\n", inet_ntoa(clienAddr.sin_addr),ntohs(clienAddr.sin_port), srbuf);
        
        int fileS = open(srbuf, O_RDWR);
        int bytes;
        //server sends the data in the file to the client
        while((bytes = read(fileS, srbuf, 1024)) > 0){
            sendto(sockfd, srbuf, 1024, 0, (struct sockaddr *)&clienAddr, sizeof(struct sockaddr));
            memset(srbuf,0,strlen(srbuf)); 

        }
        
    }
}

void client(){
    openSocketClient();
    printf("Enter source file to request from other peer\n");
    scanf("%s", srbuf);
    //sends source file name to the client
    sendto(sockfd, srbuf, strlen(srbuf), 0, (struct sockaddr *)&servAddr, sizeof(struct sockaddr));
    while (1){
        int bytes;
        int fileDest = open("dest1.txt", O_RDWR);
        //receives from the server the source file data and writes it to destination file
        while((bytes = recvfrom(sockfd, srbuf, 1024, 0, (struct sockaddr *)&clienAddr, &addrLen))>0){
            write(fileDest, srbuf, bytes);
            printf("%s", srbuf);
        }
        close(fileDest);
        break;
    }
}

int main(){
    while (1){
        char choice;
        printf("For Peer 1 if you would like to SEND enter s; if you would like to Receiver enter r; or enter q to quit\n");
        scanf("%c", &choice);
        if (choice == 's'){
            server();
        }
        else if(choice == 'r'){
            client();
        }
        else
        {
            exit(1);
        }
        break;
        
    }
    return 0; 
}