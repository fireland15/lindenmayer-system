#pragma once

#include <memory>
#include <string>
#include <vector>
#include <sstream>
#include <cctype>
#include <iostream>

#include "expression-node.h"
#include "variable-node.h"
#include "Exceptions.h"
#include "InfixToPostfixConverter.h"
#include "ExpressionTokenizer.h"

class Expression {
private:
	ExpressionNode* m_expressionRoot;
	std::map<std::string, std::list<VariableNode*>> m_variableMap;
	float m_result;

public:
	Expression(ExpressionNode* expressionTree, std::map<std::string, std::list<VariableNode*>> variableMap);

	float Evaluate();

	void SetVariable(const std::string& symbol, float value);

	float GetResult();
};
