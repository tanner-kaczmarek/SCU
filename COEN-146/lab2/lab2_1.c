/*
Name: Tanner Kaczmarek
Date: 10/1/20 
Title: Lab 2 - Part 1
Description:  Using matrix multiply with threading for optimizing effiency
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdbool.h>
#include <pthread.h>

#define M 2
#define N 2
#define L 2
pthread_t threads[N];

float A[N][M], B[M][L], C[N][L], D[N][L];  //declaring all the matrices we need

void matrixMultiply() {   //single threaded matrix multiply given during class
    unsigned i,j,k;
    for ( i = 0; i < N; i ++)
        for ( j = 0; j < L; j ++)
            for ( k = 0; k < M; k++)
                D[i][j] += A[i][k] * B[k][j];    //result is in D
}

void printMatrix(float mat[N][L]){   //prints out the matrices
    int x, y;
    for(x = 0; x<N; x++){
        for(y = 0; y < L; y++){
            printf("%.1f ", mat[x][y]);  //accuracy to one after decimal point only
        }
        printf("\n");
    }
    printf("\n");
}

void *matMuptiply(void *arg){  //multithreaded matrix multiply
    int x = (int) arg;
    for(int i = 0; i < L; i++){
        double temp = 0;
        for (int j = 0; j< M; j++)
            temp += A[x][j] * B[j][i];  //Calculates it one row at a time
        C[x][i] = temp; 
    }
}



int main(){
    srand(time(0));
    for(int i = 0; i< N; i++){
        for(int j = 0; j < M; j++){   //creating random variables into our matrices from the range 0 - 25
            A[i][j] = (rand() % (25-0 + 1));
            B[i][j] = (rand() % (25-0 + 1));
        }
    }

    for(int i = 0; i< M; i++){
        for(int j = 0; j < L; j++){   //creating random variables into our matrices from the range 0 - 25
            A[i][j] = (rand() % (25-0 + 1));
            B[i][j] = (rand() % (25-0 + 1));
        }
    }

    printf("Printing matrices A and B");
    //printMatrix(A);  //making sure Matrix A looks ok
    //printMatrix(B);  //making sure Matrix B looks ok
    matrixMultiply();
    printf("Single threaded Matrix Multiply:  \n");
    printMatrix(D);  //prints result of single threaded matrix multiplication
    
    int p;
    
    //doing the threads in one step
    for(p = 0; p < N; p++)   //creating threads for each column of size
        pthread_create(&threads[p], NULL, matMuptiply, (void *)p);  //creates threads for each column in C
    for(p = 0; p < N; p++)
        pthread_join(threads[p], NULL);  //it will wait until the thread has finished before terminating it.  This ensures every column is filled
    
    printf("Multi-threaded Matrix Multiply: \n");
    printMatrix(C);
}