/*
 * SendEvent.cpp
 *
 *  Created on: Sep 17, 2016
 *      Author: bdankwa
 */

#include "SendEvent.h"
#include "Message.h"

SendEvent::SendEvent(Comms* comms, unsigned int proc, LogicalClock* clock) {
	processClock = clock;
	communications = comms;
	process = proc;
	timeCreated = processClock->getTime();
}

void SendEvent::execute(){
	Message* outMsg = new Message();
	processClock->tick();
	outMsg->setCreatedTime(processClock->getTime());
	outMsg->setValid(true);
	communications->send(outMsg, process);

}

unsigned int SendEvent::createdAt(){
	return timeCreated;
}

SendEvent::~SendEvent() {
	// TODO Auto-generated destructor stub
}

