#include <iostream>
#include <vector>
#include <ctime>
#include <string>

#include "Getter.h"
#include "Random.h"
#include "Experimentator.h"

#define ARRAY_SIZE 5000

#define STRING_LENGTH 5
#define DOUBLE_PRECISION 3

struct Data {
	int iField;
	std::string sField;
	double dField;
	Data(int iField, std::string sField, double dField) {
		this->iField = iField;
		this->sField = sField;
		this->dField = dField;
	}
	Data(const Data& d) {
		iField = d.iField;
		sField = d.sField;
		dField = d.dField;
	}
	Data& operator=(const Data& d) {
		iField = d.iField;
		sField = d.sField;
		dField = d.dField;
		return *this;
	}
};

Data* LinearSearchByInt(std::vector<Data>& data, const int& value) {
	for (int i = 0; i < data.size(); ++i) {
		if (data[i].iField == value) {
			return &data[i];
		}
	}

	return nullptr;
}

Data* LinearSearchByDouble(std::vector<Data>& data, const double& value) {
	for (int i = 0; i < data.size(); ++i) {
		if (data[i].dField == value) {
			return &data[i];
		}
	}

	return nullptr;
}

Data* LinearSearchByString(std::vector<Data>& data, const std::string& value) {
	for (int i = 0; i < data.size(); ++i) {
		if (data[i].sField == value) {
			return &data[i];
		}
	}

	return nullptr;
}

int main() {
	using namespace Getter;

	srand((unsigned)time(NULL));

	std::vector<Data> data;
	
	for (int i = 0; i < ARRAY_SIZE; ++i) {
		Data newData(rand(), Random::STRRand(STRING_LENGTH), Random::DBLRand(DOUBLE_PRECISION));
	    data.push_back(newData);
	}

	TreeGetter<Data, int> iGetter(&Data::iField);
	TreeGetter<Data, std::string> sGetter(&Data::sField);
	TreeGetter<Data, double> dGetter(&Data::dField);

	iGetter.Create(data);
	sGetter.Create(data);
	dGetter.Create(data);
	//HashGetter hashGetter(data);

	double executionTime = 0;

	executionTime = GetAverageExecutionTime([&data]() {
		for (int i = 0; i < data.size(); ++i) {
			LinearSearchByInt(data, data[i].iField);
		}
		});

	std::cout << "LinearSearch/int/" << ARRAY_SIZE << "elements average execution time: " << executionTime / ARRAY_SIZE << " microseconds\n";

	executionTime = GetAverageExecutionTime([&data]() {
		for (int i = 0; i < data.size(); ++i) {
			LinearSearchByDouble(data, data[i].dField);
		}
		});

	std::cout << "LinearSearch/double/" << ARRAY_SIZE << "elements average execution time: " << executionTime / ARRAY_SIZE << " microseconds\n";

	executionTime = GetAverageExecutionTime([&data]() {
		for (int i = 0; i < data.size(); ++i) {
			LinearSearchByString(data, data[i].sField);
		}
		});

	std::cout << "LinearSearch/string/" << ARRAY_SIZE << "elements average execution time: " << executionTime / ARRAY_SIZE << " microseconds\n";

	executionTime = GetAverageExecutionTime([data, &iGetter]() {
		for (int i = 0; i < data.size(); ++i) {
			iGetter.Search(data[i].iField);
		}
		});

	std::cout << "TreeGetter/int/" << ARRAY_SIZE << "elements average execution time: " << executionTime / ARRAY_SIZE << " microseconds\n";

	executionTime = GetAverageExecutionTime([data, &dGetter]() {
		for (int i = 0; i < data.size(); ++i) {
			dGetter.Search(data[i].dField);
		}
		});

	std::cout << "TreeGetter/double/" << ARRAY_SIZE << "elements average execution time: " << executionTime / ARRAY_SIZE << " microseconds\n";

	executionTime = GetAverageExecutionTime([data, &sGetter]() {
		for (int i = 0; i < data.size(); ++i) {
			sGetter.Search(data[i].sField);
		}
		});

	std::cout << "TreeGetter/string/" << ARRAY_SIZE << "elements average execution time: " << executionTime / ARRAY_SIZE << " microseconds\n";

	//executionTime = GetAverageExecutionTime([data, &hashGetter]() {
	//	for (int i = 0; i < data.size(); ++i) {
	//		for (int j = 0; j < data[i].size(); ++j) {
	//			hashGetter.SearchByInt(data[i][j].intField);
	//		}
	//	}
	//	});

	//std::cout << "HashGetter/int/" << ROWS << "rows/" << COLUMNS << "columns average execution time: " << executionTime / (ROWS * COLUMNS) << " microseconds\n";

	//executionTime = GetAverageExecutionTime([data, &hashGetter]() {
	//	for (int i = 0; i < data.size(); ++i) {
	//		for (int j = 0; j < data[i].size(); ++j) {
	//			hashGetter.SearchByDouble(data[i][j].doubleField);
	//		}
	//	}
	//	});

	//std::cout << "HashGetter/double/" << ROWS << "rows/" << COLUMNS << "columns average execution time: " << executionTime / (ROWS * COLUMNS) << " microseconds\n";

	//executionTime = GetAverageExecutionTime([data, &hashGetter]() {
	//	for (int i = 0; i < data.size(); ++i) {
	//		for (int j = 0; j < data[i].size(); ++j) {
	//			hashGetter.SearchByString(data[i][j].stringField);
	//		}
	//	}
	//	});

	//std::cout << "HashGetter/string/" << ROWS << "rows/" << COLUMNS << "columns average execution time: " << executionTime / (ROWS * COLUMNS) << " microseconds\n";

	return 0;
}