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

	TreeGetter::Node* TreeGetter::IntRemove(Node* node, Data& value)
	{
		if (node == nullptr) {
			return node;
		}

		if (value.intField < node->value->intField) {
			node->left = IntRemove(node->left, value);
		}
		else if (value.intField > node->value->intField) {
			node->right = IntRemove(node->right, value);
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
				node->right = IntRemove(node->right, *tmp->value);
			}
		}

		if (node == nullptr) {
			return node;
		}

		node->UpdateHeight();

		int balanceFactor = node->CalculateBalanceFactor();
		if (balanceFactor > 1) {
			if (node->left->CalculateBalanceFactor() >= 0) {
				return RotateRight(&m_IntRoot, node);
			}
			else {
				node->left = RotateLeft(&m_IntRoot, node->left);
				return RotateRight(&m_IntRoot, node);
			}
		}
		else if (balanceFactor < -1) {
			if (node->right->CalculateBalanceFactor() <= 0) {
				return RotateLeft(&m_IntRoot, node);
			}
			else {
				node->right = RotateRight(&m_IntRoot, node->right);
				return RotateLeft(&m_IntRoot, node);
			}
		}

		return node;
	}

	TreeGetter::Node* TreeGetter::StringRemove(Node* node, Data& value)
	{
		if (node == nullptr) {
			return node;
		}

		if (value.stringField < node->value->stringField) {
			node->left = StringRemove(node->left, value);
		}
		else if (value.stringField > node->value->stringField) {
			node->right = StringRemove(node->right, value);
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
				node->right = StringRemove(node->right, *tmp->value);
			}
		}

		if (node == nullptr) {
			return node;
		}

		node->UpdateHeight();

		int balanceFactor = node->CalculateBalanceFactor();
		if (balanceFactor > 1) {
			if (node->left->CalculateBalanceFactor() >= 0) {
				return RotateRight(&m_StringRoot, node);
			}
			else {
				node->left = RotateLeft(&m_IntRoot, node->left);
				return RotateRight(&m_StringRoot, node);
			}
		}
		else if (balanceFactor < -1) {
			if (node->right->CalculateBalanceFactor() <= 0) {
				return RotateLeft(&m_StringRoot, node);
			}
			else {
				node->right = RotateRight(&m_StringRoot, node->right);
				return RotateLeft(&m_StringRoot, node);
			}
		}

		return node;
	}

	TreeGetter::Node* TreeGetter::DoubleRemove(Node* node, Data& value)
	{
		if (node == nullptr) {
			return node;
		}

		if (value.doubleField < node->value->doubleField) {
			node->left = DoubleRemove(node->left, value);
		}
		else if (value.doubleField > node->value->doubleField) {
			node->right = DoubleRemove(node->right, value);
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
				node->right = DoubleRemove(node->right, *tmp->value);
			}
		}

		if (node == nullptr) {
			return node;
		}

		node->UpdateHeight();

		int balanceFactor = node->CalculateBalanceFactor();
		if (balanceFactor > 1) {
			if (node->left->CalculateBalanceFactor() >= 0) {
				return RotateRight(&m_DoubleRoot, node);
			}
			else {
				node->left = RotateLeft(&m_DoubleRoot, node->left);
				return RotateRight(&m_DoubleRoot, node);
			}
		}
		else if (balanceFactor < -1) {
			if (node->right->CalculateBalanceFactor() <= 0) {
				return RotateLeft(&m_DoubleRoot, node);
			}
			else {
				node->right = RotateRight(&m_DoubleRoot, node->right);
				return RotateLeft(&m_DoubleRoot, node);
			}
		}

		return node;
	}

	TreeGetter::Node* TreeGetter::GetMinimumNode(Node* node) const
	{
		Node* current = node;
		while (current->left != nullptr) {
			current = current->left;
		}

		return current;
	}

	void TreeGetter::Insert(Data& value)
	{
		m_IntRoot = IntInsert(m_IntRoot, value);
		m_StringRoot = StringInsert(m_StringRoot, value);
		m_DoubleRoot = DoubleInsert(m_DoubleRoot, value);
	}

	void TreeGetter::Remove(Data& value)
	{
		m_IntRoot = IntRemove(m_IntRoot, value);
		m_StringRoot = StringRemove(m_StringRoot, value);
		m_DoubleRoot = DoubleRemove(m_DoubleRoot, value);
	}

	TreeGetter::TreeGetter()
	{
		m_IntRoot = nullptr;
		m_StringRoot = nullptr;
		m_DoubleRoot = nullptr;
	}

	TreeGetter::TreeGetter(std::vector<std::vector<Data>>& data)
	{
		Create(data);
	}

	TreeGetter::~TreeGetter()
	{
		delete m_IntRoot;
		delete m_StringRoot;
		delete m_DoubleRoot;
	}

	void TreeGetter::Create(std::vector<std::vector<Data>>& data)
	{
		if (m_IntRoot != nullptr || m_StringRoot != nullptr || m_DoubleRoot != nullptr) {
			delete m_IntRoot;
			delete m_DoubleRoot;
			delete m_StringRoot;
		}

		m_IntRoot = nullptr;
		m_DoubleRoot = nullptr;
		m_StringRoot = nullptr;

		for (int i = 0; i < data.size(); ++i) {
			for (int j = 0; j < data[i].size(); ++j) {
				Insert(data[i][j]);
			}
		}
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

	void TreeGetter::Update(const UpdateOperation& updateOperation, Data& value)
	{
		if (updateOperation == UpdateOperation::insert) {
			Insert(value);
		}
		else {
			Remove(value);
		}
	}

	HashGetter::LinkedList::LinkedList()
	{
		value = nullptr;
		next = nullptr;
		allowedToRewrite = false;
	}

	HashGetter::LinkedList::LinkedList(Data& value)
	{
		this->value = &value;
		next = nullptr;
		allowedToRewrite = false;
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

	void HashGetter::Insert(Data& value)
	{
		Insert(value, HashInt(value.intField), m_IntHashTable);
		Insert(value, HashDouble(value.doubleField), m_DoubleHashTable);
		Insert(value, HashString(value.stringField), m_StringHashTable);
	}

	void HashGetter::Insert(Data& value, const size_t& hashIndex, LinkedList*& hashTable)
	{
		if (hashTable[hashIndex].value == nullptr || hashTable[hashIndex].allowedToRewrite) {
			hashTable[hashIndex].value = &value;
			hashTable[hashIndex].allowedToRewrite = false;
			return;
		}

		if (hashTable[hashIndex].next == nullptr) {
			hashTable[hashIndex].next = new LinkedList();
			hashTable[hashIndex].next->value = &value;
			return;
		}
		else if (hashTable[hashIndex].next->allowedToRewrite) {
			hashTable[hashIndex].next->value = &value;
			hashTable[hashIndex].next->allowedToRewrite = false;
		}

		LinkedList* linkedList = hashTable[hashIndex].next;
		while (linkedList->next != nullptr) {
			if (linkedList->value == &value) {
				return;
			}

			if (linkedList->next->allowedToRewrite) {
				linkedList->next->value = &value;
				linkedList->next->allowedToRewrite = false;
				return;
			}

			linkedList = linkedList->next;
		}

		linkedList->next = new LinkedList();
		linkedList->next->value = &value;
	}

	void HashGetter::Remove(Data& value)
	{
		Remove(value, HashInt(value.intField), m_IntHashTable);
		Remove(value, HashDouble(value.doubleField), m_DoubleHashTable);
		Remove(value, HashString(value.stringField), m_StringHashTable);
	}

	void HashGetter::Remove(Data& value, const size_t& hashIndex, LinkedList*& hashTable)
	{
		LinkedList* linkedList = &hashTable[hashIndex];

		while (linkedList->value != &value) {
			linkedList = linkedList->next;
		}

		linkedList->allowedToRewrite = true;
	}

	HashGetter::HashGetter()
	{
		m_IntHashTable = nullptr;
		m_DoubleHashTable = nullptr;
		m_StringHashTable = nullptr;

		m_Capacity = 0;
	}

	HashGetter::HashGetter(std::vector<std::vector<Data>>& data)
	{
		Create(data);
	}

	HashGetter::~HashGetter()
	{
		delete[] m_IntHashTable;
		delete[] m_DoubleHashTable;
		delete[] m_StringHashTable;
	}

	void HashGetter::Create(std::vector<std::vector<Data>>& data)
	{
		if (m_IntHashTable != nullptr || m_DoubleHashTable != nullptr || m_StringHashTable != nullptr) {
			delete[] m_IntHashTable;
			delete[] m_DoubleHashTable;
			delete[] m_StringHashTable;
		}

		m_Capacity = data.size() * data[0].size();
		m_IntHashTable = new LinkedList[m_Capacity];
		m_DoubleHashTable = new LinkedList[m_Capacity];
		m_StringHashTable = new LinkedList[m_Capacity];

		for (int i = 0; i < data.size(); ++i) {
			for (int j = 0; j < data[i].size(); ++j) {
				Insert(data[i][j]);
			}
		}
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
	
	void HashGetter::Update(const UpdateOperation& updateOperation, Data& value)
	{
		if (updateOperation == UpdateOperation::insert) {
			Insert(value);
		}
		else {
			Remove(value);
		}
	}
}