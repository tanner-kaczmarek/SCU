//commented by Tanner Kaczmarek
/**********************************************
*	Assignment 2: Run and comment in details  *
*   Winter 2019								  *
***********************************************/
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>
#include <signal.h>
int id;
struct Mesg{
   char Message[40];       //message got from the user
	int count;             //number of spaces in message plus one
	char token[10][20];
	char sorttoken[10][20];
};

#define KEY       ((key_t)(713))
#define SEGSIZE   sizeof(struct Mesg)

void cleanup(int sigtype){  //the signal handler to terminate the process.
   shmdt(0);   //detaches the shared memory segment
   printf("\n Terminating\n");
   execlp("ipcrm","ipcrm","-M","713",(char*)(0));  //control transferred to new program
   printf("ERROR!");
   exit(0);  //ends the current process 
}

int main(){
   int i,j;
	int count;  
	char *token;
	char tmp[20];
	struct Mesg *msg;        //created a data structure of Mesg named msg
	struct shmid_ds shmbuf;  //creating a shared memory data structure for the future shared memory segment in the system
	signal(SIGINT,cleanup);   //signal for control-c to send to cleanup
	signal(SIGQUIT,cleanup);  //signal for control-\ to send to cleanup
	id=shmget(KEY,SEGSIZE,IPC_CREAT|0666);  //the process createes a shared memory segment
	if(id<0){  //if this is true then error creating the new shared memory
	   perror("shmget failed 1\n");
		exit(1);
	}
	msg=(struct Mesg*) shmat(id,0,0);  //shared memory is attached to the structure msg
	if(msg<=(struct Mesg *)(0)){  //if it is less than 0 then the shared memory was not attached successfully
	   perror("shma failed 2\n");
		exit(1);
	}
	msg->count=0;   //copies 0 into the shared memory's count
	printf("Parent : Enter a Message : \n");
	count=read(0,msg->Message,40);  //reads 40 bytes of data from the user
	if(count<=0){  //less than zero if error with reading from the user
	   printf("read failed or no text entered!\n");
	   exit(0);
	}
   msg->Message[count-1]='\0'; //last byte that was read is now the null character
	printf("Parent pid = %d, Message readed:'%s'\n",getpid(),msg->Message); //prints process id
	printf("Just before forking, pid = %d\n",getpid()); //should be same as above pids
	if(fork()==0){  //if fork = 0 then we are in child id of the first fork
	   printf("pid: %d  fork 1\n", getpid());
              msg->count=1;
	      for(i=0;i<count;i++)
	         if(msg->Message[i]==' ')
	            msg->count++;  //msg->count is equal to the amount of spaces in the string plus one
	   printf("token count = %d\n",msg->count);
	   exit(0);   //ends the child process to avoid a zombie
	}else
	if(fork()==0){  //if fork = 0 then we are in child id of the second fork
	   sleep(1);
        printf("pid: %d fork 2\n", getpid());
		i=0;
		token=strtok(msg->Message," ");  //returns first token from message to token
		while(token!=NULL){  //copies tokens while one of the delimeters of space are present
		   strcpy(msg->token[i],token);
			i++;
			token=strtok(NULL," ");  //moves to next token (next word seperated by spaces)
		}
		printf("Tokens : \n");
		for(i=0;i<msg->count;i++){  //prints the tokens
		   printf("%s\n",msg->token[i]);
		}
		printf("Tokens end\n");
		exit(0);  //ends the child process to avoid a zombie
	}else
	if(fork()==0){  //if fork = 0 then we are in child id of the third fork
	   sleep(3);
	   printf("fork 3\n");
		for(i=0;i<msg->count;i++){  //moving values from token to sorted token
		   strcpy(tmp,msg->token[i]);
		   strcpy(msg->sorttoken[i],tmp);
		}
		for(i=msg->count-1;i>=0;i--){  //do this for the number of tokens
		   for(j=0;j<i;j++){
			   if(strcmp(msg->sorttoken[j],msg->sorttoken[j+1])>0){  //if the next sorted token is closer to beginning of the alphabet then need to switch the two
				   strcpy(tmp,msg->sorttoken[j]);
				   strcpy(msg->sorttoken[j],msg->sorttoken[j+1]);
				   strcpy(msg->sorttoken[j+1],tmp);
				}
			}
		}
		printf("Sorted tokens : \n");
		for(i=0;i<msg->count;i++){  //printing the new sorted tokens
		   printf("%s\n",msg->sorttoken[i]);
		}
		printf("Sorted tokens end\n");
		exit(0);  //ends the child process to avoid a zombie
	}
	
	for(i=0;i<3;i++)
	   wait(0);  //waits for child processes to terminate to avoid orphans.
	printf("Press Ctrl-C (or) Ctrl-\\ to clean up the memory and exit.\n");
	for(;;);  //indefinite loop waiting for a signal to cleanup to kill the program
 return 0; 
}

