/*
 * Process.cpp
 *
 *  Created on: Sep 17, 2016
 *      Author: bdankwa
 */

#include "Process.h"
#include <iostream>
#include <unistd.h>
#include <stdio.h>

#include "InternalEvent.h"
#include "SendEvent.h"
#include "ReceiveEvent.h"
#include "utils.h"

using namespace std;

//#define NUM_OF_ITERATIONS (10000)
#define NUM_OF_PROC (4)

Process::Process(int id, int nid, Comms* comms, procGlobalData_t* data) {

	clock = new LogicalClock();
	proc_id = id;
	num_processes = nid;
	communications = comms;
	iterations = data->iterations; //args[0];
	eventProb = data->eventProb; //args[1];
	byztProb = data->byzntProb; //args[2];

	sprintf(logFile, "process_%i",id);
}

void Process::run() {
	int i;
	//int randomNumber;
	Event* rcvEvent = NULL;
	Event* randomEvent = NULL;
	static unsigned int prev_time = 0;
	FILE* fd;

	if((fd = fopen(logFile, "a")) == NULL){
		perror("Cannot open output file \n");
		exit(EXIT_FAILURE);
	}

	//cout << "Process: " << proc_id << endl;

	for(i=0; i<iterations; i++){

		/*randomNumber = generateRandomInt(1, byztProb);

		if(randomNumber == byztProb/2){
			//Byzantine event
		}
		else{
			rcvEvent = new ReceiveEvent(communications, clock, proc_id);
			if(rcvEvent != NULL){
				rcvEvent->execute();
			}
		}*/
		rcvEvent = new ReceiveEvent(communications, clock, proc_id, byztProb);
		if(rcvEvent != NULL){
			rcvEvent->execute();
		}

		randomEvent = createRandomEvent();
		if(randomEvent != NULL){
			randomEvent->execute();
		}

		/*writeToFile(logFile, proc_id, i, (eventProb/10.0), (1.0/byztProb),
				clock->getTime(), (clock->getTime() - prev_time));*/

		fprintf(fd,"%i\t%i\t%f\t%f\t%i\t%i\n",proc_id, i, (eventProb/10.0), (1.0/byztProb),
				clock->getTime(), (clock->getTime() - prev_time));

		prev_time = clock->getTime();

	}

	fclose(fd);
}

Event* Process::createRandomEvent() {

	Event* event = NULL;

	int selection = generateRandomInt(1, 10);
	unsigned int randomDestination = generateRandomInt(0, NUM_OF_PROC-1);

	switch (eventProb) {
	case 1 : // 0.1 probability
		if(selection == 1){
			event = new InternalEvent(clock);
		}
		if(selection == 10 && proc_id != randomDestination){
			event = new SendEvent(communications, randomDestination, clock);
		}
		break;
	case 2 : // 0.2 probability
		if(selection <= 2){
			event = new InternalEvent(clock);
		}
		if(selection >= 9 && proc_id != randomDestination){
			event = new SendEvent(communications, randomDestination, clock);
		}
		break;
	case 3: // 0.3 probability
		if(selection <= 3){
			event =  new InternalEvent(clock);
		}
		if(selection >= 8 && proc_id != randomDestination){
			event =  new SendEvent(communications, randomDestination, clock);
		}
		break;
	case 4: // 0.4 probability
		if(selection <= 4){
			event =  new InternalEvent(clock);
		}
		if(selection >= 7 && proc_id != randomDestination){
			event =  new SendEvent(communications, randomDestination, clock);
		}
		break;
	case 5: // 0.5 probability
		if(selection <= 5){
			event =  new InternalEvent(clock);
		}
		if(selection >= 6 && proc_id != randomDestination){
			event =  new SendEvent(communications, randomDestination, clock);
		}
		break;
	default:
		event = NULL;
		break;
	}

	return event;
}

Process::~Process() {
	// TODO Auto-generated destructor stub
}

