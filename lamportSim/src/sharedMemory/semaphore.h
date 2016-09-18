/*
 ============================================================================
 Name        : semaphore.h
 Author      : Boakye Dankwa
 Version     :
 Course      : CSCI503 Operating Systems
 Project	 : Project 3
 Description : Implementation of semaphore for thread synchronization
 ============================================================================
 */

#ifndef SEMAPHORE_H_
#define SEMAPHORE_H_

#include <pthread.h>
/*********************************
 * Data structure for semaphore
 *********************************/
typedef struct{
	int value, guard; // semaphore value and guard
	pthread_mutex_t mutex; // mutex
	pthread_cond_t cv; // condition variable
} semaphore_t;

/******************************************************************************
* Function name: semInit
* Parameters:
* 	S - Semaphore
* 	value - Initial value of semaphore
* Return: None.
*
* Description: This function initializes a semaphore.
*******************************************************************************/
void semInit(semaphore_t* S, int value);

/******************************************************************************
* Function name: P
* Parameters:
* 	S - Semaphore
* Return: None.
*
* Description: This function decrements a semaphore.
*******************************************************************************/
void P(semaphore_t* S);

/******************************************************************************
* Function name: V
* Parameters:
* 	S - Semaphore
* Return: None.
*
* Description: This function increments a semaphore.
*******************************************************************************/
void V(semaphore_t* S);

/******************************************************************************
* Function name: semBroadcast
* Parameters:
* 	S - Semaphore
* Return: None.
*
* Description: This function sets a condition variables for all threads waiting
* on semaphore S.
*******************************************************************************/
void semBroadcast(semaphore_t* S);

int getSemValue(semaphore_t* S);

#endif /* SEMAPHORE_H_ */
