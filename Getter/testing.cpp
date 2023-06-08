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

    Data* dataRef = getter.Search(12);

    data.push_back(Data(5634, 1454.241));

    getter.Update(UpdateOperation::insert, data[5]);

    dataRef = getter.Search(5634);
    
    std::cout << dataRef->a << " " << dataRef->b;

    //Tree::AVLTree<int> tree;
    //tree.Insert(5);
    //tree.Insert(14);
    //tree.Insert(5678);
    //tree.Insert(254);

    //std::cout << tree.Contains(5);

    return 0;
}