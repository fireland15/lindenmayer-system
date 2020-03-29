#pragma once

#include "expression-node.h"

class ValueNode : public ExpressionNode {
private:
	float m_value;

public:
	ValueNode(float value);
	virtual float operator()();
	virtual void Delete();
	virtual unsigned int NumChildren();
};