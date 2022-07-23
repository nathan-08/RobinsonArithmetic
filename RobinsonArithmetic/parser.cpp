// Refer to the context-free grammar in notes.txt
#include "parser.h"
using namespace std;

Node::Node(NodeType type, u8 value)
	: type(type), left(nullptr), right(nullptr), value(value) {}

Node::Node(NodeType type, Node* left, Node* right)
	: type(type), left(left), right(right)
{ }

Node::~Node() {
	//cout << "deleting " << *this << endl;
}

Parser::Parser(const Lexer& lexer)
	: lexer(lexer)
{ }

Parser::~Parser() {
	if (tree) {
		delete_tree(tree);
	}
}

void Parser::delete_tree(Node* tree) {
	if (tree) {
		delete_tree(tree->left);
		delete_tree(tree->right);
		delete tree;
	}
}

void Parser::traverse(Node* tree) {
	// Postfix rendering of tree
	if (tree->left) traverse(tree->left);
	if (tree->right) traverse(tree->right);
	cout << *tree;
}

bool Parser::parse() {
	tree = P(0, lexer.num_tokens());
	if (tree) {
		cout << endl;
		traverse(tree);
		cout << endl;
	}
	return tree != nullptr;
}

bool Parser::match(Type type, size_t pos) {
	return lexer.get_type_at(pos) == type;
}

Node* Parser::P(size_t a, size_t b) {
	// Q=Q | Q
	for (int i = a; i < b; ++i) {
		if (lexer.get_type_at(i) == EQ) {
			Node* left = Q(a, i);
			Node* right = Q(i + 1, b);
			if (left && right) {
				return new Node(NODE_EQ, left, right);
			}
			else {
				if (left) delete left;
				if (right) delete right;
			}
		}
	}
	return Q(a, b);
}

Node* Parser::Q(size_t a, size_t b) {
	// Q+R | R
	for (int i = a; i < b; ++i) {
		if (lexer.get_type_at(i) == PLUS) {
			Node* left = Q(a, i);
			Node* right = R(i + 1, b);
			if (left && right) {
				return new Node(NODE_PLUS, left, right);
			}
			else {
				if (left) delete left;
				if (right) delete right;
			}
		}
	}
	return R(a, b);
}

Node* Parser::R(size_t a, size_t b) {
	// RxF | F
	for (int i = a; i < b; ++i) {
		if (lexer.get_type_at(i) == MULT) {
			Node* left = R(a, i);
			Node* right = F(i + 1, b);
			if (left && right) {
				return new Node(NODE_MULT, left, right);
			}
			else {
				if (left) delete left;
				if (right) delete right;
			}
		}
	}
	return F(a, b);
}

Node* Parser::F(size_t a, size_t b) {
	// num | (P)
	if (a + 1 == b) {
		if (match(NUM, a)) {
			return new Node(NODE_NUM, lexer.get_value_at(a));
		}
	}
	else {
		if (match(LPAREN, a) && match(RPAREN, b - 1)) {
			Node* q = Q(a+1, b - 1);
			if (q) return q;
		}
	}
	return nullptr;
}

ostream& operator<<(ostream& os, Node& node) {
	switch (node.type) {
	case NODE_EQ:
		os << "=";
		break;
	case NODE_PLUS:
		os << "+";
		break;
	case NODE_MULT:
		os << "x";
		break;
	case NODE_NUM:
		os << "(" << static_cast<int>(node.value) << ")";
		break;
	default:
		os << "<UNKNOWN>";
	}
	return os;
}
