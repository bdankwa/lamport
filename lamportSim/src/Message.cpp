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
}

Message::Message(packet_t data) {
	// TODO Auto-generated constructor stub
	this->data = data;
	dataSize = sizeof(unsigned int);
}

packet_t Message::getContent(){

	return data;
}

int Message::size() {

	return dataSize;
}

Message::~Message() {
	// TODO Auto-generated destructor stub
}

