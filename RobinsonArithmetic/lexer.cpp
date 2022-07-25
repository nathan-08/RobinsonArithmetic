#include <stdexcept>
#include "lexer.h"
using namespace std;

Token::Token(Type type) : type(type) {}

Number::Number(Type type, u8 value) : Token(type), value(value) {}

Lexer::Lexer(const vector<char>& input) {
	for (int i = 0; i < input.size(); ++i) {
		char c = input.at(i);
		switch (c) {
		case '!':
			tokens.emplace_back(new Token(NEG));
			break;
		case '&':
			tokens.emplace_back(new Token(AND));
			break;
		case '|':
			tokens.emplace_back(new Token(OR));
			break;

		case '=': // =>
			if (i + 1 < input.size()) {
				if (input.at(i + 1) == '>') {
					tokens.emplace_back(new Token(IMPL));
					++i;
					break;
				}
			}
			tokens.emplace_back(new Token(EQ));
			break;
		case '<': // <=>
			if (i + 2 < input.size()) {
				if (input.at(i + 1) == '=' && input.at(i + 2) == '>') {
					tokens.emplace_back(new Token(IFF));
					i += 2;
					break;
				}
			}
		case '(':
			tokens.emplace_back(new Token(LPAREN));
			break;
		case ')':
			tokens.emplace_back(new Token(RPAREN));
			break;
		case '0':
			tokens.emplace_back(new Token(ZERO));
			break;
		case 's':
			tokens.emplace_back(new Token(S));
			break;
		break;
		case '+':
			tokens.emplace_back(new Token(PLUS));
			break;
		case 'x':
			tokens.emplace_back(new Token(MULT));
			break;
		default:
			tokens.emplace_back(new Token(UNKNOWN));
		}
	}
}

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

ostream& operator<<(ostream& os, Lexer& lexer) {
	for (std::unique_ptr<Token>& token : lexer.tokens) {
		switch (token->type) {
		case (NEG):
			os << "<NEG>";
			break;
		case (IMPL):
			os << "<IMPL>";
			break;
		case (IFF):
			os << "<IFF>";
			break;
		case (AND):
			os << "<AND>";
			break;
		case (OR):
			os << "<OR>";
			break;

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
		case (S):
			os << "<S>";
			break;
		case (ZERO):
			os << "<ZERO>";
			break;
		case (UNKNOWN):
			os << "<UNKNOWN>";
			break;
		default:
			throw logic_error("unidentified token");
		}
	}
	return os;
}

