#pragma once

#include <vector>

#include "../expression-evaluator/expression.h"
#include "../lindenmayer-system/lindenmayer-symbol.h"

class LindenmayerSymbolBuilder {
private:
	char m_symbol;
	std::vector<Expression> m_parameterExpressions;

public:
	LindenmayerSymbolBuilder(char symbol);
	LindenmayerSymbolBuilder(char symbol, std::initializer_list<Expression> parameterExpressions);
	LindenmayerSymbolBuilder(char symbol, std::vector<Expression> parameterExpressions);
	void PassParameter(const std::string& parameter, float value);
	LindenmayerSymbol BuildSymbol();
};