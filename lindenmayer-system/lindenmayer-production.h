#pragma once

#include <vector>

#include "context-inspector.h"
#include "lindenmayer-symbol.h"
#include "lindenmayer-symbol-builder.h"

class Production {
private:
	ContextInspector m_contextInspector;
	std::vector<LindenmayerSymbolBuilder> m_resultBuilders;

public:
	Production(ContextInspector contextInspector, std::initializer_list<LindenmayerSymbolBuilder> )
		: m_contextInspector(contextInspector) { }

	bool CanReplace(unsigned int index, LindenmayerString& string) {
		return m_contextInspector.TestContext(index, string);
	}

	LindenmayerString Produce(LindenmayerSymbol& symbol) {
		LindenmayerString str;
		for (auto builder : m_resultBuilders) {
			for (float parameter : symbol.GetParameters()) {
				builder.PassParameter("", parameter);
			}
			str.Add(builder.BuildSymbol());
		}
	}
};