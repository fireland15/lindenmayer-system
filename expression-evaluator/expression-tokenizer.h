#pragma once

#include <list>
#include <sstream>
#include <map>
#include <cctype>

#include "Token.h"
#include "Exceptions.h"

typedef std::list<Token> TokenList;
typedef std::map<std::string, OperatorType> OperatorMap;

class ExpressionTokenizer {
private:
	OperatorMap m_operatorMap;

public:
	ExpressionTokenizer(OperatorMap& operatorMap);
	const TokenList operator()(const std::string& expression) const;
};