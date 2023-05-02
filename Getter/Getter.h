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

			Node(const Data& value);
			~Node();

			int CalculateBalanceFactor() const;
			void UpdateHeight();
		};

		std::vector<std::vector<Data>>* m_Data;
		Node* m_Root;
		size_t m_Size;
		Data m_DefaultValue;

		Node* RotateLeft(Node* node);
		Node* RotateRight(Node* node);
		Node* Insert(Node* node, const Data& value);
		Node* Remove(Node* node, const Data& value);
		Node* GetMinimumNode(Node* node);
	public:
		TreeGetter(const std::vector<std::vector<Data>>& data);
		~TreeGetter();

		Data* SearchByInt(const int& value) const;
		Data* SearchByDouble(const double& value) const;
		Data* SearchByString(const std::string& value) const;
	};
}
#endif