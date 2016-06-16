#pragma once

#include <vector>

#include "lindenmayer-symbol-builder.h"

class ProductionResultGenerator {
private:
	std::vector<LindenmayerSymbolBuilder> m_symbolBuilders;

public:
	ProductionResultGenerator(std::initializer_list<LindenmayerSymbolBuilder> symbolBuilders)
		: m_symbolBuilders(symbolBuilders) { }

	std::vector<LindenmayerSymbol> Generate(LindenmayerSymbol symbol) {
		std::vector<LindenmayerSymbol> symbols;

		for (LindenmayerSymbolBuilder builder : m_symbolBuilders) {
			char param = 'a';
			for (float value : symbol.GetParameters()) {
				builder.PassParameter(std::string(1, param++), value);
			}

			symbols.push_back(builder.BuildSymbol());
		}

		return symbols;
	}
};