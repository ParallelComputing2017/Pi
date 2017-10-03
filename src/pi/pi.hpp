/*
 * pi.h
 *
 *  Created on: 10/08/2017
 *      Author: juan
 */

#ifndef PI_PI_HPP_
#define PI_PI_HPP_

/* Constants */
#define ITERATIONS 1e9

class Pi {
public:
	static double sequential();

	static double posix(int numThreads);

	static double openMP(int numThreads);

private:

};

double parallelPi(int THREADS);

double sequentialPi();

#endif /* PI_PI_HPP_ */
