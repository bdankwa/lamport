/*
 * Process.cpp
 *
 *  Created on: Sep 17, 2016
 *      Author: bdankwa
 */

#include "Process.h"
#include <iostream>
#include <unistd.h>

#include "InternalEvent.h"

using namespace std;

#define NUM_OF_ITERATIONS (5)

Process::Process(int id, int nid, Comms* comms) {

	proc_id = id;
	num_processes = nid;
	communications = comms;
}

void Process::run() {
	int i;

	//cout << "Process: " << proc_id << endl;

	for(i=0; i<NUM_OF_ITERATIONS; i++){

		Event* someEvent = new InternalEvent();

		Message* outMsg = new Message();
		outMsg->setCreatedTime(someEvent->createdAt());

		Message* inMsg;

		if(proc_id != 0){
			communications->send(outMsg, 0);
		}
		else{
		    sleep(1);
			inMsg = communications->receive(0);
			cout<< "process: "<< proc_id << " internal Event time: " << inMsg->getContent().lclock << endl;
		}

		delete outMsg;
		delete someEvent;

	}





}

Process::~Process() {
	// TODO Auto-generated destructor stub
}

