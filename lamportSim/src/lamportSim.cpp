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

#include "Process.h"
#include "Mailbox.h"

using namespace std;

#define SHM_NAME "shm_post_office"
#define SHM_SIZE (4096)
#define NUM_OF_PROCESSES (4)

int main() {

	int shm_id;
	sharedMailboxes_t* sharedMemory;

	int i;
	int pid;
	int status;

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

	for(i=0; i< NUM_OF_PROCESSES; i++){
		if((pid = fork()) == 0){ // child process

			/* Map shared region to caller's address space*/
			if ((sharedMemory = (sharedMailboxes_t*) mmap(NULL, 4096, PROT_WRITE | PROT_READ,
					MAP_SHARED, shm_id, 0)) == (void *) -1) {
				perror("mmap");
				exit(EXIT_FAILURE);
			}
			// Instantiate process object
			Process* procObj = new Process(i, NUM_OF_PROCESSES, new Mailbox(sharedMemory, i));
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
		else if (pid == -1){ // error
			perror("fork");
			exit(EXIT_FAILURE);
		}
		else{ // parent, go spawn more kids
			//cout << "waited for  process " << i << endl;
			waitpid(pid,&status, WNOHANG);
		}
	}

	return EXIT_SUCCESS;
}
