#ifndef DATA_H
#define DATA_H

#include <string>

struct Data {
	int intField;
	double doubleField;
	std::string stringField;

	Data();
	Data(int iField, std::string sField, double dField);
	Data(const Data& d);

	Data& operator=(const Data& d);
};
#endif