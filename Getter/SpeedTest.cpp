//#include <iostream>
//#include <vector>
//#include <ctime>
//#include <string>
//
//#include "Getter.h"
//#include "Data.h"
//#include "Random.h"
//#include "Experimentator.h"
//
//#define ROWS 50
//#define COLUMNS 50
//
//#define STRING_LENGTH 5
//#define DOUBLE_PRECISION 3
//
//Data* LinearSearchByInt(std::vector<std::vector<Data>>& data, const int& value) {
//	for (int i = 0; i < data.size(); ++i) {
//		for (int j = 0; j < data[i].size(); ++j) {
//			if (data[i][j].intField == value)
//				return &data[i][j];
//		}
//	}
//
//	return nullptr;
//}
//
//Data* LinearSearchByDouble(std::vector<std::vector<Data>>& data, const double& value) {
//	for (int i = 0; i < data.size(); ++i) {
//		for (int j = 0; j < data[i].size(); ++j) {
//			if (data[i][j].doubleField == value)
//				return &data[i][j];
//		}
//	}
//
//	return nullptr;
//}
//
//Data* LinearSearchByString(std::vector<std::vector<Data>>& data, const std::string& value) {
//	for (int i = 0; i < data.size(); ++i) {
//		for (int j = 0; j < data[i].size(); ++j) {
//			if (data[i][j].stringField == value)
//				return &data[i][j];
//		}
//	}
//
//	return nullptr;
//}
//
//int main() {
//	srand((unsigned)time(NULL));
//
//	std::vector<std::vector<Data>> data;
//	
//	for (int i = 0; i < ROWS; ++i) {
//	
//	    std::vector<Data> tmp;
//	    for (int j = 0; j < COLUMNS; ++j) {
//	        Data newData;
//	        newData.intField = rand();
//	        newData.doubleField = Random::DBLRand(DOUBLE_PRECISION);
//	        newData.stringField = Random::STRRand(STRING_LENGTH);
//	
//	        tmp.push_back(newData);
//	    }
//	
//	    data.push_back(tmp);
//	}
//
//	Getter::TreeGetter treeGetter(data);
//	Getter::HashGetter hashGetter(data);
//
//	double executionTime = 0;
//
//	executionTime = GetAverageExecutionTime([&data]() {
//		for (int i = 0; i < data.size(); ++i) {
//			for (int j = 0; j < data[i].size(); ++j) {
//				LinearSearchByInt(data, data[i][j].intField);
//			}
//		}
//		});
//
//	std::cout << "LinearSearch/int/" << ROWS << "rows/" << COLUMNS << "columns average execution time: " << executionTime / (ROWS * COLUMNS) << " microseconds\n";
//
//	executionTime = GetAverageExecutionTime([&data]() {
//		for (int i = 0; i < data.size(); ++i) {
//			for (int j = 0; j < data[i].size(); ++j) {
//				LinearSearchByDouble(data, data[i][j].doubleField);
//			}
//		}
//		});
//
//	std::cout << "LinearSearch/double/" << ROWS << "rows/" << COLUMNS << "columns average execution time: " << executionTime / (ROWS * COLUMNS) << " microseconds\n";
//
//	executionTime = GetAverageExecutionTime([&data]() {
//		for (int i = 0; i < data.size(); ++i) {
//			for (int j = 0; j < data[i].size(); ++j) {
//				LinearSearchByString(data, data[i][j].stringField);
//			}
//		}
//		});
//
//	std::cout << "LinearSearch/string/" << ROWS << "rows/" << COLUMNS << "columns average execution time: " << executionTime / (ROWS * COLUMNS) << " microseconds\n\n";
//
//	executionTime = GetAverageExecutionTime([data, &treeGetter]() {
//		for (int i = 0; i < data.size(); ++i) {
//			for (int j = 0; j < data[i].size(); ++j) {
//				treeGetter.SearchByInt(data[i][j].intField);
//			}
//		}
//		});
//
//	std::cout << "TreeGetter/int/" << ROWS << "rows/" << COLUMNS << "columns average execution time: " << executionTime / (ROWS * COLUMNS) << " microseconds\n";
//
//	executionTime = GetAverageExecutionTime([data, &treeGetter]() {
//		for (int i = 0; i < data.size(); ++i) {
//			for (int j = 0; j < data[i].size(); ++j) {
//				treeGetter.SearchByDouble(data[i][j].doubleField);
//			}
//		}
//		});
//
//	std::cout << "TreeGetter/double/" << ROWS << "rows/" << COLUMNS << "columns average execution time: " << executionTime / (ROWS * COLUMNS) << " microseconds\n";
//
//	executionTime = GetAverageExecutionTime([data, &treeGetter]() {
//		for (int i = 0; i < data.size(); ++i) {
//			for (int j = 0; j < data[i].size(); ++j) {
//				treeGetter.SearchByString(data[i][j].stringField);
//			}
//		}
//		});
//
//	std::cout << "TreeGetter/string/" << ROWS << "rows/" << COLUMNS << "columns average execution time: " << executionTime / (ROWS * COLUMNS) << " microseconds\n\n";
//
//	executionTime = GetAverageExecutionTime([data, &hashGetter]() {
//		for (int i = 0; i < data.size(); ++i) {
//			for (int j = 0; j < data[i].size(); ++j) {
//				hashGetter.SearchByInt(data[i][j].intField);
//			}
//		}
//		});
//
//	std::cout << "HashGetter/int/" << ROWS << "rows/" << COLUMNS << "columns average execution time: " << executionTime / (ROWS * COLUMNS) << " microseconds\n";
//
//	executionTime = GetAverageExecutionTime([data, &hashGetter]() {
//		for (int i = 0; i < data.size(); ++i) {
//			for (int j = 0; j < data[i].size(); ++j) {
//				hashGetter.SearchByDouble(data[i][j].doubleField);
//			}
//		}
//		});
//
//	std::cout << "HashGetter/double/" << ROWS << "rows/" << COLUMNS << "columns average execution time: " << executionTime / (ROWS * COLUMNS) << " microseconds\n";
//
//	executionTime = GetAverageExecutionTime([data, &hashGetter]() {
//		for (int i = 0; i < data.size(); ++i) {
//			for (int j = 0; j < data[i].size(); ++j) {
//				hashGetter.SearchByString(data[i][j].stringField);
//			}
//		}
//		});
//
//	std::cout << "HashGetter/string/" << ROWS << "rows/" << COLUMNS << "columns average execution time: " << executionTime / (ROWS * COLUMNS) << " microseconds\n";
//
//	return 0;
//}