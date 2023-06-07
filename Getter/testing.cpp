#include <iostream>
#include "Getter.h"

struct Data
{
    int a;
};

int main()
{
    using namespace Getter;

    Data data;
    data.a = 42;

    TreeGetter<Data, int> getter(&Data::a, data);

    return 0;
}