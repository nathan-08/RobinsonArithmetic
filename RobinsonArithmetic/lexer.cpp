#include <stdexcept>
#include "lexer.h"
using namespace std;

Token::Token(Type type) : type(type) {}

Number::Number(Type type, u8 value) : Token(type), value(value) {}

Lexer::Lexer(const vector<char>& input) {
	for (int i = 0; i < input.size(); ++i) {
		char c = input.at(i);
		switch (c) {
		case '(':
			tokens.emplace_back(new Token(LPAREN));
			break;
		case ')':
			tokens.emplace_back(new Token(RPAREN));
			break;
		case '=':
			tokens.emplace_back(new Token(EQ));
			break;
		case '0':
			tokens.emplace_back(new Number(NUM, 0));
			break;
		case 's':
		{
			u8 n = 1;
			char next;
			while (true) {
				i++;
				if (i >= input.size())
					throw logic_error("Lexer error");
				next = input.at(i);
				if (next == 's') {
					++n;
					continue;
				}
				else if (next == '0') {
					tokens.emplace_back(new Number(NUM, n));
					break;
				}
				else {
					throw logic_error("Lexer error");
				}

			}
		}
		break;
		case '+':
			tokens.emplace_back(new Token(PLUS));
			break;
		case 'x':
			tokens.emplace_back(new Token(MULT));
			break;
		}
	}
};

Type Lexer::get_type_at(size_t i) const {
	return tokens.at(i)->type;
}
u8 Lexer::get_value_at(size_t i) const {
	Number* number = static_cast<Number*>(tokens.at(i).get());
	if (number) {
		return number->value;
	}
	throw logic_error("Not a number");
}

const Token& Lexer::get_token_at(size_t i) const {
	return *tokens.at(i);
}
