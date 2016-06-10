#include "ExpressionTokenizer.h"

ExpressionTokenizer::ExpressionTokenizer(OperatorMap& operatorMap)
	: m_operatorMap(operatorMap) { }

const TokenList ExpressionTokenizer::operator()(const std::string& expression) const {
	TokenList tokens;
	std::stringstream stream(expression);

	char ch;
	while (stream.get(ch)) {
		if (std::isdigit(ch) || ch == '.') {
			std::stringstream number;
			number << (char)ch;

			ch = stream.peek();
			while (std::isdigit(ch) || ch == '.') {
				number << (char)(stream.get());
				ch = stream.peek();
			}

			float test;
			if (number >> test) {
				tokens.push_back(Token(test));
			}
			else {
				throw ParseException(stream.str() + " is not a number");
			}
		}

		else if (std::isalpha(ch)) {
			std::stringstream symbol;
			symbol << (char)ch;

			while (std::isalnum(stream.peek())) {
				symbol << (char)(stream.get());
			}

			tokens.push_back(Token(symbol.str()));
		}
		else if (ch == '=') {
			ch = stream.peek();
			if (ch == '=') {
				tokens.push_back(Token(OperatorType::eq));
				stream.get();
			}
			else {
				throw ParseException("Invalid symbol");
			}
		}
		else if (ch == '<') {
			ch = stream.peek();
			if (ch == '=') {
				tokens.push_back(Token(OperatorType::leq));
				stream.get();
			}
			else {
				tokens.push_back(Token(OperatorType::lt));
			}
		}
		else if (ch == '>') {
			ch = stream.peek();
			if (ch == '=') {
				tokens.push_back(Token(OperatorType::geq));
				stream.get();
			}
			else {
				tokens.push_back(Token(OperatorType::gt));
			}
		}
		else if (ch == '!') {
			ch = stream.peek();
			if (ch == '=') {
				tokens.push_back(Token(OperatorType::neq));
				stream.get();
			}
			else {
				throw ParseException("Invalid symbol");
			}
		}
		else if (m_operatorMap.find(std::string(1, ch)) != m_operatorMap.end()) {
			OperatorType opType = m_operatorMap.find(std::string(1, ch))->second;
			tokens.push_back(Token(opType));
		}
		else if (ch == '(') {
			tokens.push_back(Token(TokenType::LParen));
		}
		else if (ch == ')') {
			tokens.push_back(Token(TokenType::RParen));
		}
		else if (std::isblank(ch)) {
			continue;
		}
		else {
			throw ParseException("Symbol undefined");
		}
	}

	return tokens;
}