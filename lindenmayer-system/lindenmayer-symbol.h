#pragma once

#include <vector>

#include "../expression-evaluator/expression.h"

struct LindenmayerSymbol {
private:
	char m_symbol;
	std::vector<float> m_parameters;

public:
	LindenmayerSymbol() { }
	LindenmayerSymbol(char symbol) 
		:m_symbol(symbol) { }
	LindenmayerSymbol(char symbol, std::vector<float> parameters)
		: m_symbol(symbol), m_parameters(parameters) { }

	char GetSymbol() {
		return m_symbol;
	}

	void SetSymbol(char symbol) {
		m_symbol = symbol;
	}

	std::vector<float>& GetParameters() {
		return m_parameters;
	}

	void SetParameters(std::vector<float> parameters) {
		m_parameters = parameters;
	}

	std::string ToString() {
		throw std::exception();
	}
};