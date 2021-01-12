/*
Name: Tanner Kaczmarek
Date: 10/1/20 
Title: Lab 2 - Part 4
Description: Calcultating Round Trip Time and other scenarios involving TCP connections
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char* argv[]){
    int RTT0 = 3;
    int RTT2 = 20;
    int RTT3 = 26;
    int RTTHTTP = 47;

    //A
    int Time1 = RTT0 + RTT2 + RTT3 + (2 * RTTHTTP);
    printf("Assuming zero tranmission time, it took %d ms from when the client clicks on link till when receives object \n", Time1);

    //B
    int Time2 = RTT0 + RTT2 + RTT3 + (2 * RTTHTTP) + (6 * RTTHTTP) + (6 * RTTHTTP);
    printf("Neglecting tranmsission time, the time it takes to reference 6 small objects is %d ms \n", Time2);

    //C
    int Time3 = 0;
    int Time4 = 0; 
    int N = atoi(argv[1]);
    double packets = (N>6)? 1:  6/N;
    int np = ceil(packets);

    Time3 = RTT0 + RTT2 + RTT3 + (2 * RTTHTTP) + (2* np * RTTHTTP);
    printf("Non persistent %d parallel TCP connections is %d ms \n", N, Time3);

    Time4 = RTT0 + RTT2 + RTT3 + (2*RTTHTTP) + (np*RTTHTTP);
    printf("Persistent %d parallel TCP connections is %d ms \n", N, Time4);

}
