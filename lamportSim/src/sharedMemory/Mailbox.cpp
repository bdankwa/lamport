/*
 * Mailbox.cpp
 *
 *  Created on: Sep 17, 2016
 *      Author: bdankwa
 */

#include "Mailbox.h"
#include <string.h>
#include <stdio.h>
#include <pthread.h>

#include <iostream>
using namespace std;

Mailbox::Mailbox(sharedMailboxes_t* mboxes, unsigned int proc) {

	mailboxes = mboxes;
	proc_id = proc;

}

int Mailbox::send(Message* m, unsigned int destination){
	int status = 0;

	/**************************************
	 * Begin critical section
	 ***************************************/
	pthread_mutex_lock(&mailboxes->lock);
	status = writeShm(m->getContent(), destination);
	pthread_mutex_unlock(&mailboxes->lock);
	/**************************************
	 * End critical section
	 ***************************************/

	return status;
}

Message* Mailbox::receive(unsigned int src){

	packet_t data;
	data.validityCode = 0;

	/**************************************
	 * Read data from shared memory (own mailbox)
	 ***************************************/
	if(readShm(&data,src) == -1){
		//cout<< "Mailbox:receive - empty buffer - " << proc << endl;
	}
	Message* msg = new Message(data); //empty message

	return msg;

}

int Mailbox::numOfMessages(){
	return 0;
}

unsigned int Mailbox::getCapacity(){
	return MAILBOX_CAPACITY;
}

int Mailbox::writeShm(packet_t data, unsigned int destination){
	//TODO write to shared memory
	//update data structures in shared memory
	unsigned int index = 0;
	unsigned int head;
	//unsigned int tail;

	head = mailboxes->head[destination];
	/*tail = mailboxes->tail[destination];

	if((head - tail) == MAILBOX_CAPACITY){
		return -1; // buffer full
	}*/

	/************************************************************
	 * Keep on writing even if mailbox is full,
	 * new messages has most current clock value
	 * and has higher priority.
	 ************************************************************/
	index = head % MAILBOX_CAPACITY;
	(mailboxes->messages + (destination * MAILBOX_CAPACITY))[index] = data;

	mailboxes->head[destination]++;

	return 0;
}

int Mailbox::readShm(packet_t* data, unsigned int source){
	unsigned int index = 0;
	unsigned int head;
	unsigned int tail;

	head = mailboxes->head[source];
	tail = mailboxes->tail[source];

	/************************************************************
	 * Read from shared memory (own mailbox),
	 * stop when buffer is empty.
	 ************************************************************/
	if((head - tail) == 0){
		return -1; // empty buffer
	}

	index = tail % MAILBOX_CAPACITY;
	*data = *(mailboxes->messages + (source * MAILBOX_CAPACITY) + index);

	mailboxes->tail[source]++;

	return 0;
}

Mailbox::~Mailbox() {
	// TODO Auto-generated destructor stub
}

