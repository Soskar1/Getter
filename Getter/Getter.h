#ifndef GETTER_H
#define GETTER_H

#include <vector>
#include <type_traits>
#include "Data.h"

namespace Getter {
	enum UpdateOperation {
		insert,
		remove
	};

	template<class Structure, typename Key>
	auto GetFieldValue(const Structure& structure, Key key) {
		return structure.*key;
	}

	template<class Structure, typename Key>
	class TreeGetter {
	private:
		struct Node {
			Structure* structureRef;
			int height;
			Node* left;
			Node* right;

			Node(Structure& structure);
			~Node();

			int CalculateBalanceFactor() const;
			void UpdateHeight();
		};

		Node* m_Root;
		Key m_Key;

		Node* RotateLeft(Node*& root, Node* node);
		Node* RotateRight(Node*& root, Node* node);

		Node* Insert(Node* node, Structure& structure);
		Node* Remove(Node* node, Structure& structure);

		Node* GetMinimumNode(Node* node) const;
	public:
		using KeyDataType = typename std::remove_pointer<
			typename std::remove_reference<Key>::type>::type;

		TreeGetter();
		TreeGetter(std::vector<std::vector<Structure>>& data);
		~TreeGetter();

		void Create(std::vector<std::vector<Structure>>& data);

		Structure* Search(const KeyDataType& value) const;

		void Update(const UpdateOperation& updateOperation, Structure& value);
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

	template<class Structure, typename Key>
	TreeGetter<Structure, Key>::Node::Node(Structure& value)
	{
		this->structureRef = &value;
		height = 0;
		left = nullptr;
		right = nullptr;
	}

	template<class Structure, typename Key>
	inline TreeGetter<Structure, Key>::Node::~Node()
	{
		delete left;
		delete right;
	}

	template<class Structure, typename Key>
	int TreeGetter<Structure, Key>::Node::CalculateBalanceFactor() const
	{
		int balanceFactor = 0;

		if (this->left != nullptr && this->right != nullptr) {
			balanceFactor = this->left->height - this->right->height;
		}
		else if (this->left != nullptr && this->right == nullptr) {
			balanceFactor = this->left->height;
		}
		else if (this->left == nullptr && this->right != nullptr) {
			balanceFactor = -this->right->height;
		}

		return balanceFactor;
	}

	template<class Structure, typename Key>
	inline void TreeGetter<Structure, Key>::Node::UpdateHeight()
	{
		if (this->left != nullptr && this->right != nullptr) {
			this->height = std::max(this->left->height, this->right->height) + 1;
		}
		else if (this->left != nullptr && this->right == nullptr) {
			this->height = this->left->height + 1;
		}
		else if (this->left == nullptr && this->right != nullptr) {
			this->height = this->right->height + 1;
		}
		else {
			this->height = 1;
		}
	}

	template<class Structure, typename Key>
	typename TreeGetter<Structure, Key>::Node* TreeGetter<Structure, Key>::RotateLeft(Node*& root, Node* node)
	{
		Node* rightChild = node->right;
		node->right = rightChild->left;
		rightChild->left = node;

		node->UpdateHeight();
		rightChild->UpdateHeight();

		if (root == node) {
			root = rightChild;
		}

		return rightChild;
	}

	template<class Structure, typename Key>
	typename TreeGetter<Structure, Key>::Node* TreeGetter<Structure, Key>::RotateRight(Node*& root, Node* node)
	{
		Node* leftChild = node->left;
		node->left = leftChild->right;
		leftChild->right = node;

		node->UpdateHeight();
		leftChild->UpdateHeight();

		if (root == node) {
			root = leftChild;
		}

		return leftChild;
	}
	
	template<class Structure, typename Key>
	typename TreeGetter<Structure, Key>::Node* TreeGetter<Structure, Key>::Insert(Node* node, Structure& structure)
	{
		if (node == nullptr) {
			node = new Node(structure);
			return node;
		}

		if (GetFieldValue(structure, m_Key) < GetFieldValue(node->value, m_Key)) {
			node->left = Insert(node->left, structure);
		}
		else if (GetFieldValue(structure, m_Key) > GetFieldValue(node->value, m_Key)) {
			node->right = Insert(node->right, structure);
		}
		else {
			return node;
		}

		node->UpdateHeight();

		int balanceFactor = node->CalculateBalanceFactor();
		
		if (balanceFactor > 1 && GetFieldValue(structure, m_Key) < GetFieldValue(node->left->value, m_Key)) {
			return RotateRight(m_Root, node);
		}
		
		if (balanceFactor < -1 && GetFieldValue(structure, m_Key) > GetFieldValue(node->right->value, m_Key)) {
			return RotateLeft(m_Root, node);
		}

		if (balanceFactor > 1 && GetFieldValue(structure, m_Key) > GetFieldValue(node->left->value, m_Key)) {
			node->left = RotateLeft(m_Root, node->left);
			return RotateRight(m_Root, node);
		}

		if (balanceFactor < -1 && GetFieldValue(structure, m_Key) < GetFieldValue(node->right->value, m_Key)) {
			node->right = RotateRight(m_Root, node->right);
			return RotateLeft(m_Root, node);
		}

		return node;
	}
	
	template<class Structure, typename Key>
	typename TreeGetter<Structure, Key>::Node* TreeGetter<Structure, Key>::Remove(Node* node, Structure& structure)
	{
		if (node == nullptr) {
			return node;
		}

		if (GetFieldValue(structure, m_Key) < GetFieldValue(node->value, m_Key)) {
			node->left = Remove(node->left, structure);
		}
		else if (GetFieldValue(structure, m_Key) > GetFieldValue(node->value, m_Key)) {
			node->right = Remove(node->right, structure);
		}
		else {
			if (node->left == nullptr || node->right == nullptr) {
				Node* tmp = node->left ? node->left : node->right;
				if (tmp == nullptr) {
					tmp = node;
					node = nullptr;
				}
				else {
					*node = *tmp;
				}

				delete tmp;
			}
			else {
				Node* tmp = GetMinimumNode(node->right);
				node->value = tmp->value;
				node->right = Remove(node->right, *tmp->value);
			}
		}

		if (node == nullptr) {
			return node;
		}

		node->UpdateHeight();

		int balanceFactor = node->CalculateBalanceFactor();
		if (balanceFactor > 1) {
			if (node->left->CalculateBalanceFactor() >= 0) {
				return RotateRight(m_Root, node);
			}
			else {
				node->left = RotateLeft(m_Root, node->left);
				return RotateRight(m_Root, node);
			}
		}
		else if (balanceFactor < -1) {
			if (node->right->CalculateBalanceFactor() <= 0) {
				return RotateLeft(m_Root, node);
			}
			else {
				node->right = RotateRight(m_Root, node->right);
				return RotateLeft(m_Root, node);
			}
		}

		return node;
	}

	template<class Structure, typename Key>
	typename TreeGetter<Structure, Key>::Node* TreeGetter<Structure, Key>::GetMinimumNode(Node* node) const
	{
		Node* current = node;
		while (current->left != nullptr) {
			current = current->left;
		}

		return current;
	}

	template<class Structure, typename Key>
	inline TreeGetter<Structure, Key>::TreeGetter()
	{
		m_Root = nullptr;
	}

	template<class Structure, typename Key>
	inline TreeGetter<Structure, Key>::TreeGetter(std::vector<std::vector<Structure>>& data)
	{
		Create(data);
	}

	template<class Structure, typename Key>
	inline TreeGetter<Structure, Key>::~TreeGetter()
	{
		delete m_Root;
	}

	template<class Structure, typename Key>
	inline void TreeGetter<Structure, Key>::Create(std::vector<std::vector<Structure>>& data)
	{
		if (m_Root != nullptr) {
			delete m_Root;
		}

		m_Root = nullptr;

		for (int i = 0; i < data.size(); ++i) {
			for (int j = 0; j < data[i].size(); ++j) {
				m_Root = Insert(m_Root, data[i][j]);
			}
		}
	}

	template<class Structure, typename Key>
	inline Structure* TreeGetter<Structure, Key>::Search(const KeyDataType& value) const
	{
		if (m_Root == nullptr) {
			return nullptr;
		}

		Node* focusNode = m_Root;
		while (focusNode != nullptr) {
			if (value == GetFieldValue(focusNode->value, m_Key)) {
				return focusNode->value;
			}

			if (value < GetFieldValue(focusNode->value, m_Key)) {
				focusNode = focusNode->left;
			}
			else if (value > GetFieldValue(focusNode->value, m_Key)) {
				focusNode = focusNode->right;
			}
		}

		return nullptr;
	}

	template<class Structure, typename Key>
	inline void TreeGetter<Structure, Key>::Update(const UpdateOperation& updateOperation, Structure& value)
	{
		if (updateOperation == UpdateOperation::insert) {
			m_Root = Insert(m_Root, value);
		}
		else {
			m_Root = Remove(m_Root, value);
		}
	}
}
#endif