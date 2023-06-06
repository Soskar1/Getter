#include "Getter.h"

namespace Getter {
	HashGetter::LinkedList::LinkedList()
	{
		value = nullptr;
		next = nullptr;
		allowedToRewrite = false;
	}

	HashGetter::LinkedList::LinkedList(Data& value)
	{
		this->value = &value;
		next = nullptr;
		allowedToRewrite = false;
	}

	HashGetter::LinkedList::~LinkedList()
	{
		delete next;
	}

	size_t HashGetter::HashInt(const int& value) const
	{
		return value % m_Capacity;
	}

	size_t HashGetter::HashDouble(const double& value) const
	{
		return (int)value % m_Capacity;
	}

	size_t HashGetter::HashString(const std::string& value) const
	{
		if (value.size() == 0) {
			return 0;
		}

		return (value.size() + value[0]) % m_Capacity;
	}

	void HashGetter::Insert(Data& value)
	{
		Insert(value, HashInt(value.intField), m_IntHashTable);
		Insert(value, HashDouble(value.doubleField), m_DoubleHashTable);
		Insert(value, HashString(value.stringField), m_StringHashTable);
	}

	void HashGetter::Insert(Data& value, const size_t& hashIndex, LinkedList*& hashTable)
	{
		if (hashTable[hashIndex].value == nullptr || hashTable[hashIndex].allowedToRewrite) {
			hashTable[hashIndex].value = &value;
			hashTable[hashIndex].allowedToRewrite = false;
			return;
		}

		if (hashTable[hashIndex].next == nullptr) {
			hashTable[hashIndex].next = new LinkedList();
			hashTable[hashIndex].next->value = &value;
			return;
		}
		else if (hashTable[hashIndex].next->allowedToRewrite) {
			hashTable[hashIndex].next->value = &value;
			hashTable[hashIndex].next->allowedToRewrite = false;
		}

		LinkedList* linkedList = hashTable[hashIndex].next;
		while (linkedList->next != nullptr) {
			if (linkedList->value == &value) {
				return;
			}

			if (linkedList->next->allowedToRewrite) {
				linkedList->next->value = &value;
				linkedList->next->allowedToRewrite = false;
				return;
			}

			linkedList = linkedList->next;
		}

		linkedList->next = new LinkedList();
		linkedList->next->value = &value;
	}

	void HashGetter::Remove(Data& value)
	{
		Remove(value, HashInt(value.intField), m_IntHashTable);
		Remove(value, HashDouble(value.doubleField), m_DoubleHashTable);
		Remove(value, HashString(value.stringField), m_StringHashTable);
	}

	void HashGetter::Remove(Data& value, const size_t& hashIndex, LinkedList*& hashTable)
	{
		LinkedList* linkedList = &hashTable[hashIndex];

		while (linkedList->value != &value) {
			linkedList = linkedList->next;
		}

		linkedList->allowedToRewrite = true;
	}

	HashGetter::HashGetter()
	{
		m_IntHashTable = nullptr;
		m_DoubleHashTable = nullptr;
		m_StringHashTable = nullptr;

		m_Capacity = 0;
	}

	HashGetter::HashGetter(std::vector<std::vector<Data>>& data)
	{
		Create(data);
	}

	HashGetter::~HashGetter()
	{
		delete[] m_IntHashTable;
		delete[] m_DoubleHashTable;
		delete[] m_StringHashTable;
	}

	void HashGetter::Create(std::vector<std::vector<Data>>& data)
	{
		if (m_IntHashTable != nullptr || m_DoubleHashTable != nullptr || m_StringHashTable != nullptr) {
			delete[] m_IntHashTable;
			delete[] m_DoubleHashTable;
			delete[] m_StringHashTable;
		}

		m_Capacity = data.size() * data[0].size();
		m_IntHashTable = new LinkedList[m_Capacity];
		m_DoubleHashTable = new LinkedList[m_Capacity];
		m_StringHashTable = new LinkedList[m_Capacity];

		for (int i = 0; i < data.size(); ++i) {
			for (int j = 0; j < data[i].size(); ++j) {
				Insert(data[i][j]);
			}
		}
	}

	Data* HashGetter::SearchByInt(const int& value) const
	{
		size_t hashIndex = HashInt(value);

		if (m_IntHashTable[hashIndex].value == nullptr) {
			return nullptr;
		}

		if (m_IntHashTable[hashIndex].value->intField == value) {
			return m_IntHashTable[hashIndex].value;
		}

		if (m_IntHashTable[hashIndex].next == nullptr) {
			return nullptr;
		}

		LinkedList* linkedList = &m_IntHashTable[hashIndex];
		while (linkedList->next != nullptr) {
			linkedList = linkedList->next;

			if (linkedList->value->intField == value) {
				return linkedList->value;
			}
		}

		return nullptr;
	}

	Data* HashGetter::SearchByDouble(const double& value) const
	{
		size_t hashIndex = HashDouble(value);

		if (m_DoubleHashTable[hashIndex].value == nullptr) {
			return nullptr;
		}

		if (m_DoubleHashTable[hashIndex].value->doubleField == value) {
			return m_DoubleHashTable[hashIndex].value;
		}

		if (m_DoubleHashTable[hashIndex].next == nullptr) {
			return nullptr;
		}

		LinkedList* linkedList = &m_DoubleHashTable[hashIndex];
		while (linkedList->next != nullptr) {
			linkedList = linkedList->next;

			if (linkedList->value->doubleField == value) {
				return linkedList->value;
			}
		}

		return nullptr;
	}

	Data* HashGetter::SearchByString(const std::string& value) const
	{
		size_t hashIndex = HashString(value);

		if (m_StringHashTable[hashIndex].value == nullptr) {
			return nullptr;
		}

		if (m_StringHashTable[hashIndex].value->stringField == value) {
			return m_IntHashTable[hashIndex].value;
		}

		if (m_StringHashTable[hashIndex].next == nullptr) {
			return nullptr;
		}

		LinkedList* linkedList = &m_StringHashTable[hashIndex];
		while (linkedList->next != nullptr) {
			linkedList = linkedList->next;

			if (linkedList->value->stringField == value) {
				return linkedList->value;
			}
		}

		return nullptr;
	}
	
	void HashGetter::Update(const UpdateOperation& updateOperation, Data& value)
	{
		if (updateOperation == UpdateOperation::insert) {
			Insert(value);
		}
		else {
			Remove(value);
		}
	}
}