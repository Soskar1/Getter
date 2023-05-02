#include "Getter.h"

namespace Getter {
	TreeGetter::Node::Node(Data& value)
	{
		this->value = &value;
		height = 0;
		left = nullptr;
		right = nullptr;
	}

	TreeGetter::Node::~Node()
	{
		delete left;
		delete right;
	}

	int TreeGetter::Node::CalculateBalanceFactor() const
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

	void TreeGetter::Node::UpdateHeight()
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

	TreeGetter::Node* TreeGetter::RotateLeft(Node** root, Node* node)
	{
		Node* rightChild = node->right;
		node->right = rightChild->left;
		rightChild->left = node;

		node->UpdateHeight();
		rightChild->UpdateHeight();

		if (*root == node) {
			*root = rightChild;
		}

		return rightChild;
	}

	TreeGetter::Node* TreeGetter::RotateRight(Node** root, Node* node)
	{
		Node* leftChild = node->left;
		node->left = leftChild->right;
		leftChild->right = node;

		node->UpdateHeight();
		leftChild->UpdateHeight();

		if (*root == node) {
			*root = leftChild;
		}

		return leftChild;
	}

	TreeGetter::Node* TreeGetter::IntInsert(Node* node, Data& value)
	{
		if (node == nullptr) {
			node = new Node(value);
			return node;
		}

		if (value.intField < node->value->intField) {
			node->left = IntInsert(node->left, value);
		}
		else if (value.intField > node->value->intField) {
			node->right = IntInsert(node->right, value);
		}
		else {
			return node;
		}

		node->UpdateHeight();

		int balanceFactor = node->CalculateBalanceFactor();

		if (balanceFactor > 1 && value.intField < node->left->value->intField) {
			return RotateRight(&m_IntRoot, node);
		}

		if (balanceFactor < -1 && value.intField > node->right->value->intField) {
			return RotateLeft(&m_IntRoot, node);
		}

		if (balanceFactor > 1 && value.intField > node->left->value->intField) {
			node->left = RotateLeft(&m_IntRoot, node->left);
			return RotateRight(&m_IntRoot, node);
		}

		if (balanceFactor < -1 && value.intField < node->right->value->intField) {
			node->right = RotateRight(&m_IntRoot, node->right);
			return RotateLeft(&m_IntRoot, node);
		}

		return node;
	}

	TreeGetter::Node* TreeGetter::StringInsert(Node* node, Data& value)
	{
		if (node == nullptr) {
			node = new Node(value);
			return node;
		}

		if (value.stringField < node->value->stringField) {
			node->left = StringInsert(node->left, value);
		}
		else if (value.stringField > node->value->stringField) {
			node->right = StringInsert(node->right, value);
		}
		else {
			return node;
		}

		node->UpdateHeight();

		int balanceFactor = node->CalculateBalanceFactor();

		if (balanceFactor > 1 && value.stringField < node->left->value->stringField) {
			return RotateRight(&m_StringRoot, node);
		}

		if (balanceFactor < -1 && value.stringField > node->right->value->stringField) {
			return RotateLeft(&m_StringRoot, node);
		}

		if (balanceFactor > 1 && value.stringField > node->left->value->stringField) {
			node->left = RotateLeft(&m_StringRoot, node->left);
			return RotateRight(&m_StringRoot, node);
		}

		if (balanceFactor < -1 && value.stringField < node->right->value->stringField) {
			node->right = RotateRight(&m_StringRoot, node->right);
			return RotateLeft(&m_StringRoot, node);
		}

		return node;
	}

	TreeGetter::Node* TreeGetter::DoubleInsert(Node* node, Data& value)
	{
		if (node == nullptr) {
			node = new Node(value);
			return node;
		}

		if (value.doubleField < node->value->doubleField) {
			node->left = DoubleInsert(node->left, value);
		}
		else if (value.doubleField > node->value->doubleField) {
			node->right = DoubleInsert(node->right, value);
		}
		else {
			return node;
		}

		node->UpdateHeight();

		int balanceFactor = node->CalculateBalanceFactor();

		if (balanceFactor > 1 && value.doubleField < node->left->value->doubleField) {
			return RotateRight(&m_DoubleRoot, node);
		}

		if (balanceFactor < -1 && value.doubleField > node->right->value->doubleField) {
			return RotateLeft(&m_DoubleRoot, node);
		}

		if (balanceFactor > 1 && value.doubleField > node->left->value->doubleField) {
			node->left = RotateLeft(&m_DoubleRoot, node->left);
			return RotateRight(&m_DoubleRoot, node);
		}

		if (balanceFactor < -1 && value.doubleField < node->right->value->doubleField) {
			node->right = RotateRight(&m_DoubleRoot, node->right);
			return RotateLeft(&m_DoubleRoot, node);
		}

		return node;
	}

	TreeGetter::TreeGetter(std::vector<std::vector<Data>>& data)
	{
		m_IntRoot = nullptr;
		m_StringRoot = nullptr;
		m_DoubleRoot = nullptr;

		for (int i = 0; i < data.size(); ++i) {
			for (int j = 0; j < data[i].size(); ++j) {
				m_IntRoot = IntInsert(m_IntRoot, data[i][j]);
				m_StringRoot = StringInsert(m_StringRoot, data[i][j]);
				m_DoubleRoot = DoubleInsert(m_DoubleRoot, data[i][j]);
			}
		}
	}

	TreeGetter::~TreeGetter()
	{
		delete m_IntRoot;
		delete m_StringRoot;
		delete m_DoubleRoot;
	}

	Data* TreeGetter::SearchByInt(const int& value) const
	{
		if (m_IntRoot == nullptr) {
			return nullptr;
		}

		Node* focusNode = m_IntRoot;
		while (focusNode != nullptr) {
			if (value == focusNode->value->intField) {
				return focusNode->value;
			}

			if (value < focusNode->value->intField) {
				focusNode = focusNode->left;
			}
			else if (value > focusNode->value->intField) {
				focusNode = focusNode->right;
			}
		}

		return nullptr;
	}

	Data* TreeGetter::SearchByDouble(const double& value) const
	{
		if (m_DoubleRoot == nullptr) {
			return nullptr;
		}

		Node* focusNode = m_DoubleRoot;
		while (focusNode != nullptr) {
			if (value == focusNode->value->doubleField) {
				return focusNode->value;
			}

			if (value < focusNode->value->doubleField) {
				focusNode = focusNode->left;
			}
			else if (value > focusNode->value->doubleField) {
				focusNode = focusNode->right;
			}
		}

		return nullptr;
	}

	Data* TreeGetter::SearchByString(const std::string& value) const
	{
		if (m_StringRoot == nullptr) {
			return nullptr;
		}

		Node* focusNode = m_StringRoot;
		while (focusNode != nullptr) {
			if (value == focusNode->value->stringField) {
				return focusNode->value;
			}

			if (value < focusNode->value->stringField) {
				focusNode = focusNode->left;
			}
			else if (value > focusNode->value->stringField) {
				focusNode = focusNode->right;
			}
		}

		return nullptr;
	}
}