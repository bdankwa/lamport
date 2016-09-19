/*
 * Process.cpp
 *
 *  Created on: Sep 17, 2016
 *      Author: bdankwa
 */

#include "Process.h"
#include <iostream>

using namespace std;

Process::Process(int id, int nid, Comms* comms) {

	proc_id = id;
	num_processes = nid;
	communications = comms;
}

void Process::run() {

	cout << "Process: " << proc_id << endl;

	Message* outMsg = new Message();
	Message* inMsg;

	if(proc_id != 0){
		communications->send(outMsg, 0);
	}
	else{
		inMsg = communications->receive(0);
		cout<< "lclock for proc "<< proc_id << " is " << inMsg->getContent().lclock << endl;
	}




}

Process::~Process() {
	// TODO Auto-generated destructor stub
}

