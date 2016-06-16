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
	ContextInspector() {
		m_preContext = nullptr;
		m_postContext = nullptr;
	}

	ContextInspector(LindenmayerString* preContext, LindenmayerString* postContext)
		: m_preContext(preContext), m_postContext(postContext) { }

	~ContextInspector() {
		if (m_preContext != nullptr)
			delete m_preContext;

		if (m_postContext != nullptr)
			delete m_postContext;
	}

	bool TestContext(unsigned int pos, LindenmayerString& string) {
		bool lookBehindResult = TestPreContext(pos, string);
		bool lookAheadResult = TestPostContext(pos, string);
		return lookAheadResult && lookBehindResult;
	}

	bool TestPreContext(unsigned int pos, LindenmayerString& string) {
		if (m_preContext == nullptr)
			return true;

		return string.CompareBehind(pos - 1, *m_preContext);
	}

	bool TestPostContext(unsigned int pos, LindenmayerString& string) {
		if (m_postContext == nullptr)
			return true;

		return string.CompareAhead(pos + 1, *m_postContext);
	}
};
