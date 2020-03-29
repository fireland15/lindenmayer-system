#pragma once

#include "expression-node.h"

class OperatorNode : public ExpressionNode {
public:
	virtual float operator()() = 0;
	virtual void Delete() = 0;
	virtual void SetChild(ExpressionNode* child, unsigned int i = 0) = 0;
	virtual unsigned int NumChildren() = 0;
};