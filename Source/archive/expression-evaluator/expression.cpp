#include "expression.h"

Expression::Expression(ExpressionNode* expressionTree, std::map<std::string, std::list<VariableNode*>> variableMap)
	: m_expressionRoot(expressionTree), m_variableMap(variableMap) { }

float Expression::Evaluate() {
	m_result = (*m_expressionRoot)();
	return m_result;
}

void Expression::SetVariable(const std::string& symbol, float value) {
	if (m_variableMap.find(symbol) != m_variableMap.end()) {
		for (auto it = m_variableMap[symbol].begin(); it != m_variableMap[symbol].end(); ++it) {
			(*it)->SetValue(value);
		}
	}
}

float Expression::GetResult() {
	return m_result;
}