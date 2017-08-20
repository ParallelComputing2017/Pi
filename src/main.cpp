/*
 * main.cpp
 *
 *  Created on: 10/08/2017
 *      Author: juan
 */
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <chrono>

typedef std::chrono::high_resolution_clock Clock;
typedef std::chrono::milliseconds ms;
typedef std::chrono::duration<float> fsec;

using namespace std;

#include "pi/pi.hpp"
#include "NeuralNetwork/NeuralNetwork.hpp"

int main(int argc, char *argv[]) {

	int threads = 0;
	auto t1 = Clock::now();


	if (argc != 3) { // argc should be 3 for correct execution
		printf("Usage: Posix <program_name> <num_threads> \n");
		printf("\t num_threads = 0 for sequential mode \n");

		printf("Neural Net: %i \n", runNeuralNet());

	} else {
		string self(argv[0]);
		string program(argv[1]);
		threads = atoi(argv[2]);

		printf("Using %i threads \n", threads);

		if (program.compare("pi") == 0) {
			if (threads == 0) {
				printf("Sequential Pi: %f \n", sequentialPi());
			} else {
				printf("Parallel Pi: %f \n", parallelPi(threads));
			}
		}

	}

	// Timer
	auto t2 = Clock::now();
	fsec fs = t2 - t1;
	cout << "Running time: " << chrono::duration<float>(t2 - t1).count()
			<< " seconds" << endl;

	return 0;

}

