/*
 * Comms.h
 *
 *  Created on: Sep 17, 2016
 *      Author: bdankwa
 */

#ifndef COMMS_H_
#define COMMS_H_

#include "Message.h"

class Comms {
public:
	virtual int send(Message& m) = 0;
	virtual Message receive() = 0;
};

#endif /* COMMS_H_ */
