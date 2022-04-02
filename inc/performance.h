#ifndef _PERFORMANCE_H
#define _PERFORMANCE_H

#include <random>

#include "uLong.h"
#include <time.h>

typedef struct PerformanceTester {
	clock_t start, finish;
	double totaltime;

	void Start();
	void Stop();
	void OutputToFile(std::string filename, std::string path, byte* init, byte* goal, int size);
};

uLong getRandomState(int _size);
#endif
