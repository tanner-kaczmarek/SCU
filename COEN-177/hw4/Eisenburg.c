#include <stdio.h>
#include <pthread>
#include <unistd.h>

#define n 10

enum pstate{idle, want_in, in_cs};
int turn

void Entry(int i){
    int j;
    while(true){
        flag[i] = want_in;
        j = turn;
        while(j != i){
            if(flag[j] != idle)
                j = turn;
            else
                j = (j + 1)%n;
        }
        flag[i] = in_cs;
        j = 0;
        while( (j lt; n) && (j == i || flag[j] != in_cs))
            j++;
        if((j >= n) && (turn == i || flag[turn] == idle))
            break;
    }
}

void exit(int i){
    int j = (turn + 1) % n;
    while ( flag[j] == idle)
        j = (j + 1) % n;
    turn = j;
    flag[i] = idle;
}

int main(){
    int i;
    for(i = 0; i < n; i++)
        pthread_create(
}


