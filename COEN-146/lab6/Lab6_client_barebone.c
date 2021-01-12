/*
# Name: Tanner Kaczmarek
# Date: 10/08/20
# Title: Lab6 - Client
# Description: This code is the Client side of a file transfer that takes in account for bad checksum or sequence number, and also has a timer for packets that never arrive. 
*/

#include <arpa/inet.h>
#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <time.h>
#include <unistd.h>
#include <netdb.h>
#include <netinet/in.h>
#include "lab6.h"

int sequence;

void ClientSend(int sockfd, const struct sockaddr *address, socklen_t addrlen, Packet packet, unsigned retries) {

    while (1) {
        // calculate the checksum
        //******STUDENT WORK******
        if(retries == 3){
            printf("Too many tries");
            break;
        }

        int ranN = rand() % 4;
        printf("%d \n", ranN);
        if(ranN > 2){
            packet.header.cksum = 5;
        }
        else
            packet.header.cksum = getChecksum(packet);

        ranN = rand() % 4;
        printf("%d \n", ranN);
        if(ranN > 2){
            packet.header.seq_ack = !sequence;
        }
        else
        {
            packet.header.seq_ack = sequence;
        }
        // log what is being sent
        printf("Created: ");
        logPacket(packet);

        // Simulate lost packet.
        if (rand()%10 == 0) {
            printf("Dropping packet\n");
        } else {
            //******STUDENT WORK******
            sendto(sockfd, &packet, sizeof(packet), 0, address, addrlen);
            }

        // wait until either a packet is received or timeout, i.e using the select statement
        struct timeval tv;
        tv.tv_sec = 1;
        tv.tv_usec = 0;
        fd_set readfds;
        //******STUDENT WORK******
        fcntl(sockfd, F_SETFL, O_NONBLOCK);
        FD_ZERO(&readfds);
        FD_SET(sockfd, &readfds);

        int rv = select(sockfd + 1, &readfds, NULL, NULL, &tv);
        if(rv == 0){
            retries++;
            continue;
        }
    
        // receive an ACK from the server
        Packet recvpacket;
        //******STUDENT WORK******
        recvfrom(sockfd, &recvpacket, sizeof(recvpacket), 0, address, &addrlen);

        // log what was received
        printf("Received ACK %d, checksum %d - ", recvpacket.header.seq_ack, recvpacket.header.cksum);

        // validate the ACK
        if ( recvpacket.header.cksum != getChecksum(recvpacket)) {
            // bad checksum, resend packet
            printf("Bad checksum, expected %d\n", getChecksum(recvpacket));
        } else if (recvpacket.header.seq_ack != sequence) {
            // incorrect sequence number, resend packet
            printf("Bad seqnum, expected %d\n", packet.header.seq_ack);
        } else {
            // good ACK, we're done
            (sequence == 0)? (sequence = 1): (sequence =0);
            printf("Good ACK\n");
            break;
        }
    }

    printf("\n");
}

int main(int argc, char *argv[]) {
    // check arguments
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <ip> <port> <infile>\n", argv[0]);
        return 1;
    }

    // seed the RNG
    srand((unsigned)time(NULL));

    // create and configure the socket
    //******STUDENT WORK******
   int sockfd; 
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Failure to setup an endpoint socket");
        exit(1);   
    }

    // initialize the server address structure
    //******STUDENT WORK******
    struct sockaddr_in address;
    memset(&address, 0, sizeof(address));
    struct hostent *host;
    host = (struct hostent *)gethostbyname(argv[2]);
    address.sin_family = AF_INET;
    address.sin_port = htons(atoi(argv[1])); //Port 5000 is assigned
    address.sin_addr = *((struct in_addr *)host->h_addr); 

    // open file
    FILE *file = fopen(argv[3], "rb");
    if (file == NULL) {
        perror("fopen");
        return 1;
    }

    // send file contents to server
    Packet packet;
    int bytes;
    sequence = 0; 

    //******STUDENT WORK******
    while(!feof(file)){
        bytes = fread(packet.data, 1, sizeof(packet.data), file);
        packet.header.seq_ack = sequence;
        packet.header.len = bytes;
        packet.header.cksum = getChecksum(packet);
        ClientSend(sockfd, &address, sizeof(struct sockaddr), packet, 0);
    }


    // send zero-length packet to server to end connection according the description provided in the Lab manual
    //******STUDENT WORK******
    packet.header.seq_ack = sequence;
    packet.header.len = 0;
    packet.header.cksum = getChecksum(packet);
    ClientSend(sockfd, &address, sizeof(struct sockaddr), packet, 0);


    // clean up
    //******STUDENT WORK******
    fclose(file);
    close(sockfd);
    return 0;
}
