/*
 * Mailbox.cpp
 *
 *  Created on: Sep 17, 2016
 *      Author: bdankwa
 */

#include "Mailbox.h"
#include <string.h>
#include <stdio.h>

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

}

int Mailbox::send(Message* m, unsigned int proc){
	int status = 0;

	P(&mailboxes->lock);
	//pthread_mutex_lock(&mailboxes->locks);
	status = writeShm(m->getContent(), proc);
	//pthread_mutex_unlock(&mailboxes->locks);
	V(&mailboxes->lock);

	return status;
}

Message* Mailbox::receive(unsigned int proc){

	packet_t data;
	data.isValid = 0;

	P(&mailboxes->lock);
	//pthread_mutex_lock(&mailboxes->locks);
	if(readShm(&data,proc) == -1){
		cout<< "Mailbox:receive - empty buffer" << endl;
	}
	//pthread_mutex_unlock(&mailboxes->locks);
	V(&mailboxes->lock);

	Message* msg = new Message(data); //empty message

	return msg;

}

int Mailbox::numOfMessages(){
	return 0;
}

unsigned int Mailbox::getCapacity(){
	return MAILBOX_CAPACITY;
}

int Mailbox::writeShm(packet_t data, unsigned int proc){
	//TODO write to shared memory
	//update data structures in shared memory
	unsigned int index = 0;
	unsigned int head;
	unsigned int tail;

	head = mailboxes->head[proc];
	tail = mailboxes->tail[proc];

	if((head - tail) == MAILBOX_CAPACITY){
		return -1; // buffer full
	}

	index = head % MAILBOX_CAPACITY;
	//*(mailboxes->messages + (proc * MAILBOX_CAPACITY) + index) = data;

	mailboxes->head[proc]++;

	//cout<< "writeShm:head = " << mailboxes->head[proc] << " proc: " << proc  << endl;

	return 0;
}

int Mailbox::readShm(packet_t* data, unsigned int proc){
	unsigned int index = 0;
	unsigned int head;
	unsigned int tail;

	head = mailboxes->head[proc];
	tail = mailboxes->tail[proc];

	if((head - tail) == 0){
		return -1; // empty buffer
	}

	index = tail % MAILBOX_CAPACITY;
	*data = *(mailboxes->messages + (proc * MAILBOX_CAPACITY) + index);

	mailboxes->tail[proc]++;

	//cout<< "readShm:lclock = " << data->lclock << endl;

	return 0;
}

Mailbox::~Mailbox() {
	// TODO Auto-generated destructor stub
}

