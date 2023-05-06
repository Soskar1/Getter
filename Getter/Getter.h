#ifndef GETTER_H
#define GETTER_H

#include <vector>
#include "Data.h"

namespace Getter {
	enum UpdateOperation {
		insert,
		remove
	};

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
		
		Node* IntRemove(Node* node, Data& value);
		Node* StringRemove(Node* node, Data& value);
		Node* DoubleRemove(Node* node, Data& value);

		Node* GetMinimumNode(Node* node) const;

		void Insert(Data& value);
		void Remove(Data& value);
	public:
		TreeGetter();
		TreeGetter(std::vector<std::vector<Data>>& data);
		~TreeGetter();

		void Create(std::vector<std::vector<Data>>& data);

		Data* SearchByInt(const int& value) const;
		Data* SearchByDouble(const double& value) const;
		Data* SearchByString(const std::string& value) const;

		void Update(const UpdateOperation& updateOperation, Data& value);
	};

	class HashGetter {
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
	};
}
#endif