// Refer to the context-free grammar in notes.txt
#include "parser.h"
using namespace std;

Parser::Parser(const Lexer& lexer)
	: lexer(lexer)
{ }

bool Parser::parse() {
	return P(0, lexer.num_tokens());
}

bool Parser::match(Type type, size_t pos) {
	return lexer.get_type_at(pos) == type;
}

bool Parser::P(size_t a, size_t b) {
	// Q=Q | Q
	for (int i = a; i < b; ++i) {
		if (lexer.get_type_at(i) == EQ) {
			return (
				Q(a, i) && Q(i + 1, b)
				);
		}
	}
	return Q(a, b);
}

bool Parser::Q(size_t a, size_t b) {
	// Q+R | R
	for (int i = a; i < b; ++i) {
		if (lexer.get_type_at(i) == PLUS) {
			return (
				Q(a, i) && R(i+1, b)
				);
		}
	}
	return R(a, b);
}

bool Parser::R(size_t a, size_t b) {
	// RxF | F
	for (int i = a; i < b; ++i) {
		if (lexer.get_type_at(i) == MULT) {
			return (
				R(a, i) && F(i+1, b)
				);
		}
	}
	return F(a, b);
}

bool Parser::F(size_t a, size_t b) {
	// num | (P)
	if (a + 1 == b)
		return match(NUM, a);
	return (
		match(LPAREN, a) &&
		P(a+1,b-1) &&
		match(RPAREN, b-1)
	);
}
