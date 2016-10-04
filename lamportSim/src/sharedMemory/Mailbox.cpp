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

	/*if(pthread_mutex_init(&mailboxes->locks, NULL) != 0){
		perror("pthread_mutex_init");
	}

	if(pthread_mutex_lock(mailboxes->locks + proc) != 0){
		perror("pthread_mutex_lock");
	}

	mailboxes->head[proc] = 0;
	mailboxes->tail[proc] = 0;
	if(memset((mailboxes->messages + (proc * MAILBOX_CAPACITY)) ,0, sizeof(packet_t)*MAILBOX_CAPACITY) == NULL){
		perror("memset error");
	}

	if(pthread_mutex_unlock(mailboxes->locks + proc) != 0){
		perror("pthread_mutex_unlock");
	} */
	proc_id = proc;

}

int Mailbox::send(Message* m, unsigned int destination){
	int status = 0;

	//P(&mailboxes->lock);
	//cout<< "Process-"<< proc_id << "locking for write." << endl;
	pthread_mutex_lock(&mailboxes->lock);
	status = writeShm(m->getContent(), destination);
	pthread_mutex_unlock(&mailboxes->lock);
	//cout<< "Process-"<< proc_id << "unlocking write." << endl;
	//V(&mailboxes->lock);

	return status;
}

Message* Mailbox::receive(unsigned int src){

	packet_t data;
	data.validityCode = 0;

	//P(&mailboxes->lock);
	//cout<< "Process-"<< proc_id << "locking for read." << endl;
	//pthread_mutex_lock(&mailboxes->lock);
	if(readShm(&data,src) == -1){
		//cout<< "Mailbox:receive - empty buffer - " << proc << endl;
	}
	//pthread_mutex_unlock(&mailboxes->lock);
	//cout<< "Process-"<< proc_id << "unlocking read." << endl;
	//V(&mailboxes->lock);

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
	unsigned int tail;

	head = mailboxes->head[destination];
	tail = mailboxes->tail[destination];

	/*if((head - tail) == MAILBOX_CAPACITY){
		return -1; // buffer full
	}*/

	index = head % MAILBOX_CAPACITY;
	(mailboxes->messages + (destination * MAILBOX_CAPACITY))[index] = data;

	mailboxes->head[destination]++;

	//cout<< "writeShm:head = " << mailboxes->head[proc] << " proc: " << proc  << endl;

	return 0;
}

int Mailbox::readShm(packet_t* data, unsigned int source){
	unsigned int index = 0;
	unsigned int head;
	unsigned int tail;

	head = mailboxes->head[source];
	tail = mailboxes->tail[source];

	if((head - tail) == 0){
		return -1; // empty buffer
	}

	index = tail % MAILBOX_CAPACITY;
	*data = *(mailboxes->messages + (source * MAILBOX_CAPACITY) + index);

	mailboxes->tail[source]++;

	//cout<< "readShm:lclock = " << data->lclock << endl;

	return 0;
}

Mailbox::~Mailbox() {
	// TODO Auto-generated destructor stub
}

