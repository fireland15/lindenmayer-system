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
	ProductionRule(ContextInspector contextInspector, std::initializer_list<LindenmayerSymbolBuilder> symbolBuilders);
	ProductionRule(char symbol, ContextInspector contextInspector, ProductionResultGenerator resultGenerator);
	ProductionRule(const ProductionRule& other) = delete;
	ProductionRule(ProductionRule&& other);
	bool CanReplace(LindenmayerString::Iterator& it);
	LindenmayerString Produce(LindenmayerSymbol& symbol);
};