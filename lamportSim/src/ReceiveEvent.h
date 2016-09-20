/*
 * ReceiveEvent.h
 *
 *  Created on: Sep 17, 2016
 *      Author: bdankwa
 */

#ifndef RECEIVEEVENT_H_
#define RECEIVEEVENT_H_

#include "Event.h"
#include "Comms.h"

class ReceiveEvent: public Event {
public:
	ReceiveEvent(Comms* comms, LogicalClock* clock, unsigned int proc);
	void execute();
	unsigned int createdAt();
	virtual ~ReceiveEvent();
private:
	Comms* communications;
	unsigned int process;
	LogicalClock* processClock;
	unsigned int timeCreated;
};

#endif /* RECEIVEEVENT_H_ */
