#include "lindenmayer-symbol.h"

LindenmayerSymbol::LindenmayerSymbol() { }

LindenmayerSymbol::LindenmayerSymbol(char symbol)
	:m_symbol(symbol) { }

LindenmayerSymbol::LindenmayerSymbol(char symbol, std::vector<float> parameters)
	: m_symbol(symbol), m_parameters(parameters) { }

char LindenmayerSymbol::GetSymbol() {
	return m_symbol;
}

char LindenmayerSymbol::GetSymbol() const {
	return m_symbol;
}

void LindenmayerSymbol::SetSymbol(char symbol) {
	m_symbol = symbol;
}

std::vector<float>& LindenmayerSymbol::GetParameters() {
	return m_parameters;
}

void LindenmayerSymbol::SetParameters(std::vector<float> parameters) {
	m_parameters = parameters;
}

std::string LindenmayerSymbol::ToString() {
	throw std::exception();
}