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
		delete value;
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

	HashGetter::LinkedList::LinkedList()
	{
		value = nullptr;
		next = nullptr;
	}

	HashGetter::LinkedList::~LinkedList()
	{
		delete next;
	}

	size_t HashGetter::HashInt(const int& value) const
	{
		return value % m_Capacity;
	}

	size_t HashGetter::HashDouble(const double& value) const
	{
		return (int)value % m_Capacity;
	}

	size_t HashGetter::HashString(const std::string& value) const
	{
		if (value.size() == 0) {
			return 0;
		}

		return (value.size() + value[0]) % m_Capacity;
	}

	void HashGetter::Insert(Data& value, const size_t& hashIndex, LinkedList*& hashTable)
	{
		if (hashTable[hashIndex].value == nullptr) {
			hashTable[hashIndex].value = &value;
			return;
		}

		if (hashTable[hashIndex].next == nullptr) {
			hashTable[hashIndex].next = new LinkedList();
			hashTable[hashIndex].next->value = &value;
			return;
		}

		LinkedList* linkedList = hashTable[hashIndex].next;
		while (linkedList->next != nullptr) {
			if (linkedList->value == &value) {
				return;
			}

			linkedList = linkedList->next;
		}

		linkedList->next = new LinkedList();
		linkedList->next->value = &value;
	}

	HashGetter::HashGetter(std::vector<std::vector<Data>>& data)
	{
		m_Capacity = data.size() * 2;
		m_IntHashTable = new LinkedList[m_Capacity];
		m_DoubleHashTable = new LinkedList[m_Capacity];
		m_StringHashTable = new LinkedList[m_Capacity];

		for (int i = 0; i < data.size(); ++i) {
			for (int j = 0; j < data[i].size(); ++j) {
				Insert(data[i][j], HashInt(data[i][j].intField), m_IntHashTable);
				Insert(data[i][j], HashDouble(data[i][j].doubleField), m_DoubleHashTable);
				Insert(data[i][j], HashString(data[i][j].stringField), m_StringHashTable);
			}
		}
	}

	HashGetter::~HashGetter()
	{
		delete[] m_IntHashTable;
		delete[] m_DoubleHashTable;
		delete[] m_StringHashTable;
	}

	Data* HashGetter::SearchByInt(const int& value) const
	{
		size_t hashIndex = HashInt(value);

		if (m_IntHashTable[hashIndex].value == nullptr) {
			return nullptr;
		}

		if (m_IntHashTable[hashIndex].value->intField == value) {
			return m_IntHashTable[hashIndex].value;
		}

		if (m_IntHashTable[hashIndex].next == nullptr) {
			return nullptr;
		}

		LinkedList* linkedList = &m_IntHashTable[hashIndex];
		while (linkedList->next != nullptr) {
			linkedList = linkedList->next;

			if (linkedList->value->intField == value) {
				return linkedList->value;
			}
		}

		return nullptr;
	}

	Data* HashGetter::SearchByDouble(const double& value) const
	{
		size_t hashIndex = HashDouble(value);

		if (m_DoubleHashTable[hashIndex].value == nullptr) {
			return nullptr;
		}

		if (m_DoubleHashTable[hashIndex].value->doubleField == value) {
			return m_DoubleHashTable[hashIndex].value;
		}

		if (m_DoubleHashTable[hashIndex].next == nullptr) {
			return nullptr;
		}

		LinkedList* linkedList = &m_DoubleHashTable[hashIndex];
		while (linkedList->next != nullptr) {
			linkedList = linkedList->next;

			if (linkedList->value->doubleField == value) {
				return linkedList->value;
			}
		}

		return nullptr;
	}

	Data* HashGetter::SearchByString(const std::string& value) const
	{
		size_t hashIndex = HashString(value);

		if (m_StringHashTable[hashIndex].value == nullptr) {
			return nullptr;
		}

		if (m_StringHashTable[hashIndex].value->stringField == value) {
			return m_IntHashTable[hashIndex].value;
		}

		if (m_StringHashTable[hashIndex].next == nullptr) {
			return nullptr;
		}

		LinkedList* linkedList = &m_StringHashTable[hashIndex];
		while (linkedList->next != nullptr) {
			linkedList = linkedList->next;

			if (linkedList->value->stringField == value) {
				return linkedList->value;
			}
		}

		return nullptr;
	}
}