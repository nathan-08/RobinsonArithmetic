// Refer to the context-free grammar in notes.txt
#include "parser.h"
using namespace std;


Parser::Parser(const Lexer& lexer)
	: lexer(lexer)
{ }

void Parser::traverse(Node* tree) {
	if (tree->type != NODE_ZERO && tree->type != NODE_S)
		cout << "(";
	if (tree->left) traverse(tree->left);
	cout <<  *tree;
	if (tree->right) traverse(tree->right);
	if (tree->type != NODE_ZERO && tree->type != NODE_S)
		cout << ")";
}

Node* Parser::parse() {
	Node* tree = A(0, lexer.num_tokens());
	if (!tree) {
		tree = P(0, lexer.num_tokens());
	}
	if (tree) {
		traverse(tree);
	}
	return tree;
}

bool Parser::match(Type type, size_t pos) {
	return lexer.get_type_at(pos) == type;
}

Node* Parser::A(size_t a, size_t b) {
	// A => A<=>B | B
	for (int i = a; i < b; ++i) {
		if (lexer.get_type_at(i) == IFF) {
			Node* left = A(a, i);
			Node* right = B(i+1, b);
			if (left && right) {
				return new Node(NODE_IFF, left, right);
			}
			else {
				if (left) delete left;
				if (right) delete right;
			}
		}
	}
	return B(a, b);
}

Node* Parser::B(size_t a, size_t b) {
	// B => B=>C | C
	for (int i = a; i < b; ++i) {
		if (lexer.get_type_at(i) == IMPL) {
			Node* left = B(a, i);
			Node* right = C(i+1, b);
			if (left && right) {
				return new Node(NODE_IMPL, left, right);
			}
			else {
				if (left) delete left;
				if (right) delete right;
			}
		}
	}
	return C(a, b);
}

Node* Parser::C(size_t a, size_t b) {
	// C => C & D | D
	for (int i = a; i < b; ++i) {
		if (lexer.get_type_at(i) == AND) {
			Node* left = C(a, i);
			Node* right = D(i+1, b);
			if (left && right) {
				return new Node(NODE_AND, left, right);
			}
			else {
				if (left) delete left;
				if (right) delete right;
			}
		}
	}
	return D(a, b);
}

Node* Parser::D(size_t a, size_t b) {
	// D => D <or> E | E
	for (int i = a; i < b; ++i) {
		if (lexer.get_type_at(i) == OR) {
			Node* left = D(a, i);
			Node* right = E(i+1, b);
			if (left && right) {
				return new Node(NODE_OR, left, right);
			}
			else {
				if (left) delete left;
				if (right) delete right;
			}
		}
	}
	return E(a, b);
}

Node* Parser::E(size_t a, size_t b) {
	// E => !E | (A) | Q=Q
	if (lexer.get_type_at(a) == NEG) {
		Node* negated_proposition = E(a + 1, b);
		if (negated_proposition) {
			return new Node(NODE_NEG, nullptr, negated_proposition);
		}
	}
	// (A)
	if (match(LPAREN, a) && match(RPAREN, b - 1)) {
		Node* p = A(a + 1, b - 1);
		if (p) return p;
	}
	// Q=Q
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
	return nullptr;
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
	// sF | 0 | (Q)
	if (a + 1 == b && match(ZERO, a)) {
		return new Node(NODE_ZERO, nullptr, nullptr);
	}
	if (match(S, a)) {
		Node* f = F(a + 1, b);
		if (f) {
			return new Node(NODE_S, nullptr, f);
		}
	}
	if (match(LPAREN, a) && match(RPAREN, b - 1)) {
		Node* q = Q(a+1, b - 1);
		if (q) return q;
	}
	return nullptr;
}

