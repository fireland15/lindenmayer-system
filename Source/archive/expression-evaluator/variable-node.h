#pragma once

#include <string>

#include "expression-node.h"
#include "Exceptions.h"

class VariableNode : public ExpressionNode {
private:
	std::string m_symbol;
	float m_value;
	bool m_isSet;

public:
	VariableNode(std::string symbol);
	void SetValue(float value);
	virtual float operator()();
	virtual void Delete();
	virtual unsigned int NumChildren();
};
