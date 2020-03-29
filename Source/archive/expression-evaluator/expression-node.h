#pragma once

class ExpressionNode {
public:
	virtual float operator()() = 0;
	virtual void Delete() = 0;
	virtual unsigned int NumChildren() = 0;
};