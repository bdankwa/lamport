/*
 * Message.h
 *
 *  Created on: Sep 17, 2016
 *      Author: bdankwa
 */

#ifndef MESSAGE_H_
#define MESSAGE_H_


class Message {
public:
	Message();
	Message(unsigned int);
	int size();
	virtual ~Message();
private:
	unsigned int data;
	int dataSize; //size of message in bytes
};

#endif /* MESSAGE_H_ */
