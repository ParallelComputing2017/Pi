/*
 * pi.cpp
 *
 *  Created on: 10/08/2017
 *      Author: juan
 */
#include <stdio.h>
#include <math.h>
#include <pthread.h>

#include "pi.hpp"
#include "pi_cuda.cuh"

/* Global variables */
int NUM_THREADS = 1;
double *piTotal;


double calculatePi(int initIteration, int endIteration) {
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

	piTotal[threadid] = calculatePi(initIteration, endIteration);

	return 0;
}

double Pi::posix(int numThreads) {

	// GLOBAL VARIABLES
	NUM_THREADS = numThreads;
	piTotal = new double[NUM_THREADS];

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

double Pi::sequential() {
	return calculatePi(0, ITERATIONS - 1);
}

double Pi::openMP(int numThreads) {

	double pi = 0.0;

	int start = 0, end = ITERATIONS - 1;

#pragma omp parallel num_threads(numThreads)
	{
#pragma omp for reduction(+:pi)
		for (int i = start; i < end; i++) {
			// The alternative (pow) takes more time in the processor.
			pi = pi + (4.0 / (i * 2 + 1));
			i++;
			pi = pi - (4.0 / (i * 2 + 1));

		}
	}

	return pi;
}

double Pi::cuda(int numThreads) {
	return pi_cuda(ITERATIONS);
}


