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
#define NUM_THREADS 4

double piTotal[NUM_THREADS];

void *calculatePi(void *arg) {
	long threadid = *(int*) arg;
	int initIteration, endIteration;
	initIteration = (ITERATIONS / NUM_THREADS) * threadid;
	endIteration = initIteration + (ITERATIONS / NUM_THREADS) - 1;

	int i = threadid;

	do {
		// The alternative (pow) takes more time in the processor.
		piTotal[i] = piTotal[i] + (4.0 / (initIteration * 2 + 1));
		i++;
		piTotal[i] = piTotal[i] - (4.0 / (initIteration * 2 + 1));
		i++;
	} while (initIteration < endIteration);

	return 0;
}

int Pi2() {

	printf("Start PI\n");

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
	return 0;
}
