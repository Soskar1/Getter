//#include <iostream>
//#include <vector>
//#include <ctime>
//#include <cstdlib>
//
//#include "Data.h"
//#include "Getter.h"
//#include "Random.h"
//
//#define ROWS 20
//#define COLUMNS 20
//
//#define STRING_LENGTH 5
//#define DOUBLE_PRECISION 3
//
//int main()
//{
//    srand((unsigned)time(NULL));
//
//    std::vector<std::vector<Data>> data;
//
//    for (int i = 0; i < ROWS; ++i) {
//
//        std::vector<Data> tmp;
//        for (int j = 0; j < COLUMNS; ++j) {
//            Data newData;
//            newData.intField = rand();
//            newData.doubleField = Random::DBLRand(DOUBLE_PRECISION);
//            newData.stringField = Random::STRRand(STRING_LENGTH);
//
//            tmp.push_back(newData);
//        }
//
//        data.push_back(tmp);
//    }
//
//    Getter::TreeGetter treeGetter(data);
//
//    Data* tmp = nullptr;
//
//    tmp = treeGetter.SearchByInt(data[10][5].intField);
//    std::cout << tmp->intField << " " << tmp->doubleField << " " << tmp->stringField << std::endl;
//    
//    tmp = treeGetter.SearchByDouble(data[10][5].doubleField);
//    std::cout << tmp->intField << " " << tmp->doubleField << " " << tmp->stringField << std::endl;
//
//    tmp = treeGetter.SearchByString(data[10][5].stringField);
//    std::cout << tmp->intField << " " << tmp->doubleField << " " << tmp->stringField << std::endl;
//
//    treeGetter.Update(Getter::UpdateOperation::remove, data[10][5]);
//    data[10][5].intField = 47;
//    data[10][5].stringField = "something";
//    treeGetter.Update(Getter::UpdateOperation::insert, data[10][5]);
//
//    tmp = treeGetter.SearchByInt(data[10][5].intField);
//    std::cout << tmp->intField << " " << tmp->doubleField << " " << tmp->stringField << std::endl;
//
//    tmp = treeGetter.SearchByDouble(data[10][5].doubleField);
//    std::cout << tmp->intField << " " << tmp->doubleField << " " << tmp->stringField << std::endl;
//
//    tmp = treeGetter.SearchByString(data[10][5].stringField);
//    std::cout << tmp->intField << " " << tmp->doubleField << " " << tmp->stringField << std::endl;
//
//    return 0;
//}