#pragma once

#include <vector>

#include "lindenmayer-string.h"
#include "lindenmayer-symbol-builder.h"

class ProductionResultGenerator {
private:
	std::vector<LindenmayerSymbolBuilder> m_symbolBuilders;

public:
	ProductionResultGenerator(std::initializer_list<LindenmayerSymbolBuilder> symbolBuilders);
	ProductionResultGenerator(std::vector<LindenmayerSymbolBuilder> symbolBuilders);
	LindenmayerString Generate(LindenmayerSymbol symbol);
};