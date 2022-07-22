#pragma once
#include <cstdint>
#include <vector>
#include <memory>
#include <iostream>
using u8 = uint8_t;
enum Type {
	NUM,
	PLUS,
	MULT,
	EQ,
	LPAREN,
	RPAREN
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


friend std::ostream& operator<<(std::ostream& os, Lexer& lexer) {
	for (std::unique_ptr<Token>& token : lexer.tokens) {
		switch (token->type) {
		case (RPAREN):
			os << "<RPAREN>";
			break;
		case (LPAREN):
			os << "<LPAREN>";
			break;
		case (PLUS):
			os << "<PLUS>";
			break;
		case (MULT):
			os << "<MULT>";
			break;
		case (EQ):
			os << "<EQ>";
			break;
		case (NUM):
		{
			Number* n = static_cast<Number*>(token.get());
			os << "<NUM_" << (int)n->value << ">";
			break;
		}
		default:
			os << "<UNKNOWN>";
		}
	}
	return os;
}
};
