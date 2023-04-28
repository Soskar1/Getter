#include "Data.h"

Data::Data() {
	intField = 0;
	doubleField = 0;
	stringField = "";
}

Data::Data(int iField, std::string sField, double dField) {
	this->intField = iField;
	this->stringField = sField;
	this->doubleField = dField;
}

Data::Data(const Data& d) {
	intField = d.intField;
	stringField = d.stringField;
	doubleField = d.doubleField;
}

Data& Data::operator=(const Data& d) {
	intField = d.intField;
	stringField = d.stringField;
	doubleField = d.doubleField;
	return *this;
}