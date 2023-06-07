#ifndef AVLTREE_H
#define AVLTREE_H

#include <cstdlib>
#include <algorithm>

template <typename T>
class AVLTree {
private:
	struct Node {
		const T* value;
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
	Compare m_CompareFunctor;

	Node* RotateLeft(Node* node);
	Node* RotateRight(Node* node);

	Node* Insert(Node* node, const T& value);
	Node* Remove(Node* node, const T& value);

	Node* GetMinimumNode(Node* node) const;
public:
	AVLTree();
	~AVLTree();

	void Insert(const T& value);
	void Remove(const T& value);
	void Edit(const T& oldValue, const T& newValue);

	bool Contains(const T& value) const;

	size_t Size() const;
};

template<typename T>
inline AVLTree<T>::Node::Node(const T& value)
{
	this->value = &value;
	height = 1;
	left = nullptr;
	right = nullptr;
}

template<typename T>
inline AVLTree<T>::Node::~Node()
{
	delete left;
	delete right;
}

template<typename T>
int AVLTree<T>::Node::CalculateBalanceFactor() const
{
	return left->GetHeight() - right->GetHeight();
}

template<typename T>
inline int AVLTree<T>::Node::GetHeight() const
{
	if (this == nullptr)
		return 0;

	return height;
}

template<typename T>
inline void AVLTree<T>::Node::UpdateHeight()
{
	height = std::max(left->GetHeight(), right->GetHeight()) + 1;
}

template<typename T>
typename AVLTree<T>::Node* AVLTree<T>::RotateLeft(Node* node)
{
	Node* rightNode = node->right;
	Node* rightLeftNode = rightNode->left;

	rightNode->left = node;
	node->right = rightLeftNode;

	node->UpdateHeight();
	rightNode->UpdateHeight();

	return rightNode;
}

template<typename T>
typename AVLTree<T>::Node* AVLTree<T>::RotateRight(Node* node)
{
	Node* leftNode = node->left;
	Node* leftRightNode = leftNode->right;

	leftNode->right = node;
	node->left = leftRightNode;

	node->UpdateHeight();
	leftNode->UpdateHeight();

	return leftNode;
}

template<typename T>
typename AVLTree<T>::Node* AVLTree<T>::Insert(Node* node, const T& value)
{
	if (node == nullptr) {
		node = new Node(value);
		++m_Size;
		return node;
	}

	if (value < *node->value) {
		node->left = Insert(node->left, value);
	}
	else if (value > *node->value) {
		node->right = Insert(node->right, value);
	}
	else {
		return node;
	}

	node->UpdateHeight();

	int balanceFactor = node->CalculateBalanceFactor();

	if (balanceFactor > 1 && value < *node->left->value) {
		return RotateRight(node);
	}

	if (balanceFactor < -1 && value > *node->right->value) {
		return RotateLeft(node);
	}

	if (balanceFactor > 1 && value > *node->left->value) {
		node->left = RotateLeft(node->left);
		return RotateRight(node);
	}

	if (balanceFactor < -1 && value < *node->right->value) {
		node->right = RotateRight(node->right);
		return RotateLeft(node);
	}

	return node;
}

template<typename T>
typename AVLTree<T>::Node* AVLTree<T>::Remove(Node* node, const T& value)
{
	if (node == nullptr) {
		return node;
	}

	if (value < *node->value) {
		node->left = Remove(node->left, value);
	}
	else if (value > *node->value) {
		node->right = Remove(node->right, value);
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

			--m_Size;
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

template<typename T>
typename AVLTree<T>::Node* AVLTree<T>::GetMinimumNode(Node* node) const
{
	Node* current = node;
	while (current->left != nullptr) {
		current = current->left;
	}

	return current;
}

template<typename T>
inline AVLTree<T>::AVLTree()
{
	m_Root = nullptr;
	m_Size = 0;
}

template<typename T>
inline AVLTree<T>::~AVLTree()
{
	delete m_Root;
}

template<typename T>
inline void AVLTree<T>::Insert(const T& value)
{
	m_Root = Insert(m_Root, value);
}

template<typename T>
inline void AVLTree<T>::Remove(const T& value)
{
	m_Root = Remove(m_Root, value);
}

template<typename T>
inline void AVLTree<T>::Edit(const T& oldValue, const T& newValue)
{
	if (!Contains(oldValue)) {
		return;
	}

	m_Root = Remove(m_Root, oldValue);
	m_Root = Insert(m_Root, newValue);
}

template<typename T>
inline bool AVLTree<T>::Contains(const T& value) const
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

template<typename T>
inline size_t AVLTree<T>::Size() const
{
	return m_Size;
}

#endif