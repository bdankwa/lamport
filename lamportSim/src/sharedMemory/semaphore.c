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
#include <stdlib.h>
#include "semaphore.h"

/******************************************************************************
* Function name: semInit
* Parameters:
* 	S - Semaphore
* 	value - Initial value of semaphore
* Return: None.
*
* Description: This function initializes a semaphore.
*******************************************************************************/
void semInit(semaphore_t* S, int value){
	S->guard = 0;
	S->value = value;
	pthread_mutex_init(&(S->mutex), NULL);
	pthread_cond_init(&(S->cv), NULL);
}

/******************************************************************************
* Function name: P
* Parameters:
* 	S - Semaphore
* Return: None.
*
* Description: This function decrements a semaphore.
*******************************************************************************/
void P(semaphore_t* S){
	while(__sync_lock_test_and_set(&(S->guard),1)){;}//spin
	pthread_mutex_lock(&(S->mutex));
	while(S->value <=0){
		S->guard = 0;
		//printf("Thread %X, is about to block! \n", pthread_self());
		pthread_cond_wait(&(S->cv),&(S->mutex));
	}
	S->value--;
	pthread_mutex_unlock(&(S->mutex));
	S->guard = 0;
}

/******************************************************************************
* Function name: V
* Parameters:
* 	S - Semaphore
* Return: None.
*
* Description: This function increments a semaphore.
*******************************************************************************/
void V(semaphore_t* S){
	while(__sync_lock_test_and_set(&(S->guard),1)){;}//spin
	pthread_mutex_lock(&(S->mutex));
	//printf("Thread %X, is now free to proceed! \n", pthread_self());
	S->value++;
	pthread_cond_signal(&(S->cv));
	pthread_mutex_unlock(&(S->mutex));
	S->guard = 0;
}

/******************************************************************************
* Function name: semBroadcast
* Parameters:
* 	S - Semaphore
* Return: None.
*
* Description: This function sets a condition variables for all threads waiting
* on semaphore S.
*******************************************************************************/
void semBroadcast(semaphore_t* S){
	pthread_cond_broadcast(&(S->cv));
}

int getSemValue(semaphore_t* S){
	return S->value;
}
