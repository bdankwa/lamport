/*
 * ReceiveEvent.cpp
 *
 *  Created on: Sep 17, 2016
 *      Author: bdankwa
 */

#include "ReceiveEvent.h"

ReceiveEvent::ReceiveEvent(Comms* comms, LogicalClock* clock, unsigned int proc) {
	communications = comms;
	process = proc;
	processClock = clock;
	timeCreated = processClock->getTime();
}

void ReceiveEvent::execute(){
	processClock->tick();
	Message* inMsg = communications->receive(process);
	if( inMsg->isValid() && (processClock->getTime() <= inMsg->getContent().lclock)){
		processClock->setTime((inMsg->getContent().lclock) + 1);
	}
}

unsigned int ReceiveEvent::createdAt(){
	return timeCreated;
}

ReceiveEvent::~ReceiveEvent() {
	// TODO Auto-generated destructor stub
}

