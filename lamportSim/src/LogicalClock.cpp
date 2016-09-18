/*
 * LogicalClock.cpp
 *
 *  Created on: Sep 17, 2016
 *      Author: bdankwa
 */

#include "LogicalClock.h"

unsigned int LogicalClock::time = 0;

LogicalClock::LogicalClock() {}

unsigned int LogicalClock::getTime(){
	return time++;
}

void LogicalClock::reset(){
	time = 0;
}

LogicalClock::~LogicalClock() {}

