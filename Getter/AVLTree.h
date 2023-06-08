#ifndef AVLTREE_H
#define AVLTREE_H

#include <cstdlib>
#include <algorithm>
#include <vector>

namespace Tree {
	template <typename T>
	struct GetValue {
		T operator()(const T& value) const {
			return value;
		}
	};

	template <typename T, class ValueExtraction = GetValue<T>>
	class AVLTree {
	private:
		struct Node {
			std::vector<T> values;
			int height;
			Node* left;
			Node* right;

			Node(const T& value);
			~Node();

			int CalculateBalanceFactor() const;
			int GetHeight() const;
			void UpdateHeight();
		};

		Node* m_Root;
		size_t m_Size;
		ValueExtraction m_ValueExtraction;

		Node* RotateLeft(Node* node);
		Node* RotateRight(Node* node);

		Node* Insert(Node* node, const T& value);
		Node* Remove(Node* node, const T& value);

		Node* GetMinimumNode(Node* node) const;
	public:
		AVLTree();
		AVLTree(ValueExtraction valueExtraction);
		~AVLTree();

		void Insert(const T& value);
		void Remove(const T& value);
		void Edit(const T& oldValue, const T& newValue);

		bool Contains(const T& value) const;

		size_t Size() const;
	};

	template<typename T, class ValueExtraction>
	inline AVLTree<T, ValueExtraction>::Node::Node(const T& value)
	{
		values.push_back(value);
		height = 1;
		left = nullptr;
		right = nullptr;
	}

	template<typename T, class ValueExtraction>
	inline AVLTree<T, ValueExtraction>::Node::~Node()
	{
		delete left;
		delete right;
	}

	template<typename T, class ValueExtraction>
	int AVLTree<T, ValueExtraction>::Node::CalculateBalanceFactor() const
	{
		return left->GetHeight() - right->GetHeight();
	}

	template<typename T, class ValueExtraction>
	inline int AVLTree<T, ValueExtraction>::Node::GetHeight() const
	{
		if (this == nullptr)
			return 0;

		return height;
	}

	template<typename T, class ValueExtraction>
	inline void AVLTree<T, ValueExtraction>::Node::UpdateHeight()
	{
		height = std::max(left->GetHeight(), right->GetHeight()) + 1;
	}

	template<typename T, class ValueExtraction>
	typename AVLTree<T, ValueExtraction>::Node* AVLTree<T, ValueExtraction>::RotateLeft(Node* node)
	{
		Node* rightNode = node->right;
		Node* rightLeftNode = rightNode->left;

		rightNode->left = node;
		node->right = rightLeftNode;

		node->UpdateHeight();
		rightNode->UpdateHeight();

		return rightNode;
	}

	template<typename T, class ValueExtraction>
	typename AVLTree<T, ValueExtraction>::Node* AVLTree<T, ValueExtraction>::RotateRight(Node* node)
	{
		Node* leftNode = node->left;
		Node* leftRightNode = leftNode->right;

		leftNode->right = node;
		node->left = leftRightNode;

		node->UpdateHeight();
		leftNode->UpdateHeight();

		return leftNode;
	}

	template<typename T, class ValueExtraction>
	typename AVLTree<T, ValueExtraction>::Node* AVLTree<T, ValueExtraction>::Insert(Node* node, const T& value)
	{
		if (node == nullptr) {
			node = new Node(value);
			++m_Size;
			return node;
		}

		if (m_ValueExtraction(value) < m_ValueExtraction(node->values[0])) {
			node->left = Insert(node->left, value);
		}
		else if (m_ValueExtraction(value) > m_ValueExtraction(node->values[0])) {
			node->right = Insert(node->right, value);
		}
		else {
			node->values.push_back(value);
			++m_Size;
			return node;
		}

		node->UpdateHeight();

		int balanceFactor = node->CalculateBalanceFactor();

		if (balanceFactor > 1 && m_ValueExtraction(value) < m_ValueExtraction(node->left->values[0])) {
			return RotateRight(node);
		}

		if (balanceFactor < -1 && m_ValueExtraction(value) > m_ValueExtraction(node->right->values[0])) {
			return RotateLeft(node);
		}

		if (balanceFactor > 1 && m_ValueExtraction(value) > m_ValueExtraction(node->left->values[0])) {
			node->left = RotateLeft(node->left);
			return RotateRight(node);
		}

		if (balanceFactor < -1 && m_ValueExtraction(value) < m_ValueExtraction(node->right->values[0])) {
			node->right = RotateRight(node->right);
			return RotateLeft(node);
		}

		return node;
	}

	template<typename T, class ValueExtraction>
	typename AVLTree<T, ValueExtraction>::Node* AVLTree<T, ValueExtraction>::Remove(Node* node, const T& value)
	{
		if (node == nullptr) {
			return node;
		}

		if (m_ValueExtraction(value) < m_ValueExtraction(node->values[0])) {
			node->left = Remove(node->left, value);
		}
		else if (m_ValueExtraction(value) > m_ValueExtraction(node->values[0])) {
			node->right = Remove(node->right, value);
		}
		else {
			auto it = std::find(node->values.begin(), node->values.end(), value);

			if (it == node->values.end()) {
				return node;
			}

			node->values.erase(it);

			if (node->values.size() != 0) {
				--m_Size;
				return node;
			}

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

				--m_Size;
			}
			else {
				Node* tmp = GetMinimumNode(node->right);
				node->values = tmp->values;
				node->right = Remove(node->right, tmp->values[0]);
			}
		}

		if (node == nullptr) {
			return node;
		}

		node->UpdateHeight();

		int balanceFactor = node->CalculateBalanceFactor();
		if (balanceFactor > 1) {
			if (node->left->CalculateBalanceFactor() >= 0) {
				return RotateRight(node);
			}
			else {
				node->left = RotateLeft(node->left);
				return RotateRight(node);
			}
		}
		else if (balanceFactor < -1) {
			if (node->right->CalculateBalanceFactor() <= 0) {
				return RotateLeft(node);
			}
			else {
				node->right = RotateRight(node->right);
				return RotateLeft(node);
			}
		}

		return node;
	}

	template<typename T, class ValueExtraction>
	typename AVLTree<T, ValueExtraction>::Node* AVLTree<T, ValueExtraction>::GetMinimumNode(Node* node) const
	{
		Node* current = node;
		while (current->left != nullptr) {
			current = current->left;
		}

		return current;
	}

	template<typename T, class ValueExtraction>
	inline AVLTree<T, ValueExtraction>::AVLTree()
	{
		m_Root = nullptr;
		m_Size = 0;
	}

	template<typename T, class ValueExtraction>
	inline AVLTree<T, ValueExtraction>::AVLTree(ValueExtraction valueExtraction)
	{
		m_Root = nullptr;
		m_Size = 0;
		m_ValueExtraction = valueExtraction;
	}

	template<typename T, class ValueExtraction>
	inline AVLTree<T, ValueExtraction>::~AVLTree()
	{
		delete m_Root;
	}

	template<typename T, class ValueExtraction>
	inline void AVLTree<T, ValueExtraction>::Insert(const T& value)
	{
		m_Root = Insert(m_Root, value);
	}

	template<typename T, class ValueExtraction>
	inline void AVLTree<T, ValueExtraction>::Remove(const T& value)
	{
		m_Root = Remove(m_Root, value);
	}

	template<typename T, class ValueExtraction>
	inline void AVLTree<T, ValueExtraction>::Edit(const T& oldValue, const T& newValue)
	{
		if (!Contains(oldValue)) {
			return;
		}

		m_Root = Remove(m_Root, oldValue);
		m_Root = Insert(m_Root, newValue);
	}

	template<typename T, class ValueExtraction>
	inline bool AVLTree<T, ValueExtraction>::Contains(const T& value) const
	{
		if (m_Root == nullptr) {
			return false;
		}

		Node* focusNode = m_Root;
		while (focusNode != nullptr) {
			if (value == *focusNode->value) {
				return true;
			}

			if (value < *focusNode->value) {
				focusNode = focusNode->left;
			}
			else if (value > *focusNode->value) {
				focusNode = focusNode->right;
			}
		}

		return false;
	}

	template<typename T, class ValueExtraction>
	inline size_t AVLTree<T, ValueExtraction>::Size() const
	{
		return m_Size;
	}
}
#endif