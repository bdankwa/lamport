/*
 * Message.cpp
 *
 *  Created on: Sep 17, 2016
 *      Author: bdankwa
 */

#include "Message.h"

#define VALID_DATA (0xDEADBEEF)

Message::Message() {
	// TODO Auto-generated constructor stub
	dataSize = 0;
	data.lclock = 0;
	data.validityCode = 0;
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
		data.validityCode = VALID_DATA;
	}
	else{
		data.validityCode = 0;
	}

}

bool Message::isValid(){

	if(data.validityCode == VALID_DATA){
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

