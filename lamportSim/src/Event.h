/*
 * Event.h
 *
 *  Created on: Sep 17, 2016
 *      Author: bdankwa
 */

#ifndef EVENT_H_
#define EVENT_H_

#include "LogicalClock.h"

class Event {
public:
	virtual void execute() = 0;
	virtual unsigned int createdAt() = 0;
	virtual ~Event(){
		;
	}
};

#endif /* EVENT_H_ */
