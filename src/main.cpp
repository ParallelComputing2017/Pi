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

void writeCSV(string program, int threads, string runningTime);

int main(int argc, char *argv[]) {

	int threads = 8;
	string self(argv[0]);
	string mode = "all";

	if (argc != 3) { // argc should be 3 for correct execution
		printf("Usage: Posix <mode_name> <num_threads>\n");
		printf("\tModes: all, posix, openmp, sequential \n");
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

		printf("Posix.\t time: %s\t result: %f \n",
				timer.format(3, "%ws ").c_str(), pi);
	}
	if (mode.compare("openmp") == 0 || all) {

		timer.start();
		double pi = Pi::openMP(threads);
		timer.stop();

		printf("OpenMP\t time: %s\t result: %f \n",
				timer.format(3, "%ws").c_str(), pi);

	}
	if (mode.compare("sequential") == 0 || all) {

		timer.start();
		double pi = Pi::sequential();
		timer.stop();

		printf("Simple.\t time: %s\t result: %f \n",
				timer.format(3, "%ws").c_str(), pi);
	}


	writeCSV(mode, threads, timer.format(3, "%ws"));

	return 0;

}

void writeCSV(string program, int threads, string seconds_runningTime) {

	ofstream myfile;

	myfile.open("./log/pi.csv", std::ofstream::app);

	myfile << "\"" + program + "\"";
	myfile << "; " + to_string(threads);
	myfile << "; " + seconds_runningTime;
	myfile << "\n";

	myfile.close();
}

