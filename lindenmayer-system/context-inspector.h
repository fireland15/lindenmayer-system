#pragma once

#include "lindenmayer-symbol.h"
#include "lindenmayer-string.h"

#include <stdexcept>
#include <list>

typedef std::vector<LindenmayerSymbol> vSymbols_t;

class ContextInspector {
	LindenmayerString* m_preContext;
	LindenmayerString* m_postContext;

public:
	ContextInspector();
	ContextInspector(LindenmayerString* preContext, LindenmayerString* postContext);
	ContextInspector(ContextInspector&& other);
	ContextInspector(const ContextInspector& that) = delete;
	ContextInspector& operator=(const ContextInspector&) = delete;	
	~ContextInspector();
	bool TestContext(LindenmayerString::Iterator& it);
	bool TestPreContext(LindenmayerString::Iterator& it);
	bool TestPostContext(LindenmayerString::Iterator& it);
};
