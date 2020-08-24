// Key solution
#include "pn.h"

void leaveCS(int i){
    j = (turn+1) % N;   //j is now the index
        while (flag[j]==idle) //finding a process not in idle state
            j = (j+1)%N;
        turn = j;
        flag[i]=idle; //acknowledging it is done
    printf("Thread %d left Critical Section\n", i);
}

void enterCS(int i){
        while (1) {
            flag[i] = want_in;     //notifying we want in
            j = turn;  //j is our index variable

            while (j != i) {  //finding our current process and repeating if need be until all processes are idle
                if (flag[j] != idle)
                    j = turn;
                else
                    j = (j+1) % N; 
            }
                flag[i] = in_cs; //claim in critical section tentatively
                j = 0;

                while ( (j<N) && (j==i || flag[j] != in_cs)) //finding the first active process
                    j++;
                if ( (j>=N) && (turn==i || flag[turn]==idle))  //exits if there are no other active processes and its this thread turn or if it this turns idle
                    break;      //ENTER THE CRITICAL SECTION
        }
    printf("Thread %d entered Critical Section\n", i);

}

void *thread(void* arg) {
        int i = (int)arg;
        enterCS(i);  //entry to critical section
        sleep(5);
        leaveCS(i);   //exit the critical section
        printf("Goodbye\n");
        return 0;
}

int main(){
    int i;
    for (i = 0; i < N; i++)  //creating N threads
         pthread_create(&thread_id[i], NULL, thread, (void*)(size_t)i); //passing i by value
    for (i = 0; i < N; i++)  //calling all the N threads to call the main thread to be in wait state
        pthread_join(thread_id[i], NULL);  //making it in wait state
    return 0;
}
