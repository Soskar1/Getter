#include <iostream>
#include <iomanip>
#include <vector>
#include <ctime>

#include "Data.h"

#define ROWS 20
#define COLUMNS 20
#define STRING_LENGTH 5
#define DOUBLE_PRECISION 3

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

int main()
{
    srand((unsigned)time(NULL));

    std::vector<std::vector<Data>> data;

    for (int i = 0; i < ROWS; ++i) {

        std::vector<Data> tmp;
        for (int j = 0; j < COLUMNS; ++j) {
            Data newData;
            newData.intField = rand();
            newData.doubleField = DBLRand(DOUBLE_PRECISION);
            newData.stringField = STRRand(STRING_LENGTH);

            tmp.push_back(newData);
        }

        data.push_back(tmp);
    }

    return 0;
}