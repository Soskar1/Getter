#ifndef GETTER_H
#define GETTER_H

#include <vector>
#include "AVLTree.h"

namespace Getter {
	enum UpdateOperation {
		insert,
		remove
	};

	template<class Structure, typename FieldDataType>
	class TreeGetter {
	private:
		using Field = FieldDataType Structure::*;
		Field m_Field;

		struct ValueExtraction {
			Field m_Field;

			ValueExtraction() : m_Field(nullptr) {}
			ValueExtraction(Field field) : m_Field(field) {}

			FieldDataType operator()(Structure* structure) const {
				return (*structure).*m_Field;
			}

			ValueExtraction& operator=(const ValueExtraction& valueExtraction) {
				m_Field = valueExtraction.m_Field;

				return *this;
			}
		};

		ValueExtraction m_ValueExtraction;
		Tree::AVLTree<Structure*, ValueExtraction> m_AVLTree;
	public:
		TreeGetter(Field field);

		void Create(std::vector<Structure>& arr);

		template<class Container>
		void Create(Container* container);

		Structure* Search(const FieldDataType& value) const;

		void Update(const UpdateOperation& updateOperation, const Structure& value);
	};

	/*class HashGetter {
		struct LinkedList {
			LinkedList* next;
			Data* value;
			bool allowedToRewrite;

			LinkedList();
			LinkedList(Data& value);
			~LinkedList();
		};

		size_t HashInt(const int& value) const;
		size_t HashDouble(const double& value) const;
		size_t HashString(const std::string& value) const;

		LinkedList* m_IntHashTable;
		LinkedList* m_DoubleHashTable;
		LinkedList* m_StringHashTable;
		size_t m_Capacity;

		void Insert(Data& value);
		void Insert(Data& value, const size_t& hashIndex, LinkedList*& hashTable);

		void Remove(Data& value);
		void Remove(Data& value, const size_t& hashIndex, LinkedList*& hashTable);
	public:
		HashGetter();
		HashGetter(std::vector<std::vector<Data>>& data);
		~HashGetter();

		void Create(std::vector<std::vector<Data>>& data);

		Data* SearchByInt(const int& value) const;
		Data* SearchByDouble(const double& value) const;
		Data* SearchByString(const std::string& value) const;

		void Update(const UpdateOperation& updateOperation, Data& value);
	};*/

	template<class Structure, typename FieldDataType>
	inline TreeGetter<Structure, FieldDataType>::TreeGetter(Field field)
	{
		m_Field = field;
		m_ValueExtraction = ValueExtraction(m_Field);
		m_AVLTree = Tree::AVLTree<Structure*, ValueExtraction>(m_ValueExtraction);
	}

	template<class Structure, typename FieldDataType>
	inline void TreeGetter<Structure, FieldDataType>::Create(std::vector<Structure>& arr)
	{
		for (int i = 0; i < arr.size(); ++i) {
			m_AVLTree.Insert(&arr[i]);
		}
	}

	template<class Structure, typename FieldDataType>
	template<class Container>
	inline void TreeGetter<Structure, FieldDataType>::Create(Container* container)
	{
		for (int i = 0; i < container->size(); ++i) {
			m_AVLTree.Insert(container->getElement(i));
		}
	}

	template<class Structure, typename FieldDataType>
	inline Structure* TreeGetter<Structure, FieldDataType>::Search(const FieldDataType& value) const
	{
		return m_AVLTree.Search(value);
	}

	template<class Structure, typename FieldDataType>
	inline void TreeGetter<Structure, FieldDataType>::Update(const UpdateOperation& updateOperation, const Structure& value)
	{
		if (updateOperation == UpdateOperation::insert) {
			m_AVLTree.Insert(&value);
		}

		if (updateOperation == UpdateOperation::remove) {
			m_AVLTree.Remove(&value);
		}
	}
	
}
#endif