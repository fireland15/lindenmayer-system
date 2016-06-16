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

	bool TestContext(vSymbols_t::iterator begin, vSymbols_t::iterator it, vSymbols_t::iterator end) {
		bool lookBehindResult = TestPreContext(begin, it);
		bool lookAheadResult = TestPostContext(it, end);
		return lookAheadResult && lookBehindResult;
	}

	bool TestPreContext(vSymbols_t::iterator begin, vSymbols_t::iterator it) {
		//if (m_preContext == nullptr)
		//	return true;

		//auto rBegin = std::reverse_iterator<vSymbols_t::iterator>(begin);
		//auto rIt = std::reverse_iterator<vSymbols_t::iterator>(it);

		//auto contextIterator = m_preContext->rBegin();

		//while (rIt != rBegin && contextIterator != m_preContext->rEnd()) {
		//	if (rIt->symbol != contextIterator->symbol)
		//		return false;
		//	++rIt;
		//}

		return true;
	}

	bool TestPostContext(vSymbols_t::iterator it, vSymbols_t::iterator end) {
		//if (m_postContext == nullptr)
		//	return true;

		//it = std::next(it);

		//auto contextIterator = m_postContext->Begin();

		//while (it != end && contextIterator != m_postContext->End()) {
		//	if (it->symbol != contextIterator->symbol)
		//		return false;
		//	++it;
		//}

		return true;
	}
};
