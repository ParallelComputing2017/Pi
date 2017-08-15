/*
 * main.cpp
 *
 *  Created on: 10/08/2017
 *      Author: juan
 */
#include <stdio.h>
#include <stdlib.h>
#include <string>

using namespace std;

#include "pi.hpp"

int main(int argc, char *argv[]) {

	int threads = 0;

	if (argc != 3) { // argc should be 3 for correct execution
		printf("Usage: Posix <program_name> <num_threads> \n");
		printf("\t num_threads = 0 for sequential mode \n");

		printf("Parallel Pi %f \n", parallelPi(4));

	} else {
		string self(argv[0]);
		string program(argv[1]);
		threads = atoi(argv[2]);

		printf("Using %i threads \n", threads);

		if (program.compare("pi") == 0) {
			if (threads == 0) {
				printf("Sequential Pi %f \n", sequentialPi());
			} else {
				printf("Parallel Pi %f \n", parallelPi(threads));
			}
		}

	}

	return 0;

}

