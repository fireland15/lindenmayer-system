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

	bool TestContext(LindenmayerString::Iterator& it) {
		bool lookBehindResult = TestPreContext(--it);
		bool lookAheadResult = TestPostContext(++(++it));
		return lookAheadResult && lookBehindResult;
	}

	bool TestPreContext(LindenmayerString::Iterator& it) {
		if (m_preContext == nullptr)
			return true;

		LindenmayerString::Iterator cIt = m_preContext->Last();

		while (!it.AtStart() && !cIt.AtStart()) {
			if (it != cIt)
				return false;

			--it; --cIt;
		}
		return true;
	}

	bool TestPostContext(LindenmayerString::Iterator& it) {
		if (m_postContext == nullptr)
			return true;

		LindenmayerString::Iterator cIt = m_postContext->Begin();

		while (!it.AtEnd() && !cIt.AtEnd()) {
			if (it != cIt)
				return false;

			++it; ++cIt;
		}
		return true;
	}
};
