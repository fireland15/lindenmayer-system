#include "expression-builder.h"

ExpressionBuilder::ExpressionBuilder()
	: m_converter(BuildOperatorMap()), m_tokenizer(BuildOperatorSymbolMap()) { }

Expression ExpressionBuilder::Build(std::string expression) {
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

	return{ nodeStk.top(),  m_nodeBuilder.GetVariableMap() };
}

std::map<OperatorType, std::pair<Associativity, Precedence>> ExpressionBuilder::BuildOperatorMap() {
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

std::map<std::string, OperatorType> ExpressionBuilder::BuildOperatorSymbolMap() {
	std::map<std::string, OperatorType> opMap;
	opMap["~"] = OperatorType::neg;
	opMap["+"] = OperatorType::add;
	opMap["-"] = OperatorType::sub;
	opMap["*"] = OperatorType::mul;
	opMap["/"] = OperatorType::div;
	return opMap;
}