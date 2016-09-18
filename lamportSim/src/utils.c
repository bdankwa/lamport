/*
 ============================================================================
 Name        : utils.h
 Author      : Boakye Dankwa
 Version     :
 Description : Utilities
 ============================================================================
 */
#include <stdlib.h>
#include <sys/time.h>
#include <stdio.h>

#include "utils.h"

/******************************************************************************
* Function name: generateRandomInt
* Parameters: lower - lower limit
*             upper - upper limit
* Return: random integer in the range [lower , upper].
*
* Description: This function generates a random integer in the range [lower , upper] .
*******************************************************************************/
int generateRandomInt(int lower, int upper){
	struct timeval   tv;
	struct timezone  tz;
	double cur_time;

	gettimeofday(&tv, &tz);
	cur_time = tv.tv_sec + tv.tv_usec;

	srand(cur_time);// seed random number generator with current time

	return (rand() % (upper - lower + 1) + lower);
}

/******************************************************************************
* Function name: generateRandomDouble
* Parameters: None
* Return: random double value.
*
* Description: This function generates a value of type double .
*******************************************************************************/
double generateRandomDouble(){
	return ((double)generateRandomInt(-5, 5)/generateRandomInt(1, 5));
}

/******************************************************************************
* Function name: getCurrentTime
* Parameters: None
* Return: seconds since epoch.
*
* Description: This function returns the current time since epoch in seconds .
*******************************************************************************/
double getCurrentTime(void){
	struct timeval   tv;
	struct timezone  tz;
	double cur_time;

	gettimeofday(&tv, &tz);
	cur_time = tv.tv_sec + tv.tv_usec / 1000000.0;

	return cur_time;
}

/******************************************************************************
* Function name: writeToFile
* Parameters: fileName, proc, eventProb, bztProb, time
* Return: none.
*
* Description: This function saves simulation data to file
*******************************************************************************/
void writeToFile(char* fileName, int proc, float eventProb, float bztProb, unsigned int time){
	FILE* fd;
	if((fd = fopen(fileName, "a")) == NULL){
		perror("Cannot open output file \n");
		exit(EXIT_FAILURE);
	}
	fprintf(fd,"%i\t%f\t%f\t%i\n",proc,eventProb, bztProb, time);
}
