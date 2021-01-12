/* Name: Tanner Kaczmarek
 * Date: November 11 2020
 * Link State Routing
 * Lab 7
 * Description: Building a link state routing protocol that communicates change in neighbor cost. Also the use of Djikstra Algorithm to find shortest algorithm.
 */

#include <unistd.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <time.h>
#include <unistd.h>
#include <netdb.h>
#include <netinet/in.h>
#include <pthread.h> 
#include <errno.h>
        // Import the required libraries
        //******STUDENT WORK******


//defines
#define	N			6
#define	INFINITE	1000

//program takes in 0) program name, 2) number of Nodes, 1) myID #, 3)File, 4) Cost File

// types
typedef struct machines
{
	//******STUDENT WORK******	
	int port;
	char name[50];
	char ip[50];

} MACHINES;


// global variables
MACHINES	machines[N];
int			costs[N][N];
int			distances[N];
int			myid, nodes;
int			sock;
struct sockaddr_in addr;
struct sockaddr_in otheraddr;
socklen_t addr_size;
pthread_mutex_t	lock;



// functions
void *run_link_state (void *);
void *receive_info (void *);
void *change_costs (void *);  //new function used to change costs. 
void print_costs (void);


/**********************
 * main
 **********************/
int
main (int argc, char *argv[])
{
	FILE	*fp;
	int		i, j;
	pthread_t	thr1, thr2, thr3;
	int		id, cost;
	int		packet[3];


	if (argc < 5)
	{
		// check the number of arguments
        //******STUDENT WORK******
		printf("Not enough arguments \n");
		return 1; 
	}

	myid = atoi(argv[1]);
	nodes = atoi(argv[2]);

	if (id >= N)
	{
		printf ("wrong id\n");
		return 1;
	}	

	if (nodes != N)
	{
		printf("%d", nodes);
		printf ("wrong number of nodes\n");
		return 1;
	}	
	
	//get info on machines from the file using fopen and fscanf and populate the array of machines-struct
	//******STUDENT WORK******
	if ((fp = fopen(argv[3], "r"))==NULL){
		printf("Was not able to read from the files containing info for the machines");
		return 1; 
	}
	for(i = 0; i < N; i++){
		fscanf(fp, "%s %s %d", machines[i].name, machines[i].ip, &machines[i].port);
	}


	// get costs from the costs file and populate the matrix
	if ((fp = fopen (argv[4], "r")) == NULL){
		printf("Not able to read from the costs file \n");
		return 1;
	}
	for(i = 0; i<N; i++){
		for(j = 0; j<N; j++){
			fscanf(fp, "%d", &costs[i][j]);
		}
	}

	//******STUDENT WORK******
	fclose(fp);
	
    // init address
    //******STUDENT WORK******
	addr.sin_family = AF_INET;
    addr.sin_port = htons(machines[myid-1].port); //Port 5000 is assigned
    addr.sin_addr.s_addr = INADDR_ANY;

	addr_size = sizeof(struct sockaddr);


    // create socket
    //******STUDENT WORK******
    if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Failure to setup an endpoint socket");
        exit(1);
    }

    // bind
    //******STUDENT WORK******
	if ((bind(sock, (struct sockaddr *)&addr, sizeof(struct sockaddr))) < 0){
        perror("Failure to bind server address to the endpoint socket");
        exit(1);
    }


	// create threads and initiate mutex
	pthread_mutex_init (&lock, NULL);
	pthread_create (&thr1, NULL, receive_info, NULL);
	pthread_create (&thr2, NULL, run_link_state, NULL);

	// read changes from the keyboard, update the costs matrix inform other nodes about the changes
	{ // This section can be inside the main or can be a thread by itself
		for (i = 0; i < 3; i++)
		{
			//******STUDENT WORK******
			if(i == 0){
				pthread_create(&thr1, NULL, receive_info, NULL);  // run the receive_info function 
			}
			if(i == 1){
				pthread_create(&thr2, NULL, change_costs, NULL);  //run the change costs function
			}
			if(i == 2){
				pthread_create(&thr3, NULL, run_link_state, NULL);  //run the run link state function 
			}


			printf ("sent\n");
		}
	}

	pthread_join(thr1, NULL);
	pthread_join(thr2, NULL);
	pthread_join(thr3, NULL);

	sleep (5);

}


/**********************
 * receive info
 **********************/
//If there is a cost update on other machine, they will let us know through a UDP packet. We need to receive that packet and update our costs table
void *receive_info (void *arg)
{
	int	new[3];
	int	nbytes;
	int	n0, n1, n2;

	while(1){

		//using udp to send
		recvfrom(sock, new, sizeof(new), 0, (struct sockaddr *)&addr, &addr_size);
		n0 = new[0];
		n1 = new[1];
		n2 = new[2];

		//change for the new costs changes
		pthread_mutex_lock(&lock);
		costs[n0][n1] = n2;
		costs[n1][n0] = n2;
		pthread_mutex_unlock(&lock);

		printf("Costs Updated: \n");
		print_costs();
		sleep(10);
	}
	
}

/**********************
 * change costs
 **********************/
// scans a location and cost change from user and sends to all other nodes with a UDP transportation protocol. 
void *change_costs(void * arg){
	int newCost;
	int neighborID;
	int i;
	int data[3];


	while(1){
		printf("Enter neighbor's id to change (know that the current ID is: %d )\n", myid);
		scanf("%d", &neighborID);
		printf("Enter new cost: \n");
		scanf("%d", &newCost);

		//change to both locations on the table
		pthread_mutex_lock(&lock);
		costs[myid-1][neighborID-1] = newCost;
		costs[neighborID-1][myid-1] = newCost;
		pthread_mutex_unlock(&lock);

		printf("Costs Changed: \n");
		print_costs();

		//send to every port
		for(i = 0; i < N; i++){
			if(i == myid-1){
				continue;
			}

		//setup the otheraddr to send
		otheraddr.sin_family = AF_INET;
		otheraddr.sin_port = htons(machines[i].port);
		inet_pton(AF_INET, machines[i].ip, &otheraddr.sin_addr.s_addr);

		data[0] = neighborID-1;
		data[1] = myid-1;
		data[2] = newCost;

		//udp used to send
		sendto(sock, data, sizeof(data), 0, (struct sockaddr *)&otheraddr, addr_size);
		printf("Sent changes to %s  with port %d \n", machines[i].ip, machines[i].port);

		}
	}
}


/**********************
 * run_link_state
 **********************/
// This thread runs the Dijkastra's algorithm on the cost table and calculates the shortest path
void *
run_link_state (void *arg)
{
	int	taken[N];
	int	min, spot;
	int	i, j;
	int	r;

	min = 1000;

	//******STUDENT WORK******

	while(1){

		for(i = 0; i < N; i++){
			distances[i] = costs[myid-1][i];  //take the given distances for the node to start off with
			taken[i] = 0;  //reset to 0 every time
			if(costs[myid-1][i] < min && costs[myid-1][i] != 0){
				min = costs[myid-1][i];
				spot = i;
			}
		}
		distances[myid-1] = 0;  //current location distance to itself is 0
		taken[myid -1] = 1;  //if spot is equal to one then shortest distance already found
		taken[spot] = 0;

		while(1){
			int temp = spot;  //setup the temp location at spot to cycle through every iteration
			min = 1000;
			//printf("One time ");
			//printf("Spot: %d", spot);
			for(j = 0; j < N; j++){
				if(costs[temp][j] + distances[temp] < distances[j]){
					distances[j] = costs[temp][j] + distances[temp]; //update the distances
				}
				if(costs[temp][j] < min && costs[temp][j] != 0 && taken[j] == 0){ //if all these cases are true then we have found next node to iterate through
					min = costs[temp][j];
					taken[j] = 1;
					spot = j;
				}
			}
			if(temp == spot){
				break;
			}
		}

		/*
		for(i = 0; i < myid-1; i++){
			for(j = 0; j < N; j++){
				printf("1   ");
				if(costs[i][j] + distances[i] < distances[j]){
					distances[j] = costs[i][j] + distances[i];
					taken[j] = j;
				}
			}
		}
		printf("\n");
		for(i = myid; i < N; i++){
			for(j = 0; j < N; j++){
				printf("2   ");
				if(costs[i][j] + distances[i] < distances[j]){
					distances[j] = costs[i][j] + distances[i];
					taken[j] = j;
				}
			}
		}
		*/


		printf ("new-shortest distances:\n");
		for (i = 0; i < N; i++)
			printf ("%d ", distances[i]);
		printf ("\n");

		sleep(10);
	}
}


/**********************
 * print costs
 **********************/
void
print_costs (void)
{
	int i, j;

	for (i = 0; i < N; i++)
	{
		for (j = 0; j < N; j++)
		{
			pthread_mutex_lock (&lock);
			printf ("%d ", costs[i][j]);
			pthread_mutex_unlock (&lock);
		}
		printf ("\n");
	}

}
