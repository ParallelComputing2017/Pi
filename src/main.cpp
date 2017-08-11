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
		printf("Usage %i <num_threads>\n", argv[0]);
	}
	printf("secuencialPi %i \n", secuencialPi);

	threads = atoi(argv[1]);
	return Pi2(threads);

}

