#include "production-rule.h"

ProductionRule::ProductionRule(ContextInspector contextInspector, std::initializer_list<LindenmayerSymbolBuilder> symbolBuilders)
	: m_contextInspector(std::move(contextInspector)), m_resultGenerator(symbolBuilders) { }

ProductionRule::ProductionRule(char symbol, ContextInspector contextInspector, ProductionResultGenerator resultGenerator)
	: m_symbol(symbol), m_contextInspector(std::move(contextInspector)), m_resultGenerator(resultGenerator) { }

ProductionRule::ProductionRule(ProductionRule&& other)
	: m_contextInspector(std::move(other.m_contextInspector)), m_resultGenerator(other.m_resultGenerator), m_symbol(other.m_symbol) {

}

bool ProductionRule::CanReplace(LindenmayerString::Iterator& it) {
	if (m_symbol == (*it).GetSymbol())
		return m_contextInspector.TestContext(it);

	return false;
}

LindenmayerString ProductionRule::Produce(LindenmayerSymbol& symbol) {
	return m_resultGenerator.Generate(symbol);
}