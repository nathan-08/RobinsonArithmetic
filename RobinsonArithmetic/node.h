#pragma once
#include <iostream>
#include "types.h"

enum NodeType {
	NODE_NEG,
	NODE_IMPL,
	NODE_IFF,
	NODE_AND,
	NODE_OR,

	NODE_EQ,
	NODE_PLUS,
	NODE_MULT,
	NODE_S,
	NODE_ZERO
};
struct Node {
	const NodeType type;
	Node* left = nullptr;
	Node* right = nullptr;
	u8 value = 0;
	Node(NodeType, u8);
	Node(NodeType, Node*, Node*);
	~Node();
	friend std::ostream& operator<<(std::ostream&, Node&);
};

