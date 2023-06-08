#include <iostream>
#include <vector>
#include "Getter.h"

struct Data
{
    int a;
    double b;

    Data(int a, double b) {
        this->a = a;
        this->b = b;
    }
};

int main()
{
    using namespace Getter;

    std::vector<Data> data;
    data.push_back(Data(4, 2.0));
    data.push_back(Data(25, 0.98));
    data.push_back(Data(12, 3.5));
    data.push_back(Data(8, 3.0));
    data.push_back(Data(120, 20.12));

    TreeGetter<Data, int> getter(&Data::a);
    getter.Create(data);

    return 0;
}