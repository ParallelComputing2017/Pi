/*
 * pi.cpp
 *
 *  Created on: 10/08/2017
 *      Author: juan
 */
#include <stdio.h>
#include <math.h>
#include <pthread.h>
#define NUM_RECT 100000000
#define NUM_THREADS 4
double gPi = 0.0;  //  global accumulator for pi
pthread_mutex_t gLock;

void *Area(void *threadid) {
	long tId;
	tId = (long) threadid;
	double h = 2.0 / NUM_RECT;
	double partialSum = 0.0, x;  // local to each thread

	// use every NUMTHREADS-th ste
	for (int i = tId; i < NUM_RECT; i += NUM_THREADS) {
		x = -1 + (i + 0.5f) * h;
		partialSum += sqrt(1.0 - x * x) * h;
	}
	pthread_mutex_lock(&gLock);
	gPi += partialSum;  // add partial to global final answer
	pthread_mutex_unlock(&gLock);
	return 0;
}

int Pi() {

	printf("Start PI\n");

	pthread_t threads[NUM_THREADS];
	long  i;
	pthread_mutex_init(&gLock, NULL);
	for (i = 0; i < NUM_THREADS; ++i) {
		pthread_create(&threads[i],           // Returned thread handle
				NULL,                 // Thread Attributes
				Area,                   // Thread function
				(void *) i);        // Data for Area()
	}
	for (i = 0; i < NUM_THREADS; ++i) {
		pthread_join(threads[i], NULL);
	}
	gPi *= 2.0;
	printf("Computed value of Pi:  %12.9f\n", gPi);
	pthread_mutex_destroy(&gLock);
	return 0;
}
