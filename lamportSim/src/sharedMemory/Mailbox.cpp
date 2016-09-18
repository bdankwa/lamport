/*
 * Mailbox.cpp
 *
 *  Created on: Sep 17, 2016
 *      Author: bdankwa
 */

#include "Mailbox.h"

Mailbox::Mailbox() {
	MAILBOX_CAPACITY = 100;
	pthread_mutex_init(&_lock, NULL);

}

int Mailbox::send(Message& m){

	if(_mailbox.size() > MAILBOX_CAPACITY){
		destroyCurrentMessage();
	}
	_mailbox.push(m);

	return 0;
}

Message Mailbox::receive(){

	Message* msg = new Message(); //empty message

	if(!_mailbox.empty()){
		return _mailbox.front();
	}
	else{
		return *msg; // users should test for empty message
	}
}

int Mailbox::numOfMessages(){
	return _mailbox.size();
}

unsigned int Mailbox::getCapacity(){
	return MAILBOX_CAPACITY;
}

void Mailbox::lock(){
	pthread_mutex_lock(&_lock);

}

void Mailbox::unlock(){
	pthread_mutex_unlock(&_lock);
}

void Mailbox::destroyCurrentMessage(){
	_mailbox.pop();
}

Mailbox::~Mailbox() {
	// TODO Auto-generated destructor stub
}

