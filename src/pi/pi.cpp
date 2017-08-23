/*
 * pi.cpp
 *
 *  Created on: 10/08/2017
 *      Author: juan
 */
#include <stdio.h>
#include <math.h>
#include <pthread.h>

/* Constants */
#define ITERATIONS 1e9

/* Global variables */
int NUM_THREADS = 1;
double *piTotal;


double calcPi(int initIteration, int endIteration) {
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

void *calcPi(void *arg) {
	int threadid = *(int*) arg;
	int initIteration, endIteration;
	initIteration = (ITERATIONS / NUM_THREADS) * threadid;
	endIteration = initIteration + (ITERATIONS / NUM_THREADS) - 1;

	piTotal[threadid] = calcPi(initIteration, endIteration);

	return 0;
}

double parallelPi(int THREADS) {

	// GLOBAL VARIABLES
	NUM_THREADS = THREADS;
	piTotal = new double[NUM_THREADS];

	printf("Start Parallel PI (NUM_THREADS = %i)\n", NUM_THREADS);

	pthread_t threads[NUM_THREADS];
	int threadId[NUM_THREADS], i, *retval;

	for (i = 0; i < NUM_THREADS; i++) {
		threadId[i] = i;
		pthread_create(&threads[i], NULL, calcPi, &threadId[i]);
	}
	for (i = 0; i < NUM_THREADS; i++) {
		// wait for thread termination
		pthread_join(threads[i], (void**) &retval);
	}

	for (i = 1; i < NUM_THREADS; i++) {
		piTotal[0] = piTotal[0] + piTotal[i];
	}

	double pi = piTotal[0];

	// DELETE block
	delete[] piTotal;

	return pi;
}

double sequentialPi() {
	return calcPi(0, ITERATIONS - 1);
}


