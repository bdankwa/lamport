/*
 * ReceiveEvent.cpp
 *
 *  Created on: Sep 17, 2016
 *      Author: bdankwa
 */

#include "ReceiveEvent.h"
#include <iostream>
#include "utils.h"

using namespace std;

ReceiveEvent::ReceiveEvent(Comms* comms, LogicalClock* clock, unsigned int proc, unsigned int byztProb) {
	communications = comms;
	process = proc;
	processClock = clock;
	byzatineProb = byztProb;
	timeCreated = processClock->getTime();
}

void ReceiveEvent::execute(){
	int randomNumber;

	Message* inMsg = communications->receive(process);
	randomNumber = generateRandomInt(1, byzatineProb);

	if(randomNumber == byzatineProb/2){
		//Byzantine event
	}
	else{
		processClock->tick();

		if( inMsg->isValid() && (processClock->getTime() <= inMsg->getContent().lclock)){
			processClock->setTime((inMsg->getContent().lclock) + 1);
			//cout << "Process:" << process <<"Advanced my clock"<<endl;
		}
	}
}

unsigned int ReceiveEvent::createdAt(){
	return timeCreated;
}

ReceiveEvent::~ReceiveEvent() {
	// TODO Auto-generated destructor stub
}

