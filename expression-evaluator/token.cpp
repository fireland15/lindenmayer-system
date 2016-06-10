#include "token.h"

Token::Token(float value) 
	: m_type(TokenType::Value), m_value(value) { }

Token::Token(OperatorType opType) 
	: m_type(TokenType::Operator), m_opType(opType) { }

Token::Token(std::string symbol) 
	: m_type(TokenType::Identifier), m_symbol(symbol) { }

Token::Token(TokenType type) 
	: m_type(type) { }


TokenType Token::Type() const { 
	return m_type; 
}

OperatorType Token::Operator() const { 
	return m_opType; 
}

std::string Token::Symbol() const { 
	return m_symbol; 
}

float Token::Value() const { 
	return m_value; 
}
