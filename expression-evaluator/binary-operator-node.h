#pragma once

#include <functional>

#include "operator-node.h"
#include "Exceptions.h"

class BinaryOperatorNode : public OperatorNode {
protected:
	std::function<float(float, float)> m_operation;
	ExpressionNode* m_child[2];

public:
	BinaryOperatorNode(std::function<float(float, float)> operation);
	virtual float operator()();
	virtual void Delete();
	virtual unsigned int NumChildren();
	virtual void SetChild(ExpressionNode* child, unsigned int i = 0);
};