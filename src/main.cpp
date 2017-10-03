/*
 * main.cpp
 *
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <boost/timer/timer.hpp>

#include <iostream>
#include <fstream>

using namespace boost::timer;

using namespace std;

#include "pi/pi.hpp"

void printLog(string mode, cpu_timer timer, double result);

int main(int argc, char *argv[]) {

	int threads = 4;
	string self(argv[0]);
	string mode = "all";

	if (argc != 3) { // argc should be 3 for correct execution
		printf("Usage: Posix <mode_name> <num_threads>\n");
		printf("\tModes: all, posix, openmp, cuda, single \n");
	} else {
		mode = argv[1];
		threads = atoi(argv[2]);
	}

	cpu_timer timer;

	printf("Using %i threads \n", threads);


	bool all = (mode.compare("all") == 0);

	if (mode.compare("posix") == 0 || all) {

		timer.start();
		double pi = Pi::posix(threads);
		timer.stop();

		printLog("Posix", timer, pi);
	}
	if (mode.compare("openmp") == 0 || all) {

		timer.start();
		double pi = Pi::openMP(threads);
		timer.stop();

		printLog("OpenMP", timer, pi);

	}
	if (mode.compare("cuda") == 0 || all) {

			timer.start();
			double pi = Pi::cuda(threads);
			timer.stop();

			printLog("CUDA", timer, pi);

		}
	if (mode.compare("single") == 0) {

		timer.start();
		double pi = Pi::sequential();
		timer.stop();

		printLog("Single", timer, pi);
	}

	return 0;

}

void printLog(string mode, cpu_timer timer, double result) {

	printf("%s\t time: %s\t result: %f \n", mode.c_str(),
			timer.format(3, "%ws").c_str(), result);
}

