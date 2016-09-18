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
#include "semaphore.h"

#define MAILBOX_CAPACITY (100)
#define NUM_PROC (4)


/*typedef struct {
	unsigned int lclock;
	unsigned int payload[10];
}packet_t;*/

typedef struct{
	semaphore_t lock;
	unsigned int head[NUM_PROC];
	unsigned int tail[NUM_PROC];
	packet_t messages[NUM_PROC * MAILBOX_CAPACITY];
}sharedMailboxes_t;

class Mailbox : public Comms{
public:
	Mailbox(sharedMailboxes_t* mailboxes, unsigned int proc);
	int send(Message* m, unsigned int proc);
	Message* receive(unsigned int proc);
	virtual ~Mailbox();
	int numOfMessages();
	unsigned int getCapacity();
private:
	sharedMailboxes_t* mailboxes;
	int writeShm(packet_t data, unsigned int);
	int readShm(packet_t* data, unsigned int);
};

#endif /* MAILBOX_H_ */
