/*
 * Internal.h
 *
 *  Created on: Sep 17, 2016
 *      Author: bdankwa
 */

#ifndef INTERNALEVENT_H_
#define INTERNALEVENT_H_

#include "Event.h"

class InternalEvent: public Event {
public:
	InternalEvent(LogicalClock* clock);
	void execute();
	unsigned int createdAt();
	virtual ~InternalEvent();
private:
	unsigned int currentTime;
	LogicalClock* processClock;
};

#endif /* INTERNALEVENT_H_ */
