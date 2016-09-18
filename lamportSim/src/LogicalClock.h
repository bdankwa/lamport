/*
 * LogicalClock.h
 *
 *  Created on: Sep 17, 2016
 *      Author: bdankwa
 */

#ifndef LOGICALCLOCK_H_
#define LOGICALCLOCK_H_

class LogicalClock {
public:
	LogicalClock();
	unsigned int getTime();
	void reset();
	virtual ~LogicalClock();
private:
	static unsigned int time;
};

#endif /* LOGICALCLOCK_H_ */
