/*
 * SendEvent.cpp
 *
 *  Created on: Sep 17, 2016
 *      Author: bdankwa
 */

#include "SendEvent.h"
#include "Message.h"

SendEvent::SendEvent(Comms* comms, unsigned int dest, LogicalClock* clock) {
	processClock = clock;
	communications = comms;
	destination = dest;
	timeCreated = processClock->getTime();
}

void SendEvent::execute(){
	/************************************************
	 * Create a message, write current clock value and
	 * send to destination.
	 ************************************************/
	Message* outMsg = new Message();
	processClock->tick();
	outMsg->setCreatedTime(processClock->getTime());
	outMsg->setValid(true);
	communications->send(outMsg, destination);

}

unsigned int SendEvent::createdAt(){
	return timeCreated;
}

SendEvent::~SendEvent() {
	// TODO Auto-generated destructor stub
}

