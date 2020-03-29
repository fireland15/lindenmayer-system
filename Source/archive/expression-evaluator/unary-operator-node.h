#pragma once

#include <functional>

#include "operator-node.h"

class UnaryOperatorNode : public OperatorNode {
protected:
	std::function<float(float)> m_operation;
	ExpressionNode* m_child;

public:
	UnaryOperatorNode(std::function<float(float)> operation);
	virtual float operator()();
	virtual void Delete();
	virtual unsigned int NumChildren();
	virtual void SetChild(ExpressionNode* child, unsigned int i = 0);
};