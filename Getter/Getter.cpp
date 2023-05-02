#include "Getter.h"

namespace Getter {
	TreeGetter::Node::Node(const Data& value)
	{

	}

	TreeGetter::Node::~Node()
	{
		delete left;
		delete right;
	}

	int TreeGetter::Node::CalculateBalanceFactor() const
	{
		return 0;
	}

	void TreeGetter::Node::UpdateHeight()
	{

	}

	TreeGetter::Node* TreeGetter::RotateLeft(Node* node)
	{
		return nullptr;
	}

	TreeGetter::Node* TreeGetter::RotateRight(Node* node)
	{
		return nullptr;
	}

	TreeGetter::Node* TreeGetter::Insert(Node* node, const Data& value)
	{
		return nullptr;
	}

	TreeGetter::Node* TreeGetter::Remove(Node* node, const Data& value)
	{
		return nullptr;
	}

	TreeGetter::Node* TreeGetter::GetMinimumNode(Node* node)
	{
		return nullptr;
	}

	TreeGetter::TreeGetter(const std::vector<std::vector<Data>>& data)
	{
		for (int i = 0; i < data.size(); ++i) {
			for (int j = 0; j < data[i].size(); ++j) {
				Node* newNode = new Node(data[i][j]);
				Insert(newNode);
			}
		}
	}

	TreeGetter::~TreeGetter()
	{
		delete m_Root;
	}

	Data* TreeGetter::SearchByInt(const int& value) const
	{
		return nullptr;
	}

	Data* TreeGetter::SearchByDouble(const double& value) const
	{
		return nullptr;
	}

	Data* TreeGetter::SearchByString(const std::string& value) const
	{
		return nullptr;
	}
}