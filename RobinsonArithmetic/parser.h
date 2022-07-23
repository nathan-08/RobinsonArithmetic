#pragma once
#include "lexer.h"
#include <iostream>

enum NodeType {
	NODE_EQ,
	NODE_PLUS,
	NODE_MULT,
	NODE_NUM
};
struct Node {
	const NodeType type;
	Node* left;
	Node* right;
	u8 value = 0;
	Node(NodeType, u8);
	Node(NodeType, Node*, Node*);
	~Node();
	friend std::ostream& operator<<(std::ostream&, Node&);
};

class Parser {
	const Lexer& lexer;
	Node* tree = nullptr;
	static void delete_tree(Node*);
public:
	Parser(const Lexer&);
	~Parser();
	bool parse();
	bool match(Type, size_t);
	Node* P(size_t, size_t);
	Node* Q(size_t, size_t);
	Node* R(size_t, size_t);
	Node* F(size_t, size_t);
	static void traverse(Node*);
};

