/*
 * InternalEvent.cpp
 *
 *  Created on: Sep 17, 2016
 *      Author: bdankwa
 */

#include "InternalEvent.h"

InternalEvent::InternalEvent(LogicalClock* clock) {
	processClock = clock;
	currentTime = 0;
}

void InternalEvent::execute(){
	/**********************************
	 * Internal event - only advance clock
	 *************************************/
	processClock->tick();
	currentTime = processClock->getTime();

}

unsigned int InternalEvent::createdAt(){
	return currentTime;

}

InternalEvent::~InternalEvent() {}

