/*
 * Rand.h
 *
 *  Created on: 2010-01-21
 *      Author: theolol
 */

#ifndef RAND_H_
#define RAND_H_
#include "Types.h"

class Rand {
public:
	static void init (uint seed) { _seed = seed; }
	static uint next_rand() {
		uint lo = 16807 * (_seed & 0xffff);
		uint hi = 16807 * (_seed >> 16);
		lo += (hi & 0x7fff) << 16;
		lo += hi >> 15;
		return _seed = (lo & 0x7FFFFFFF) + (lo >> 31);
	}
	static uint next_rand(uint n) {
	  return ((next_rand() & 0xffff) * n) >> 16;
	}
private:
	static uint _seed;
};

uint Rand::_seed;

#endif /* RAND_H_ */
