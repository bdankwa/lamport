/*
 * ReceiveEvent.h
 *
 *  Created on: Sep 17, 2016
 *      Author: bdankwa
 */

#ifndef RECEIVEEVENT_H_
#define RECEIVEEVENT_H_

#include "Event.h"

class ReceiveEvent: public Event {
public:
	ReceiveEvent();
	virtual ~ReceiveEvent();
};

#endif /* RECEIVEEVENT_H_ */
