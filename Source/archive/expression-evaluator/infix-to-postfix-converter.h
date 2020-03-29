#pragma once

#include <list>
#include <stack>
#include <map>

#include "Token.h"
#include "Exceptions.h"

typedef std::list<Token> TokenList;

class InfixToPostfixConverter {
private:
	std::map<OperatorType, std::pair<Associativity, Precedence>> m_operatorMap;

public:
	InfixToPostfixConverter(std::map<OperatorType, std::pair<Associativity, Precedence>>& operatorMap);
	TokenList operator()(const TokenList& in) const;

private:
	bool TestPrecedence(const Token& t1, const Token& t2) const;
};