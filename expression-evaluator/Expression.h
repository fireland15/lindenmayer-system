#pragma once
#include <memory>
#include <string>
#include <vector>
#include <sstream>
#include <cctype>
#include <iostream>

#include "ExpressionNodes.h"
#include "Exceptions.h"
#include "InfixToPostfixConverter.h"
#include "ExpressionTokenizer.h"

class Expression {
private:
	ExpressionNode* m_expressionRoot;
	std::map<std::string, std::list<VariableNode*>> m_variableMap;
	float m_result;

public:
	Expression(ExpressionNode* expressionTree, std::map<std::string, std::list<VariableNode*>> variableMap)
		: m_expressionRoot(expressionTree),  m_variableMap(variableMap) {
		
	}

	float Evaluate() {
		m_result = (*m_expressionRoot)();
		return m_result;
	}

	void SetVariable(const std::string& symbol, float value) {
		if (m_variableMap.find(symbol) != m_variableMap.end()) {
			for (auto it = m_variableMap[symbol].begin(); it != m_variableMap[symbol].end(); ++it) {
				(*it)->SetValue(value);
			}
		}
	}

	float GetResult() {
		return m_result;
	}
};

class ExpressionBuilder {
private:
	InfixToPostfixConverter m_converter;
	ExpressionNodeBuilder m_nodeBuilder;
	ExpressionTokenizer m_tokenizer;

public:
	ExpressionBuilder() 
		: m_converter(BuildOperatorMap()), m_tokenizer(BuildOperatorSymbolMap()) { }

	Expression Build(std::string expression) {
		TokenList tokens = m_tokenizer(expression);

		TokenList postfix = m_converter(tokens);

		std::stack<ExpressionNode*> nodeStk;

		auto it = postfix.begin();

		nodeStk.push(m_nodeBuilder.NewExpressionNode(*it));

		while (++it != postfix.end()) {
			ExpressionNode* node = m_nodeBuilder.NewExpressionNode(*it);

			switch (node->NumChildren()) {
			case 0:
				nodeStk.push(node);
				break;
			case 1:
				static_cast<OperatorNode*>(node)->SetChild(nodeStk.top());
				nodeStk.pop();
				nodeStk.push(node);
				break;
			case 2:
				static_cast<OperatorNode*>(node)->SetChild(nodeStk.top(), 1);
				nodeStk.pop();
				static_cast<OperatorNode*>(node)->SetChild(nodeStk.top(), 0);
				nodeStk.pop();
				nodeStk.push(node);
				break;
			}
		}
		
		return { nodeStk.top(),  m_nodeBuilder.GetVariableMap()};
	}

private:
	std::map<OperatorType, std::pair<Associativity, Precedence>> BuildOperatorMap() {
		std::map<OperatorType, std::pair<Associativity, Precedence>> opMap;
		opMap[OperatorType::add] = std::make_pair(Associativity::left, Precedence::low);
		opMap[OperatorType::sub] = std::make_pair(Associativity::left, Precedence::low);
		opMap[OperatorType::neg] = std::make_pair(Associativity::right, Precedence::high);
		opMap[OperatorType::mul] = std::make_pair(Associativity::left, Precedence::mid);
		opMap[OperatorType::div] = std::make_pair(Associativity::left, Precedence::mid);
		opMap[OperatorType::eq] = std::make_pair(Associativity::left, Precedence::lowest);
		opMap[OperatorType::gt] = std::make_pair(Associativity::left, Precedence::lowest);
		opMap[OperatorType::geq] = std::make_pair(Associativity::left, Precedence::lowest);
		opMap[OperatorType::lt] = std::make_pair(Associativity::left, Precedence::lowest);
		opMap[OperatorType::leq] = std::make_pair(Associativity::left, Precedence::lowest);
		return opMap;
	}

	std::map<std::string, OperatorType> BuildOperatorSymbolMap() {
		std::map<std::string, OperatorType> opMap;
		opMap["~"] = OperatorType::neg;
		opMap["+"] = OperatorType::add;
		opMap["-"] = OperatorType::sub;
		opMap["*"] = OperatorType::mul;
		opMap["/"] = OperatorType::div;
		return opMap;
	}
};