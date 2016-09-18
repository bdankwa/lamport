/*
 * Mailbox.cpp
 *
 *  Created on: Sep 17, 2016
 *      Author: bdankwa
 */

#include "Mailbox.h"

Mailbox::Mailbox() {
	// TODO Auto-generated constructor stub
	pthread_mutex_init(&_lock, NULL);

}

int Mailbox::send(Message& m){

	_mailbox.push(m);

	return 0;
}

Message Mailbox:: receive(){

	Message* msg = new Message(); //empty message

	if(!_mailbox.empty()){
		return _mailbox.front();
	}
	else{
		return *msg; // users should test for empty message
	}
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

