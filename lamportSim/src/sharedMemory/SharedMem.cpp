/*
 * SharedMem.cpp
 *
 *  Created on: Sep 18, 2016
 *      Author: bdankwa
 */

#include "SharedMem.h"

#define NUM_OF_MAILBOXES (4)

SharedMem::SharedMem() {

	int i;
	for(i=0; i<NUM_OF_MAILBOXES; i++){
		mailboxes[i] = new Mailbox();
	}
}

int SharedMem::send(Message& m, int proc){

	Mailbox mailbox;
	if((mailbox = getMailbox(proc)) != NULL){
		return mailbox.send(m);
	}

	return -1;

}
Message SharedMem::receive( int proc){

}

Mailbox* SharedMem::getMailbox(int i){
	return mailboxes[i];
}

SharedMem::~SharedMem() {
	// TODO Auto-generated destructor stub
}

