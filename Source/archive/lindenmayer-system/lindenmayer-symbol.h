#pragma once

#include <vector>

#include "../expression-evaluator/expression.h"

struct LindenmayerSymbol {
private:
	char m_symbol;
	std::vector<float> m_parameters;

public:
	LindenmayerSymbol();
	LindenmayerSymbol(char symbol);
	LindenmayerSymbol(char symbol, std::vector<float> parameters);
	char GetSymbol();
	void SetSymbol(char symbol);
	std::vector<float>& GetParameters();
	void SetParameters(std::vector<float> parameters);
	std::string ToString();
};