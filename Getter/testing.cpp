//#include <iostream>
//#include "Getter.h"
//#include <string>
//
//using namespace std;
//
//struct Data {
//	int iField;
//	string sField;
//	double dField;
//	Data(int iField, string sField, double dField) {
//		this->iField = iField;
//		this->sField = sField;
//		this->dField = dField;
//	}
//	Data(const Data& d) {
//		iField = d.iField;
//		sField = d.sField;
//		dField = d.dField;
//	}
//	Data& operator=(const Data& d) {
//		iField = d.iField;
//		sField = d.sField;
//		dField = d.dField;
//		return *this;
//	}
//};
//
//class OutOfBoundsException {
//};
//class NotImplementedException {
//};
//
//// data structure
//class Container {
//	Data** data;
//	int n;
//public:
//	Container() {
//		data = NULL;
//		n = 0;
//	}
//	Container(const Container& other) {
//		throw NotImplementedException(); // do not modify this, always pass by reference
//	}
//	Container& operator= (const Container& other) {
//		throw NotImplementedException(); // do not modify this, always pass by reference
//	}
//	int size() const {
//		return getSize();
//	}
//	int getSize() const {
//		return n;
//	}
//	Data* operator[](int i) const {
//		if ((i < 0) || (i >= n))
//			throw OutOfBoundsException();
//		return getElement(i);
//	}
//	Data* getElement(int i) const {
//		return data[i];
//	}
//
//	void add(int index, Data d) {
//		if ((index < 0) || (index > n))
//			throw OutOfBoundsException();
//		data = (Data**)realloc(data, ++n * sizeof(Data*));
//		for (int i = n - 1; i > index; --i) {
//			data[i] = data[i - 1];
//		}
//		data[index] = new Data(d);
//	}
//	void remove(int index) {
//		if ((index < 0) || (index >= n))
//			throw OutOfBoundsException();
//		delete(data[index]);
//		for (int i = index; i < n - 1; ++i)
//			data[i] = data[i + 1];
//		data = (Data**)realloc(data, --n * sizeof(Data*));
//	}
//	void edit(int index, Data d) {
//		if ((index < 0) || (index >= n))
//			throw OutOfBoundsException();
//		delete(data[index]);
//		data[index] = new Data(d);
//	}
//	~Container() {
//		for (int i = 0; i < n; ++i)
//			delete(data[i]);
//		free(data);
//	}
//};
//
//int main()
//{
//    using namespace Getter;
//
//	Container container;
//	container.add(0, Data(4, "asdf", 2.0));
//	container.add(1, Data(123, "bv", 251.04));
//	container.add(2, Data(5, "drft", 523.55));
//	container.add(3, Data(87, "mbn", 23.22));
//
//	TreeGetter<Data, int> getter(&Data::iField);
//	getter.Create(&container);
//	Data* dataRef = getter.Search(87);
//
//	container.add(4, Data(57, "df", 57.87));
//	getter.Insert(*container[4]);
//
//	dataRef = getter.Search(4);
//
//	getter.Remove(*container[0]);
//	dataRef->iField = 524;
//	getter.Insert(*container[0]);
//
//	dataRef = getter.Search(524);
//
//    std::cout << dataRef->iField << " " << dataRef->sField << " " << dataRef->dField;
//
//    return 0;
//}