#pragma once

#include <string>

enum class Associativity { left, right };
enum class Precedence { lowest, low, mid, high, highest };

enum class OperatorType : unsigned int {
	neg,
	add,
	sub,
	mul,
	div,
	eq, // equal
	neq, // not equal
	gt, // greater than
	lt, // less than
	geq, // greater than or equal
	leq // less than or equal
};

enum class TokenType : unsigned int {
	Value,
	Identifier,
	Operator,
	LParen,
	RParen
};

class Token {
private:
	TokenType m_type;
	OperatorType m_opType;
	std::string m_symbol;
	float m_value;

public:
	Token(float value) : m_type(TokenType::Value), m_value(value) { } // value
	Token(OperatorType opType) : m_type(TokenType::Operator), m_opType(opType) { } // operator
	Token(std::string symbol) : m_type(TokenType::Identifier), m_symbol(symbol) { } // variable
	Token(TokenType type) : m_type(type) { }

	TokenType Type() const { return m_type; }
	OperatorType OperatorType() const { return m_opType; }
	std::string Symbol() const { return m_symbol; }
	float Value() const { return m_value; }
};