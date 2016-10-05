/*
 * SendEvent.h
 *
 *  Created on: Sep 17, 2016
 *      Author: bdankwa
 */

#ifndef SENDEVENT_H_
#define SENDEVENT_H_

#include "Event.h"
#include "Comms.h"

class SendEvent: public Event {
public:
	SendEvent(Comms* comms, unsigned int dest, LogicalClock* clock);
	void execute();
	unsigned int createdAt();
	virtual ~SendEvent();
private:
	unsigned int timeCreated;
	Comms* communications;
	unsigned int destination;
	LogicalClock* processClock;
};

#endif /* SENDEVENT_H_ */
