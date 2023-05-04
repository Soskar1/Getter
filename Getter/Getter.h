#ifndef GETTER_H
#define GETTER_H

#include <vector>
#include "Data.h"

namespace Getter {
	class TreeGetter {
	private:
		struct Node {
			Data* value;
			int height;
			Node* left;
			Node* right;

			Node(Data& value);
			~Node();

			int CalculateBalanceFactor() const;
			void UpdateHeight();
		};

		Node* m_IntRoot;
		Node* m_StringRoot;
		Node* m_DoubleRoot;

		Node* RotateLeft(Node** root, Node* node);
		Node* RotateRight(Node** root, Node* node);

		Node* IntInsert(Node* node, Data& value);
		Node* StringInsert(Node* node, Data& value);
		Node* DoubleInsert(Node* node, Data& value);
	public:
		TreeGetter(std::vector<std::vector<Data>>& data);
		~TreeGetter();

		Data* SearchByInt(const int& value) const;
		Data* SearchByDouble(const double& value) const;
		Data* SearchByString(const std::string& value) const;
	};

	class HashGetter {
		struct LinkedList {
			LinkedList* next;
			Data* value;

			LinkedList();
			~LinkedList();
		};

		size_t HashInt(const int& value) const;
		size_t HashDouble(const double& value) const;
		size_t HashString(const std::string& value) const;

		LinkedList* m_IntHashTable;
		LinkedList* m_DoubleHashTable;
		LinkedList* m_StringHashTable;
		size_t m_Capacity;

		void Insert(Data& value, const size_t& hashIndex, LinkedList*& hashTable);
	public:
		HashGetter(std::vector<std::vector<Data>>& data);
		~HashGetter();

		Data* SearchByInt(const int& value) const;
		Data* SearchByDouble(const double& value) const;
		Data* SearchByString(const std::string& value) const;
	};
}
#endif