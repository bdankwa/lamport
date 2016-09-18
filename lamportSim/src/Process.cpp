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
}

void Process::run() {

	cout << "Process: " << proc_id << " num_proc: " << num_processes << endl;


}

Process::~Process() {
	// TODO Auto-generated destructor stub
}

