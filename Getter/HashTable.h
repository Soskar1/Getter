#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <list>
#include <cstdlib>
#include <functional>

namespace HashTables {
	template <typename T>
	struct GetValue {
		T operator()(const T& value) const {
			return value;
		}
	};

	template <typename T, typename HashDataType = T, class ValueExtraction = GetValue<T>>
	class HashTable {
	private:
		size_t m_Capacity;
		std::list<T>* m_Table;
		std::hash<HashDataType> m_Hash;

		ValueExtraction m_ValueExtraction;

		size_t Hash(const T& value) const;
	public:
		HashTable(const size_t& capacity);
		HashTable(const size_t& capacity, ValueExtraction valueExtraction);
		~HashTable();

		void Insert(const T& value);
		void Remove(const T& value);
		bool Contains(const T& value) const;
	};

	template<typename T, typename HashDataType, class ValueExtraction>
	inline size_t HashTable<T, HashDataType, ValueExtraction>::Hash(const T& value) const
	{
		return m_Hash((HashDataType)m_ValueExtraction(value)) % m_Capacity;
	}

	template<typename T, typename HashDataType, class ValueExtraction>
	inline HashTable<T, HashDataType, ValueExtraction>::HashTable(const size_t& capacity) {
		m_Capacity = capacity;
		m_Table = new std::list<T>[capacity];
	}

	template<typename T, typename HashDataType, class ValueExtraction>
	inline HashTable<T, HashDataType, ValueExtraction>::HashTable(const size_t& capacity, ValueExtraction valueExtraction)
	{
		m_Capacity = capacity;
		m_Table = new std::list<T>[capacity];
		m_ValueExtraction = valueExtraction;
	}

	template<typename T, typename HashDataType, class ValueExtraction>
	inline HashTable<T, HashDataType, ValueExtraction>::~HashTable() {
		delete[] m_Table;
	}

	template<typename T, typename HashDataType, class ValueExtraction>
	inline void HashTable<T, HashDataType, ValueExtraction>::Insert(const T& value) {
		size_t hashIndex = Hash(value);
		m_Table[hashIndex].push_back(value);
	}

	template<typename T, typename HashDataType, class ValueExtraction>
	inline void HashTable<T, HashDataType, ValueExtraction>::Remove(const T& value)
	{
		size_t hashIndex = Hash(value);
		std::list<T>& list = m_Table[hashIndex];

		auto it = std::find(list.begin(), list.end(), value);

		if (it != list.end()) {
			list.erase(it);
		}
	}

	template<typename T, typename HashDataType, class ValueExtraction>
	inline bool HashTable<T, HashDataType, ValueExtraction>::Contains(const T& value) const
	{
		size_t hashIndex = Hash(value);
		std::list<T>& list = m_Table[hashIndex];

		auto it = std::find(list.begin(), list.end(), value);

		if (it != list.end()) {
			return true;
		}

		return false;
	}
}
#endif