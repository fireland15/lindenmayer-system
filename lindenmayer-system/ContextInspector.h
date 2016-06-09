#pragma once

#include "LindenmayerSymbol.h"

#include <stdexcept>
#include <list>

template<typename Iterator>
class ContextInspector {
	std::list<LindenmayerSymbol> m_preContext;
	std::list<LindenmayerSymbol> m_postContext;
public:
	ContextInspector(std::list<LindenmayerSymbol> preContext, std::list<LindenmayerSymbol> postContext)
		: m_preContext(preContext), m_postContext(postContext) {

	}

	bool TestContext(Iterator it) {
		// Todo: Implement context tests
		throw std::exception("Not Implemented");

		bool lookBehindResult = TestPreContext(std::prev(it));
		bool lookAheadResult = TestPostContext(std::next(it));
	}

private:
	bool TestPreContext(Iterator it) {
		auto contextIterator = m_preContext.rbegin();

		for (contextIterator; contextIterator != m_preContext.rend(); ++contextIterator) {
			if (contextIterator->symbol != it->symbol) {
				return false;
			}
			--it;
		}

		return true;
	}

	bool TestPostContext(Iterator it) {
		auto contextIterator = m_postContext.begin();

		for (contextIterator; contextIterator != m_postContext.end(); ++contextIterator) {
			if (contextIterator->symbol != it->symbol) {
				return false;
			}
			++it;
		}

		return true;
	}
};
