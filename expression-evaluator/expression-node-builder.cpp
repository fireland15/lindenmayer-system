#include "expression-node-builder.h"

ExpressionNode* ExpressionNodeBuilder::NewExpressionNode(const Token token) {
	if (token.Type() == TokenType::Operator) {
		switch (token.Operator()) {
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


std::map<std::string, std::list<VariableNode*>> ExpressionNodeBuilder::GetVariableMap() {
	return m_variableMap;
}