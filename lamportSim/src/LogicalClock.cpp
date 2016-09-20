/*
 * LogicalClock.cpp
 *
 *  Created on: Sep 17, 2016
 *      Author: bdankwa
 */

#include "LogicalClock.h"

unsigned int LogicalClock::time = 0;

LogicalClock::LogicalClock() {
	time = 0;
}

void LogicalClock::tick(){
    time++;
}

void LogicalClock::setTime(unsigned int t){
	time = t;
}

unsigned int LogicalClock::getTime(){
	return time;
}

void LogicalClock::reset(){
	time = 0;
}

LogicalClock::~LogicalClock() {}

