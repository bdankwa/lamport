//============================================================================
// Name        : lamportSim.cpp
// Author      : Boakye Dankwa
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

#include "Process.h"
#include "Mailbox.h"
#include "utils.h"

using namespace std;

#define SHM_NAME "shm_post_office"
#define SHM_SIZE (4096)
#define NUM_OF_PROCESSES (4)

/******************************************************************************
* Function name: 	printUsage
* Parameters: 		None
* Return: 			None
*
* Description: Prints program help information
*******************************************************************************/
void printUsage(void){
	fprintf(stderr, "Usage: ./lmptSim NumOfIterations EventProb ByzantimeProb \n");
	fprintf(stderr, "       NumOfIterations : Number of iterations \n");
	fprintf(stderr, "       EventProb 	: Internal or Send event probability (1=0.1, 2=0.2, 3=0.3, 4=0.4, 5=0.5) \n");
	fprintf(stderr, "       ByzantimeProb   : Probability for Byzantine  failures (1=1, 10=0.1, 100=0.01, 1000=0.001, 10000=0.0001 \n");
}

/******************************************************************************
* Function name: 	validateInput
* Parameters: argc, argv
* 	args - pointer to validated inputs.
*
* Return: 			None
* Description: This function validates command line arguments.
*******************************************************************************/
void validateInput(int argc, char** argv, unsigned int* args){
	int i, j, arg;
	char cmdArg[3];


	if(argc != 4){
		handle_error("validateInput: number of arguments must be 3.\n");
	}

	for(i=1; i<= 3; i++){
		strcpy(cmdArg, argv[i]);
		for(j=0; j < strlen(cmdArg); j++){
			if(!isdigit(cmdArg[j])){
				handle_error("validateInput: arguments must be positive integers. \n");
			}
		}
		if(sscanf(argv[i], "%u", &arg) == 0){
			handle_error("validateInput: arguments must be integers. \n");
		}
		if((i == 2) && (arg != 1 && arg != 2 && arg != 3 && arg != 4 && arg != 5)){

			handle_error("validateInput: 2nd argument must be 1, 2, 3, 4 or 5. \n");
		}
		if((i == 3) && (arg != 1 && arg != 10 && arg != 100 && arg != 1000 && arg != 10000)){

			handle_error("validateInput: 3rd argument must be 1, 10, 100, 1000 or 10000 \n");
		}
		args[i-1] = arg;
	}
}

int main(int argc, char** argv) {

	int shm_id;
	sharedMailboxes_t* sharedMemory;
	//semaphore_t lock;
	pthread_mutex_t lock;

	int i;
	int pids[NUM_OF_PROCESSES];
	int status;
	unsigned int arguments[NUM_OF_PROCESSES];

	validateInput(argc, argv, arguments);

	/* create a shared memory region*/
	if((shm_id = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666)) == -1) {
		perror("shm_open");
		exit(EXIT_FAILURE);
	}

	/* truncate size of shared region to size 4k */
	if (ftruncate(shm_id, SHM_SIZE) == -1) {
		perror("ftruncate");
		exit(EXIT_FAILURE);
	}

	/* Map shared region to caller's address space*/
	if ((sharedMemory = (sharedMailboxes_t*) mmap(NULL, 4096, PROT_WRITE | PROT_READ,
			MAP_SHARED, shm_id, 0)) == (void *) -1) {
		perror("mmap");
		exit(EXIT_FAILURE);
	}

	//semInit(&lock, 1);
	sharedMemory->lock = lock;

	for(i=0; i< NUM_OF_PROCESSES; i++){
		if((pids[i] = fork()) == 0){ // child process

			/* Map shared region to caller's address space*/
			if ((sharedMemory = (sharedMailboxes_t*) mmap(NULL, 4096, PROT_WRITE | PROT_READ,
					MAP_SHARED, shm_id, 0)) == (void *) -1) {
				perror("mmap");
				exit(EXIT_FAILURE);
			}
			// Instantiate process object
			Process* procObj = new Process(i, NUM_OF_PROCESSES, new Mailbox(sharedMemory, i), arguments);
			//start processing events
			procObj->run();

			/* Unmap shared region from caller's address space*/
			if(munmap(sharedMemory, SHM_SIZE) == -1) {
				perror("munmap");
			}
			/*****Unlink shared memory *******/
			shm_unlink(SHM_NAME);

			exit(EXIT_SUCCESS);
		}
		else if (pids[i] == -1){ // error
			perror("fork");
			exit(EXIT_FAILURE);
		}
		else{
			;
		}
	}

	for(i=0; i< NUM_OF_PROCESSES; i++){
	    while (-1 == waitpid(pids[i], &status, 0));
	    cout << "Waited on: "<< i << endl;
	    if (!WIFEXITED(status) || WEXITSTATUS(status) != 0) {
	        cerr << "Process " << i << " (pid " << pids[i] << ") failed" << endl;
	        exit(1);
	    }
	}


	return EXIT_SUCCESS;
}
