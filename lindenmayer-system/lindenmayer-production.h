#pragma once

#include <vector>

#include "context-inspector.h"
#include "lindenmayer-symbol.h"
#include "lindenmayer-symbol-builder.h"

class Production {
private:
	ContextInspector m_contextInspector;
	std::vector<LindenmayerSymbolBuilder> m_ResultBuilders;

public:
	Production(ContextInspector contextInspector, std::initializer_list<LindenmayerSymbolBuilder> )
		: m_contextInspector(contextInspector) { }


};