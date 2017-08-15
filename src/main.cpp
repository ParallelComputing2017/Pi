/*
 * main.cpp
 *
 *  Created on: 10/08/2017
 *      Author: juan
 */
#include <stdio.h>
#include <stdlib.h>

using namespace std;

#include "pi2.hpp"

int main(int argc, char *argv[]) {
	int threads = 4;
	if (argc != 2) { // argc should be 2 for correct execution
		// We print argv[0] assuming it is the program name
		printf("Usage <program_name> <num_threads>\n");
	} else {
		threads = atoi(argv[1]);
	}
	printf("Secuencial Pi %f \n", secuencialPi());

	printf("Using %i threads \n", threads);
	printf("Parallel Pi %f \n", Pi2(threads));

	return 0;

}

