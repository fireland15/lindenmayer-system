#include "lindenmayer-symbol-builder.h"

LindenmayerSymbolBuilder::LindenmayerSymbolBuilder(char symbol) :m_symbol(symbol) { }

LindenmayerSymbolBuilder::LindenmayerSymbolBuilder(char symbol, std::initializer_list<Expression> parameterExpressions)
	: m_symbol(symbol), m_parameterExpressions(parameterExpressions) { }

LindenmayerSymbolBuilder::LindenmayerSymbolBuilder(char symbol, std::vector<Expression> parameterExpressions)
	:m_symbol(symbol), m_parameterExpressions(parameterExpressions) { }

void LindenmayerSymbolBuilder::PassParameter(const std::string& parameter, float value) {
	for (Expression expression : m_parameterExpressions) {
		expression.SetVariable(parameter, value);
	}
}

LindenmayerSymbol LindenmayerSymbolBuilder::BuildSymbol() {
	size_t numParameters = m_parameterExpressions.size();

	LindenmayerSymbol symbol(m_symbol, std::vector<float>(numParameters));

	for (unsigned int i = 0; i < m_parameterExpressions.size(); i++) {
		m_parameterExpressions[i].Evaluate();
		symbol.GetParameters()[i] = m_parameterExpressions[i].GetResult();
	}

	return symbol;
}