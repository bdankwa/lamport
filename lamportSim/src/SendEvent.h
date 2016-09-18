/*
 * SendEvent.h
 *
 *  Created on: Sep 17, 2016
 *      Author: bdankwa
 */

#ifndef SENDEVENT_H_
#define SENDEVENT_H_

#include "Event.h"

class SendEvent: public Event {
public:
	SendEvent();
	virtual ~SendEvent();
};

#endif /* SENDEVENT_H_ */
