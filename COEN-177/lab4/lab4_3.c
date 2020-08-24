/*
Name: Tanner Kaczmarek
Date: 4/21/20 T 5:15
Title: Lab 4 - Part 2
Description:
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdbool.h>
#include <pthread.h>

#define SIZE 8
pthread_t threads[SIZE];
float A[SIZE][SIZE], B[SIZE][SIZE], C[SIZE][SIZE], D[SIZE][SIZE];  //declaring all the matrices we need

void matrixMultiply() {   //single threaded matrix multiply given during class
    unsigned i,j,k;
    for ( i = 0; i < SIZE; i ++)
        for ( j = 0; j < SIZE; j ++)
            for ( k = 0; k < SIZE; k++)
                D[i][j] += A[i][k] * B[k][j];    //result is in D
}

void printMatrix(float mat[SIZE][SIZE]){   //prints out the matrices
    int x, y;
    for(x = 0; x<SIZE; x++){
        for(y = 0; y < SIZE; y++){
            printf("%.1f ", mat[x][y]);  //accuracy to one after decimal point only
        }
        printf("\n");
    }
    printf("\n");
}

void *matMuptiply(void *arg){  //multithreaded matrix multiply
    int x = (int) arg;
    //double temp = 0;
    for(int i = 0; i < SIZE; i++){
        for (int j = 0; j< SIZE; j++)
            C[i][x] += A[i][j] * B[j][x];  //Calculates it one row at a time
    }
}



int main(){
    srand(time(0));
    for(int i = 0; i< SIZE; i++){
        for(int j = 0; j < SIZE; j++){   //creating random variables into our matrices from the range 0 - 25
            A[i][j] = (rand() % (25-0 + 1));
            B[i][j] = (rand() % (25-0 + 1));
        }
    }
    printf("Printing matrices A and B");
    printMatrix(A);  //making sure Matrix A looks ok
    printMatrix(B);  //making sure Matrix B looks ok
    matrixMultiply();
    printf("Single threaded Matrix Multiply:  \n");
    printMatrix(D);  //prints result of single threaded matrix multiplication
    
    int p;
    
    //doing the threads in one step
    for(p = 0; p < SIZE; p++)   //creating threads for each column of size
        pthread_create(&threads[p], NULL, matMuptiply, (void *)p);  //creates threads for each column in C
    for(p = 0; p < half; p++)
        pthread_join(threads[p], NULL);  //it will wait until the thread has finished before terminating it.  This ensures every column is filled
    
    printf("Multi-threaded Matrix Multiply: \n");
    printMatrix(C);
}
