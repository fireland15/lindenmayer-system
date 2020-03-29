#pragma once

#include <map>
#include <stack>

#include "expression.h"
#include "expression-node-builder.h"

class ExpressionBuilder {
private:
	InfixToPostfixConverter m_converter;
	ExpressionNodeBuilder m_nodeBuilder;
	ExpressionTokenizer m_tokenizer;

public:
	ExpressionBuilder();
	Expression Build(std::string expression);

private:
	std::map<OperatorType, std::pair<Associativity, Precedence>> BuildOperatorMap();
	std::map<std::string, OperatorType> BuildOperatorSymbolMap();
};