#pragma once
#include "lexer.h"

class Parser {
	size_t pos = 0;
	size_t begin = 0;
	size_t end;
	Type lookahead;
	const Lexer& lexer;
public:
	Parser(const Lexer&);
	bool parse();
	bool match(Type, size_t);
	bool P(size_t, size_t);
	bool Q(size_t, size_t);
	bool R(size_t, size_t);
	bool F(size_t, size_t);
};
