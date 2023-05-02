#include "Random.h"

#include <cstdlib>
#include <cmath>

namespace Random {
    double DBLRand(const size_t& precision) {
        double powerNum = pow(10, precision);
        double fraction = round(((double)rand() / RAND_MAX) * powerNum) / powerNum;
        return rand() + fraction;
    }

    std::string STRRand(const size_t& length) {
        static const char alphanum[] =
            "0123456789"
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
            "abcdefghijklmnopqrstuvwxyz";

        std::string tmp;
        tmp.reserve(length);

        for (int i = 0; i < length; ++i) {
            tmp += alphanum[rand() % (sizeof(alphanum) - 1)];
        }

        return tmp;
    }
}