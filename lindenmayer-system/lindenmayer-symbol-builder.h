#pragma once

#include <vector>

#include "../expression-evaluator/expression.h"
#include "../lindenmayer-system/lindenmayer-symbol.h"

class LindenmayerSymbolBuilder {
private:
	char m_symbol;
	std::vector<Expression> m_parameterExpressions;

public:
	LindenmayerSymbolBuilder(char symbol) :m_symbol(symbol) { }

	LindenmayerSymbolBuilder(char symbol, std::initializer_list<Expression> parameterExpressions)
		: m_symbol(symbol), m_parameterExpressions(parameterExpressions) { }

	void PassParameter(const std::string& parameter, float value) {
		for (Expression expression : m_parameterExpressions) {
			expression.SetVariable(parameter, value);
		}
	}

	LindenmayerSymbol BuildSymbol() {
		size_t numParameters = m_parameterExpressions.size();

		LindenmayerSymbol symbol(m_symbol, std::vector<float>(numParameters));

		for (unsigned int i = 0; i < m_parameterExpressions.size(); i++) {
			m_parameterExpressions[i].Evaluate();
			symbol.GetParameters()[i] = m_parameterExpressions[i].GetResult();
		}

		return symbol;
	}
};