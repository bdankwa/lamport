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

#define NUM_OF_ITERATIONS (100)
#define NUM_OF_PROC (4)

Process::Process(int id, int nid, Comms* comms, unsigned int Eventprob, unsigned int byzantineProb) {

	clock = new LogicalClock();
	proc_id = id;
	num_processes = nid;
	communications = comms;
	eventProb = Eventprob;
	byztProb = byzantineProb;
	sprintf(logFile, "process_%i",id);
}

void Process::run() {
	int i;
	int randomNumber;
	Event* rcvEvent = NULL;
	Event* randomEvent = NULL;

	//cout << "Process: " << proc_id << endl;

	for(i=0; i<NUM_OF_ITERATIONS; i++){

		randomNumber = generateRandomInt(1, 10);

		if(randomNumber == 5){

		}
		else{
			rcvEvent = new ReceiveEvent(communications, clock, proc_id);
			if(rcvEvent != NULL){
				rcvEvent->execute();
			}
		}

		randomEvent = createRandomEvent();
		if(randomEvent != NULL){
			randomEvent->execute();
		}

		writeToFile(logFile, proc_id, i, ((float)eventProb/10.0), ((float)byztProb/10.0), clock->getTime());



		/*Message* outMsg = new Message();
		outMsg->setCreatedTime(randomEvent->createdAt());*/


		/*if(proc_id != 0){
			randomEvent->execute();
			//communications->send(outMsg, 0);
		}
		else{
		    sleep(1);
			inMsg = communications->receive(0);
			cout<< "process: "<< proc_id << " internal Event time: " << inMsg->getContent().lclock << endl;
		} */

		/*if(rcvEvent != NULL){
			delete rcvEvent;
		}
		if(randomEvent != NULL){
			delete randomEvent;
		}*/

	}
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
		if(selection == 10){
			event = new SendEvent(communications, randomDestination, clock);
		}
		break;
	case 2 : // 0.2 probability
		if(selection <= 2){
			event = new InternalEvent(clock);
		}
		if(selection >= 9){
			event = new SendEvent(communications, randomDestination, clock);
		}
		break;
	case 3: // 0.3 probability
		if(selection <= 3){
			event =  new InternalEvent(clock);
		}
		if(selection >= 8){
			event =  new SendEvent(communications, randomDestination, clock);
		}
		break;
	case 4: // 0.4 probability
		if(selection <= 4){
			event =  new InternalEvent(clock);
		}
		if(selection >= 7){
			event =  new SendEvent(communications, randomDestination, clock);
		}
		break;
	case 5: // 0.5 probability
		if(selection <= 5){
			event =  new InternalEvent(clock);
		}
		if(selection >= 6){
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

