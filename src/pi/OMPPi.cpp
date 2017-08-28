/*
 * pi.cpp
 *
 *  Created on: 10/08/2017
 *      Author: juan
 */
#include <stdio.h>
#include <math.h>
#include <pthread.h>
#include <omp.h>

#define ITERATIONS 1e9
#define PAD 8

double forOMPPi(int threads) {

	double pi = 0.0;

	int start = 0, end = ITERATIONS - 1;

#pragma omp parallel num_threads(threads)
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
