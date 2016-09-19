/*
 * Message.h
 *
 *  Created on: Sep 17, 2016
 *      Author: bdankwa
 */

#ifndef MESSAGE_H_
#define MESSAGE_H_

typedef struct {
	unsigned int lclock;
	unsigned int payload[10];
}packet_t;

class Message {
public:
	Message();
	Message(packet_t);
	int size();
	packet_t getContent();
	virtual ~Message();
private:
	packet_t data;
	int dataSize; //size of message in bytes
};

#endif /* MESSAGE_H_ */
