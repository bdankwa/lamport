/*
 * Mailbox.h
 *
 *  Created on: Sep 17, 2016
 *      Author: bdankwa
 */

#ifndef MAILBOX_H_
#define MAILBOX_H_

#include <queue>
#include <pthread.h>

#include "Comms.h"
#include "Message.h"


/*typedef struct {
	unsigned int lclock;
	unsigned int payload[10];
}packet_t;*/

typedef struct{
	pthread_mutex_t locks[4];
	unsigned int head[4];
	unsigned int tail[4];
	packet_t message[4];
}sharedMailboxes_t;

class Mailbox : public Comms{
public:
	Mailbox(sharedMailboxes_t* mailboxes, unsigned int proc);
	int send(Message& m, unsigned int proc);
	Message receive(unsigned int proc);
	virtual ~Mailbox();
	int numOfMessages();
	unsigned int getCapacity();
private:
	sharedMailboxes_t* mailboxes;
	int send(packet_t data, unsigned int);
	packet_t rcv(unsigned int);
	unsigned int MAILBOX_CAPACITY;
};

#endif /* MAILBOX_H_ */
