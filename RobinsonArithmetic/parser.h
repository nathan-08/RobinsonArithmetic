#pragma once
#include "lexer.h"
#include "node.h"
#include <iostream>

class Parser {
	const Lexer& lexer;
public:
	Parser(const Lexer&);
	Node* parse();
	bool match(Type, size_t);
	Node* A(size_t, size_t);
	Node* B(size_t, size_t);
	Node* C(size_t, size_t);
	Node* D(size_t, size_t);
	Node* E(size_t, size_t);

	Node* P(size_t, size_t);
	Node* Q(size_t, size_t);
	Node* R(size_t, size_t);
	Node* F(size_t, size_t);
	static void traverse(Node*);
};

