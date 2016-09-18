/*
 * Mailbox.h
 *
 *  Created on: Sep 17, 2016
 *      Author: bdankwa
 */

#ifndef MAILBOX_H_
#define MAILBOX_H_

#include "Comms.h"
#include <queue>
#include <pthread.h>

class Mailbox: public Comms {
public:
	Mailbox();
	int send(Message& m);
	Message receive();
	virtual ~Mailbox();
	void lock();
	void unlock();
	void destroyCurrentMessage();

private:
	std::queue<Message> _mailbox;
	pthread_mutex_t _lock; // mutex
};

#endif /* MAILBOX_H_ */
