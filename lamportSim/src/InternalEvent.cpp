/*
 * InternalEvent.cpp
 *
 *  Created on: Sep 17, 2016
 *      Author: bdankwa
 */

#include "InternalEvent.h"

InternalEvent::InternalEvent() {
	LogicalClock* clock = new LogicalClock();
	timeCreated = clock->getTime();
}

void InternalEvent::execute(){
	//Do nothing for internal event

}

unsigned int InternalEvent::createdAt(){
	return timeCreated;

}

InternalEvent::~InternalEvent() {}

