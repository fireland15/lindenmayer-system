#pragma once

#include <map>
#include <list>
#include <string>

#include "expression-node.h"
#include "variable-node.h"
#include "value-node.h"
#include "unary-operator-node.h"
#include "binary-operator-node.h"
#include "token.h"

class ExpressionNodeBuilder {
private:
	/// <summary>
	/// Stores pointer to all variableNodes that have been constructed by this builder
	/// Does not own pointers. Cannot delete them.
	/// </summary>
	std::map<std::string, std::list<VariableNode*>> m_variableMap;

public:
	ExpressionNode* NewExpressionNode(const Token token);
	std::map<std::string, std::list<VariableNode*>> GetVariableMap();
};