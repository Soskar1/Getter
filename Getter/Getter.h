#ifndef GETTER_H
#define GETTER_H

#include <vector>
#include "AVLTree.h"

namespace Getter {
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
		void Create(const Container& container);

		Structure* Search(const FieldDataType& value) const;

		void Insert(const Structure& value);
		void Remove(const Structure& value);
	};

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
	inline void TreeGetter<Structure, FieldDataType>::Create(const Container& container)
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
	inline void TreeGetter<Structure, FieldDataType>::Insert(const Structure& value)
	{
		Structure* structureRef = const_cast<Structure*>(&value);
		m_AVLTree.Insert(structureRef);
	}

	template<class Structure, typename FieldDataType>
	inline void TreeGetter<Structure, FieldDataType>::Remove(const Structure& value)
	{
		Structure* structureRef = const_cast<Structure*>(&value);
		m_AVLTree.Remove(structureRef);
	}
}
#endif