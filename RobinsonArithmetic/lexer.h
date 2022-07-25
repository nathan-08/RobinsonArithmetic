#pragma once
#include <cstdint>
#include <vector>
#include <memory>
#include <iostream>
#include "types.h"
enum Type {
	NEG,
	IMPL,
	IFF,
	AND,
	OR,

	ZERO,
	S,
	PLUS,
	MULT,
	EQ,
	LPAREN,
	RPAREN,

	UNKNOWN
};
struct Token {
	const Type type;
	Token(Type);
};

struct Number : public Token {
	const u8 value;
	Number(Type, u8);
};

class Lexer {
	std::vector<std::unique_ptr<Token>> tokens;
public:
	Lexer(const std::vector<char>&);
	size_t inline num_tokens() const { return tokens.size(); };
	Type get_type_at(size_t) const;
	u8 get_value_at(size_t) const;
	const Token& get_token_at(size_t) const;

	friend std::ostream& operator<<(std::ostream&, Lexer&);
};

