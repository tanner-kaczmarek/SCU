/*
# Name: Tanner Kaczmarek
# Date: 10/08/20
# Title: Lab5 - Client
# Description: This code is the client side of a file transfer that takes in account for bad checksum or sequence number
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
#include "lab5.h"

int sequence;

// NOTE: beware of sign extension if the checksum is stored in a char, then converted to an int!
int getChecksum(Packet packet) {
    packet.header.cksum = 0;

    int checksum = 0;
    char *ptr = (char *)&packet;
    char *end = ptr + sizeof(Header) + packet.header.len;

//Please find an error from the remaining part getChecksum() function 
//******STUDENT WORK****** 
    while (ptr < end) {
        checksum ^= *ptr;
        ptr++;  //look here
    }

    return checksum;
}

void logPacket(Packet packet) {
    printf("Packet{ header: { seq_ack: %d, len: %d, cksum: %d }, data: \"",
            packet.header.seq_ack,
            packet.header.len,
            packet.header.cksum);
    fwrite(packet.data, (size_t)packet.header.len, 1, stdout);
    printf("\" }\n");
}



void ClientSend(int sockfd, const struct sockaddr *address, socklen_t addrlen, Packet packet) {
    while (1) {

        // send the packet
        printf("Sending packet\n");
		//******STUDENT WORK******

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
        

        logPacket(packet);
        sendto(sockfd, &packet, sizeof(packet), 0, address, addrlen);

        // receive an ACK from the server
        Packet recvpacket;
		//******STUDENT WORK******
        recvfrom(sockfd, &recvpacket, sizeof(recvpacket), 0, address, &addrlen);
        //printf("fail2\n");

        // log what was received
        printf("Received ACK %d, checksum %d - ", recvpacket.header.seq_ack, recvpacket.header.cksum);

        // validate the ACK
        if (recvpacket.header.cksum != getChecksum(recvpacket)) {
            // bad checksum, resend packet
            printf("Bad checksum, expected checksum was: %d\n", getChecksum(recvpacket));
        } else if (recvpacket.header.seq_ack != sequence) {
            // incorrect sequence number, resend packet
            printf("Bad seqnum, expected sequence number was: %d\n", sequence);
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

    // create and configure the socket [name the socket sockfd] 
	//******STUDENT WORK******	 
    int sockfd; 
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Failure to setup an endpoint socket");
        exit(1);   
    }

    // initialize the server address structure using argv[2] and argv[1]
    struct sockaddr_in address;
    memset(&address, 0, sizeof(address));
	//******STUDENT WORK******
    struct hostent *host;
    host = (struct hostent *)gethostbyname(argv[2]); //Local host runs the server. You may use "127.0.0.1": loopback IP address

    address.sin_family = AF_INET;
    address.sin_port = htons(atoi(argv[1])); //Port 5000 is assigned
    address.sin_addr = *((struct in_addr *)host->h_addr);

    // open file using argv[3]
	//******STUDENT WORK******
    int fileSource = open(argv[3], O_RDWR);

    // send file contents to server
	//-create a packet
	//-set the seq_ack field 
	//-set the len field
	//-calculate the checksum
	//-send the packet
	//******STUDENT WORK******
    Packet p;
    int bytes;
    sequence = 0;
    
    while((bytes = read(fileSource, p.data, sizeof(p.data))) > 0){
        p.header.seq_ack = sequence;
        p.header.len = bytes;
        //p.header.cksum = 5;      //testing bad checksum
        ClientSend(sockfd, &address, sizeof(struct sockaddr), p);
    }
    



    // send zero-length packet to server to end connection
	//******STUDENT WORK******
    p.header.seq_ack = sequence;
    p.header.len = 0;
    p.header.cksum = getChecksum(p);
    ClientSend(sockfd, &address, sizeof(struct sockaddr), p);

    // clean up
	//-close the sockets and file
    	//******STUDENT WORK******
    close(fileSource);
    close(sockfd);


    return 0;
}
