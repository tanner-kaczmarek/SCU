/*
# Name: Tanner Kaczmarek
# Date: 9/24/20
# Title: Lab1 - Section 6 and 7
# Description: The code is an example of Circuit Switching and Packet Switching calculations. 
*/


#include <stdio.h>      /* printf, stderr */
#include <sys/types.h>  /* pid_t */
#include <unistd.h>     /* fork */
#include <stdlib.h>     /* atoi */
#include <errno.h>      /* errno */ 
#include <math.h>

//factorial function done with recursion
double factorial(double n){
    if(n <= 0)
        return 1;
    else
        return (n * factorial(n-1));
}

int main(){
    int linkBandwidth = 200; //Mbps
    int userBandwidth = 20; //Mbps
    double tPSuser = .10;
    int nPSusers = 19;

    //6a
    int nCSusers = linkBandwidth/userBandwidth;
    printf("Number of circuit-switched users that can be supported: %d\n", nCSusers);

    //7a
    double pPSuser = tPSuser;
    printf("The probability that a given user is busy transmitting is: %f \n", pPSuser);

    //7b
    double pPSusersNotBusy = 1 - pPSuser;
    printf("The probability that that one specific other user is not busy is: %f \n", pPSusersNotBusy);

    //7c
    double pSpecificUserNotBusy = pow(pPSusersNotBusy, (nPSusers - 1));
    printf("The probability that all of the other specific other users are not busy is %f \n", pSpecificUserNotBusy);

    //7d
    double pUserTransmittingAndRestNot = pPSuser * pow(pPSusersNotBusy, (nPSusers - 1));  
    printf("The probability that only one specific user is transmitting and rest are not is %f \n", pUserTransmittingAndRestNot);

    //7e
    double anyOne = nPSusers * pPSuser * pow(pPSusersNotBusy, (nPSusers - 1)); 
    printf("The probability that exaclty one of the nPSusers users is busy is pPSusers time the probablity that a given specific user is transmitting and the remaining users are not is %f \n", anyOne);

    //7f 
    double pTenUsers = pow(pPSuser, 10) * pow(pPSusersNotBusy, nPSusers-10);
    printf("The probability that 10 specific users are transmitting and others are idle is %lf \n", pTenUsers);

    //7g
    double anyTenTemp = factorial(nPSusers)/(factorial(10)*factorial(nPSusers - 10));  //binomial coefficient
    double anyTen = anyTenTemp * pow(pPSuser, 10) * pow(pPSusersNotBusy, (nPSusers - 10));
    printf("The probablity that any 10 users of nPSusers are transmitting and the others are idle is %lf \n", anyTen);

    //7h
    double moreThanTen = 0;
    double temp = 0;
    for(int i = 11; i < userBandwidth; i++){
        temp = factorial(nPSusers)/(factorial(i)*factorial(nPSusers - i));   //binomial coefficient
        moreThanTen += temp * pow(pPSuser, i) * pow(pPSusersNotBusy, (nPSusers - i));  
    }
    printf("The probablility that more than 10 users of nPSusers are transmitting and the others are idle is %lf \n" ,moreThanTen);



}
