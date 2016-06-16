#pragma once

#include "production-result-generator.h"
#include "context-inspector.h"

class Production {
private:
	ProductionResultGenerator m_resultGenerator;
	ContextInspector m_contextInspector;
	char m_matchingSymbol;

public:
	Production(ContextInspector contextInspector, ProductionResultGenerator resultGenerator)
		: m_contextInspector(contextInspector), m_resultGenerator(resultGenerator) { }

	bool 
};