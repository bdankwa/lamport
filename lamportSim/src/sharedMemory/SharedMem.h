/*
 * SharedMem.h
 *
 *  Created on: Sep 18, 2016
 *      Author: bdankwa
 */

#ifndef SHAREDMEM_H_
#define SHAREDMEM_H_

#include "Mailbox.h"

class SharedMem : public Comms{
public:
	SharedMem();
	int send(Message& m, int proc);
	Message receive( int proc);
	virtual ~SharedMem();
private:
	Mailbox* getMailbox(int i);
	std::vector<Mailbox*> mailboxes;
};

#endif /* SHAREDMEM_H_ */
