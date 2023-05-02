#ifndef RANDOM_H
#define RANDOM_H

#include <string>

namespace Random {
	double DBLRand(const size_t& precision);
	std::string STRRand(const size_t& length);
}

#endif