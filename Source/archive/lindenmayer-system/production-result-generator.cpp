#include "production-result-generator.h"

ProductionResultGenerator::ProductionResultGenerator(std::initializer_list<LindenmayerSymbolBuilder> symbolBuilders)
	: m_symbolBuilders(symbolBuilders) { }
ProductionResultGenerator::ProductionResultGenerator(std::vector<LindenmayerSymbolBuilder> symbolBuilders)
	: m_symbolBuilders(symbolBuilders) { }

LindenmayerString ProductionResultGenerator::Generate(LindenmayerSymbol symbol) {
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