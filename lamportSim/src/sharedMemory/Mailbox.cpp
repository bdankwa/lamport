/*
 * Mailbox.cpp
 *
 *  Created on: Sep 17, 2016
 *      Author: bdankwa
 */

#include "Mailbox.h"

Mailbox::Mailbox(sharedMailboxes_t* mboxes, unsigned int proc) {

	mailboxes = mboxes;
	MAILBOX_CAPACITY = 100;

	pthread_mutex_init(mailboxes->locks + proc, NULL);

}

int Mailbox::send(Message& m, unsigned int proc){
	int status = 0;

	pthread_mutex_lock(mailboxes->locks + proc);
	status = send(m.getContent(), proc);
	pthread_mutex_unlock(mailboxes->locks + proc);

	return status;
}

Message Mailbox::receive(unsigned int proc){

	packet_t data;

	pthread_mutex_lock(mailboxes->locks + proc);
	data = rcv(proc);
	pthread_mutex_unlock(mailboxes->locks + proc);

	Message* msg = new Message(); //empty message

	return *msg; // users should test for empty message

}

int Mailbox::numOfMessages(){
	return 0;
}

unsigned int Mailbox::getCapacity(){
	return MAILBOX_CAPACITY;
}

int Mailbox::send(packet_t data, unsigned int proc){
	//TODO write to shared memory
	//update data structures in shared memory


	return 0;
}

packet_t Mailbox::rcv( unsigned int proc){

	packet_t data;

	return data;

}

Mailbox::~Mailbox() {
	// TODO Auto-generated destructor stub
}

