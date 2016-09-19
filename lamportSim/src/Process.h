/*
 * Process.h
 *
 *  Created on: Sep 17, 2016
 *      Author: bdankwa
 */

#ifndef PROCESS_H_
#define PROCESS_H_

#include "Comms.h"

class Process {
public:
	Process(int id, int nid, Comms* comms);
	void run();
	virtual ~Process();
private:
	int proc_id;
	int num_processes;
	Comms* communications;
};

#endif /* PROCESS_H_ */
