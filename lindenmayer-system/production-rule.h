#pragma once

#include <vector>

#include "context-inspector.h"
#include "lindenmayer-symbol.h"
#include "lindenmayer-symbol-builder.h"
#include "production-result-generator.h"

class ProductionRule {
private:
	char m_symbol;
	ContextInspector m_contextInspector;
	ProductionResultGenerator m_resultGenerator;

public:
	ProductionRule(ContextInspector contextInspector, std::initializer_list<LindenmayerSymbolBuilder> symbolBuilders)
		: m_contextInspector(std::move(contextInspector)), m_resultGenerator(symbolBuilders) { }

	ProductionRule(char symbol, ContextInspector contextInspector, ProductionResultGenerator resultGenerator)
		: m_symbol(symbol), m_contextInspector(std::move(contextInspector)), m_resultGenerator(resultGenerator) { }

	bool CanReplace(LindenmayerString::Iterator it) {
		if (m_symbol == (*it).GetSymbol())
			return m_contextInspector.TestContext(it);

		return false;
	}

	LindenmayerString Produce(LindenmayerSymbol& symbol) {
		return m_resultGenerator.Generate(symbol);
	}
};