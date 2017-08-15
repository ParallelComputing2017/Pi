/*
 * pi.cpp
 *
 *  Created on: 10/08/2017
 *      Author: juan
 */
#include <stdio.h>
#include <math.h>
#include <pthread.h>

#define ITERATIONS 1e9

int NUM_THREADS = 1;

double *piTotal;

void *calculatePi(void *arg) {
	int threadid = *(int*) arg;
	int initIteration, endIteration;
	initIteration = (ITERATIONS / NUM_THREADS) * threadid;
	endIteration = initIteration + (ITERATIONS / NUM_THREADS) - 1;

	piTotal[threadid] = 0.0;

	do {
		// The alternative (pow) takes more time in the processor.
		piTotal[threadid] = piTotal[threadid] + (4.0 / (initIteration * 2 + 1));
		initIteration++;
		piTotal[threadid] = piTotal[threadid] - (4.0 / (initIteration * 2 + 1));
		initIteration++;
	} while (initIteration < endIteration);

	return 0;
}

int Pi2(int THREADS) {

	// GLOBAL VARIABLES
	NUM_THREADS = THREADS;
	piTotal = new double[NUM_THREADS];

	printf("Start PI (NUM_THREADS = %i)\n", NUM_THREADS);

	pthread_t threads[NUM_THREADS];
	int threadId[NUM_THREADS], i, *retval;

	for (i = 0; i < NUM_THREADS; i++) {
		threadId[i] = i;
		pthread_create(&threads[i], NULL, calculatePi, &threadId[i]);
	}
	for (i = 0; i < NUM_THREADS; i++) {
		// wait for thread termination
		pthread_join(threads[i], (void**) &retval);
	}

	for (i = 1; i < NUM_THREADS; i++) {
		piTotal[0] = piTotal[0] + piTotal[i];
	}

	printf("Computed value of Pi:  %12.9f\n", piTotal[0]);

	// DELETE block
	delete[] piTotal;

	return 0;
}

double secuencialPi() {
	int initIteration, endIteration;
	initIteration = 0;
	endIteration = ITERATIONS - 1;

	double pi = 0.0;

	do {
		// The alternative (pow) takes more time in the processor.
		pi = pi + (4.0 / (initIteration * 2 + 1));
		initIteration++;
		pi = pi - (4.0 / (initIteration * 2 + 1));
		initIteration++;
	} while (initIteration < endIteration);

	return pi;
}
