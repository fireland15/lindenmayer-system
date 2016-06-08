#pragma once

#include <stdexcept>
#include <memory>
#include <functional>
#include <map>
#include <list>

#include "Token.h"
#include "Exceptions.h"

// Expression Node

class ExpressionNode {
public:
	virtual float operator()() = 0;
	virtual void Delete() = 0;
	virtual unsigned int NumChildren() = 0;
};

// Operator Nodes

class OperatorNode : public ExpressionNode {
public:
	virtual float operator()() = 0;
	virtual void Delete() = 0;
	virtual void SetChild(ExpressionNode* child, unsigned int i = 0) = 0;
	virtual unsigned int NumChildren() = 0;
};

class UnaryOperatorNode : public OperatorNode {
protected:
	std::function<float(float)> m_operation;
	ExpressionNode* m_child;

public:
	UnaryOperatorNode(std::function<float(float)> operation)
		:m_operation(operation) {

	}

	virtual float operator()() {
		return m_operation((*m_child)());
	}

	virtual void Delete() {
		m_child->Delete();
		delete m_child;
	}

	virtual unsigned int NumChildren() { return 1; }


	virtual void SetChild(ExpressionNode* child, unsigned int i = 0) {
		m_child = child;
	}
};

class BinaryOperatorNode : public OperatorNode {
protected:
	std::function<float(float, float)> m_operation;
	ExpressionNode* m_child[2];

public:
	BinaryOperatorNode(std::function<float(float, float)> operation) 
		:m_operation(operation) {

	}

	virtual float operator()() {
		return m_operation((*m_child[0])(), (*m_child[1])());
	}

	virtual void Delete() {
		m_child[0]->Delete();
		m_child[1]->Delete();

		delete m_child[0];
		delete m_child[1];
	}

	virtual unsigned int NumChildren() { return 2; }

	virtual void SetChild(ExpressionNode* child, unsigned int i = 0) {
		if (i >= 2)
			throw std::runtime_error("cannot set child at index: " + i);

		m_child[i] = child;
	}
};

// Value Nodes

class ValueNode : public ExpressionNode {
private:
	float m_value;

public:
	ValueNode(float value)
		: m_value(value) {

	}

	virtual float operator()() {
		return m_value;
	}

	virtual void Delete() {
		return;
	}

	virtual unsigned int NumChildren() { return 0; }
};

class VariableNode : public ExpressionNode {
private:
	std::string m_symbol;
	float m_value;
	bool m_isSet;

public:
	VariableNode(std::string symbol) 
		:m_isSet(false), m_symbol(symbol) { }

	void SetValue(float value) {
		m_value = value;
		m_isSet = true;
	}

	virtual float operator()() {
		if (!m_isSet)
			throw ValueNotSetException(m_symbol);
		return m_value;
	}

	virtual void Delete() {
		return;
	}

	virtual unsigned int NumChildren() { return 0; }
};

// Node Builder

class ExpressionNodeBuilder {
private:
	/// <summary>
	/// Stores pointer to all variableNodes that have been constructed by this builder
	/// Does not own pointers. Cannot delete them.
	/// </summary>
	std::map<std::string, std::list<VariableNode*>> m_variableMap;

public:
	ExpressionNode* NewExpressionNode(const Token token) {
		if (token.Type() == TokenType::Operator) {
			switch (token.OperatorType()) {
			case OperatorType::neg:
				return new UnaryOperatorNode([](float x) { return -1 * x; });
			case OperatorType::add:
				return new BinaryOperatorNode([](float x, float y) { return x + y; });
			case OperatorType::sub:
				return new BinaryOperatorNode([](float x, float y) { return x - y; });
			case OperatorType::mul:
				return new BinaryOperatorNode([](float x, float y) { return x * y; });
			case OperatorType::div:
				return new BinaryOperatorNode([](float x, float y) { return x / y; });
			case OperatorType::eq:
				return new BinaryOperatorNode([](float x, float y) { return x == y ? 1.0f : 0.0f; });
			case OperatorType::neq:
				return new BinaryOperatorNode([](float x, float y) { return x != y ? 1.0f : 0.0f; });
			case OperatorType::lt:
				return new BinaryOperatorNode([](float x, float y) { return x < y ? 1.0f : 0.0f; });
			case OperatorType::leq:
				return new BinaryOperatorNode([](float x, float y) { return x <= y ? 1.0f : 0.0f; });
			case OperatorType::gt:
				return new BinaryOperatorNode([](float x, float y) { return x > y ? 1.0f : 0.0f; });
			case OperatorType::geq:
				return new BinaryOperatorNode([](float x, float y) { return x >= y ? 1.0f : 0.0f; });

			}
		}
		else if (token.Type() == TokenType::Value) {
			return new ValueNode(token.Value());
		}
		else if (token.Type() == TokenType::Identifier) {
			VariableNode* node = new VariableNode(token.Symbol());

			if (m_variableMap.count(token.Symbol()) == 0) {
				m_variableMap.insert(std::make_pair(token.Symbol(), std::list<VariableNode*>()));
			}
			m_variableMap.find(token.Symbol())->second.push_back(node);

			return node;
		}
		
		return nullptr;
	}

	std::map<std::string, std::list<VariableNode*>> GetVariableMap() {
		return m_variableMap;
	}
};