#pragma once

#include <vector>

#include "lindenmayer-string.h"
#include "lindenmayer-symbol-builder.h"

class ProductionResultGenerator {
private:
	std::vector<LindenmayerSymbolBuilder> m_symbolBuilders;

public:
	ProductionResultGenerator(std::initializer_list<LindenmayerSymbolBuilder> symbolBuilders)
		: m_symbolBuilders(symbolBuilders) { }
	ProductionResultGenerator(std::vector<LindenmayerSymbolBuilder> symbolBuilders)
		: m_symbolBuilders(symbolBuilders) { }

	LindenmayerString Generate(LindenmayerSymbol symbol) {
		LindenmayerString symbols;

		for (LindenmayerSymbolBuilder builder : m_symbolBuilders) {
			char param = 'a';
			for (float value : symbol.GetParameters()) {
				builder.PassParameter(std::string(1, param++), value);
			}

			symbols.Add(builder.BuildSymbol());
		}

		return symbols;
	}
};