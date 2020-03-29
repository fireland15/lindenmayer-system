#pragma once

#include <string>

#include "token-type.h"
#include "operator-type.h"

class Token {
private:
	TokenType m_type;
	OperatorType m_opType;
	std::string m_symbol;
	float m_value;

public:
	Token(float value);
	Token(OperatorType opType);
	Token(std::string symbol);
	Token(TokenType type);

	TokenType Type() const;
	OperatorType Operator() const;
	std::string Symbol() const;
	float Value() const;
};