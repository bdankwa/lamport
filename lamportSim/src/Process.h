/*
 * Process.h
 *
 *  Created on: Sep 17, 2016
 *      Author: bdankwa
 */

#ifndef PROCESS_H_
#define PROCESS_H_

#include "Comms.h"
#include "Event.h"

typedef struct{
	unsigned int iterations;
	unsigned int eventProb;
	unsigned int byzntProb;
}procGlobalData_t;

class Process {
public:
	Process(int id, int nid, Comms* comms, procGlobalData_t* data);
	void run();
	virtual ~Process();
private:
	LogicalClock* clock;
	unsigned int proc_id;
	int num_processes;
	unsigned int eventProb;
	unsigned int byztProb;
	unsigned int iterations;
	char logFile[10];
	Comms* communications;
	Event* createRandomEvent();
};

#endif /* PROCESS_H_ */
