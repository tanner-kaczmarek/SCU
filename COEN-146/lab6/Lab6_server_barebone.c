/*
# Name: Tanner Kaczmarek
# Date: 10/08/20
# Title: Lab6 - Server
# Description: This code is the server side of a file transfer that takes in account for bad checksum or sequence number, and also has a timer for packets that never arrive. 
*/

//Explain what each library does in the context of this lab. Do we need all of them?
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <time.h>
#include <unistd.h>
#include <netdb.h>
#include <netinet/in.h>
#include "lab6.h"

//add the missing functions
//******STUDENT WORK******
//******STUDENT WORK******


void ServerSend(int sockfd, const struct sockaddr *address, socklen_t addrlen, int seqnum) {
    // Simulatting a chance that ACK gets lost
    if (rand()%10 == 0) {
        //******STUDENT WORK******
        printf("Dropping packet\n");
        return;
    }
    //prepare and send the ACK
    Packet packet;
    //******STUDENT WORK******
    packet.header.seq_ack = seqnum;
    packet.header.len = 0;
    packet.header.cksum = getChecksum(packet);

    sendto(sockfd, &packet, sizeof(packet), 0, address, addrlen);
    printf("Sent ACK %d, checksum %d\n", packet.header.seq_ack, packet.header.cksum);

    printf("Sent ACK %d, checksum %d\n", packet.header.seq_ack, packet.header.cksum);
}

Packet ServerReceive(int sockfd, struct sockaddr *address, socklen_t *addrlen, int seqnum)
{
                     
    Packet packet;

    while (1) {
        //Receive a packet from the client
        //******STUDENT WORK******
        recvfrom(sockfd, &packet, sizeof(packet), 0, address, addrlen);


        // validate the length of the packet
        //******STUDENT WORK******
        int packetLength = strlen(packet.data);
        if(packetLength != packet.header.len){
            printf("Packet Length is not equal to the packet header length \n");
            printf("%d %d \n", packetLength, packet.header.len);
        }

        // log what was received
        printf("Received: ");
        logPacket(packet);

        //verify the checksum and the sequence number
        if (packet.header.cksum != getChecksum(packet)) {
            printf("Bad checksum, expected %d\n", getChecksum(packet));
            //******STUDENT WORK******
            ServerSend(sockfd, address, *addrlen, !seqnum);

        } else if (packet.header.seq_ack != seqnum) {
            printf("Bad seqnum, expected %d\n", seqnum);
            ServerSend(sockfd, address, *addrlen, !seqnum);
            //******STUDENT WORK******
        } else {
            printf("Good packet\n");
            //******STUDENT WORK******
            ServerSend(sockfd, address, *addrlen, seqnum);
            break;
        }
    }

    printf("\n");
    return packet;
}

int main(int argc, char *argv[]) {
    // check arguments
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <port> <outfile>\n", argv[0]);
        return EXIT_FAILURE;
    }

    // seed the RNG
    srand((unsigned)time(NULL));

    // create a socket
    //******STUDENT WORK******
    int sockfd;
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Failure to setup an endpoint socket");
        exit(1);
    }

    // initialize the server address structure
    //******STUDENT WORK******
    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_port = htons(atoi(argv[1])); //Port 5000 is assigned
    address.sin_addr.s_addr = INADDR_ANY;


    // bind the socket
    //******STUDENT WORK******
    if ((bind(sockfd, (struct sockaddr *)&address, sizeof(struct sockaddr))) < 0){
        perror("Failure to bind server address to the endpoint socket");
        exit(1);
    }

    //Please answer the following questions
        //[Q1] Briefly explain what is "AF_INET" used for.
        //[Q2] Briefly explain what is "SOCK_DGRAM" used for.
        //[Q3] Briefly explain what is "htons" used for.
        //[Q4] Briefly explain why bind is required on the server and not on the client.
    
    
    
    // open file
    FILE *file = fopen(argv[2], "wb");
    if (file == NULL) {
        perror("fopen");
        return EXIT_FAILURE;
    }

    // get file contents from client and save it to the file
    int seqnum = 0;
    Packet packet;
    struct sockaddr_in clientaddr;
    socklen_t clientaddr_len = sizeof(clientaddr);
    do {
        //******STUDENT WORK******
        packet = ServerReceive(sockfd, (struct sockaddr*)&clientaddr, &clientaddr_len, seqnum);
        fwrite(packet.data, 1, packet.header.len, file);
        (seqnum == 0)? (seqnum = 1):(seqnum = 0);
    } while (packet.header.len != 0);

    //cleanup
    //******STUDENT WORK******
    fclose(file);
    close(sockfd);
    
    return 0;
}
