/*
 * Message.cpp
 *
 *  Created on: Sep 17, 2016
 *      Author: bdankwa
 */

#include "Message.h"

Message::Message() {
	// TODO Auto-generated constructor stub
	dataSize = 0;
	data.lclock = 0;
	data.isValid = 0;
}

Message::Message(packet_t data) {
	// TODO Auto-generated constructor stub
	this->data = data;
	dataSize = sizeof(data);
}

packet_t Message::getContent(){

	return data;
}

void Message::setValid(bool setValid){
	if(setValid){
		data.isValid = 1;
	}

}

bool Message::isValid(){

	if(data.isValid){
		return true;
	}
	else{
		return false;
	}
}

void Message::setCreatedTime(unsigned int time){

	data.lclock = time;
}

int Message::size() {

	return dataSize;
}

Message::~Message() {
	// TODO Auto-generated destructor stub
}

