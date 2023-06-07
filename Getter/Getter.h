#ifndef GETTER_H
#define GETTER_H

#include <vector>
#include "AVLTree.h"

namespace Getter {
	enum UpdateOperation {
		insert,
		remove
	};

	template <class Structure, typename Field, typename FieldDataType>
	FieldDataType GetFieldValue(const Structure& structure, Field Structure::* field)
	{
		return structure.*field;
	}

	template<class Structure, typename FieldDataType>
	class TreeGetter {
	private:
		using Field = FieldDataType Structure::*;

		Tree::AVLTree<Structure*> m_AVLTree;
		Field m_Field;
	public:
		TreeGetter(Field field, const Structure& structure);

		template<class Container>
		void Create(const Container& container);

		Structure* Search(const FieldDataType& value) const;

		void Update(const UpdateOperation& updateOperation, Structure& value);
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
	inline TreeGetter<Structure, FieldDataType>::TreeGetter(Field field, const Structure& structure)
	{
		m_AVLTree = AVLTree<FieldDataType>();
		m_Field = field;
	}

	//template<class Structure, typename FieldDataType>
	//inline FieldDataType TreeGetter<Structure, FieldDataType>::Get()
	//{
	//	return GetFieldValue<Structure, FieldDataType, FieldDataType>(*m_StructureRef, m_Field);
	//}

	//template<class Structure, typename Key>
	//inline void TreeGetter<Structure, Key>::Create(const std::vector<std::vector<Structure>>& data)
	//{
	//	for (int i = 0; i < data.size(); ++i) {
	//		for (int j = 0; j < data[i].size(); ++j) {
	//			//avlTree.Insert
	//		}
	//	}
	//}

	template<class Structure, typename FieldDataType>
	template<class Container>
	inline void TreeGetter<Structure, FieldDataType>::Create(const Container& container)
	{
		for (int i = 0; i < container.size(); ++i) {
			for (int j = 0; j < data[i].size(); ++j) {
				m_AVLTree.Insert(&data[i][j]);
			}
		}
	}

	//template<class Structure, typename Key>
	//inline void TreeGetter<Structure, Key>::Update(const UpdateOperation& updateOperation, Structure& value)
	//{
	//	if (updateOperation == UpdateOperation::insert) {
	//		m_Root = Insert(m_Root, value);
	//	}
	//	else {
	//		m_Root = Remove(m_Root, value);
	//	}
	//}
}
#endif