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

#include <iostream>
#include <fstream>

typedef std::chrono::high_resolution_clock Clock;
typedef std::chrono::milliseconds ms;
typedef std::chrono::duration<float> fsec;

using namespace std;

#include "pi/pi.hpp"
#include "NeuralNetwork/NeuralNetwork.hpp"

#include "../lib/simple_cnn/Example_MNIST/example.h"

void writeCSV(string program, int threads, float runningTime);

int main(int argc, char *argv[]) {

	int threads = 4;
	string self(argv[0]);
	string program = "nn";

	if (argc != 3) { // argc should be 3 for correct execution
		printf("Usage: Posix <program_name> <num_threads> \n");
		printf("\t num_threads = 0 for sequential mode \n");

	} else {
		program = argv[1];
		threads = atoi(argv[2]);
	}

	auto t1 = Clock::now();

	printf("Using %i threads \n", threads);

	if (program.compare("pi") == 0) {
		if (threads == 0) {
			printf("Sequential Pi: %f \n", Pi::sequential());
		} else {
			printf("Parallel Posix Pi: %f \n", Pi::posix(threads));

			printf("Parallel OpenMP Pi: %f \n", Pi::openMP(threads));
		}
	} else {

		printf("Neural Net: %i \n", mainExample());
	}

	// Timer
	auto t2 = Clock::now();
	fsec fs = t2 - t1;

	writeCSV(program, threads, fs.count());

	return 0;

}

void writeCSV(string program, int threads, float seconds_runningTime) {

	ofstream myfile;

	myfile.open("./log/" + program + ".csv", std::ofstream::app);

	myfile << "\"" + program + "\"";
	myfile << "; " + to_string(threads);
	myfile << "; " + to_string(seconds_runningTime);
	myfile << "\n";

	myfile.close();
}

