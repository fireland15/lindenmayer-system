#include "context-inspector.h"

ContextInspector::ContextInspector() {
	m_preContext = nullptr;
	m_postContext = nullptr;
}

ContextInspector::ContextInspector(LindenmayerString* preContext, LindenmayerString* postContext)
	: m_preContext(preContext), m_postContext(postContext) { 
}

ContextInspector::ContextInspector(ContextInspector&& other)
	: m_preContext(other.m_preContext), m_postContext(other.m_postContext) {
	other.m_preContext = nullptr;
	other.m_postContext = nullptr;
}

ContextInspector::~ContextInspector() {
	if (m_preContext != nullptr)
		delete m_preContext;

	if (m_postContext != nullptr)
		delete m_postContext;
}

bool ContextInspector::TestContext(LindenmayerString::Iterator& it) {
	bool lookBehindResult = TestPreContext(--it);
	bool lookAheadResult = TestPostContext(++(++it));
	return lookAheadResult && lookBehindResult;
}

bool ContextInspector::TestPreContext(LindenmayerString::Iterator& it) {
	if (m_preContext == nullptr)
		return true;

	LindenmayerString::Iterator cIt = m_preContext->Last();

	while (!it.AtStart() && !cIt.AtStart()) {
		if (it != cIt)
			return false;

		--it; --cIt;
	}

	if (it.AtStart() && !cIt.AtStart())
		return false;

	return true;
}

bool ContextInspector::TestPostContext(LindenmayerString::Iterator& it) {
	if (m_postContext == nullptr)
		return true;

	LindenmayerString::Iterator cIt = m_postContext->Begin();

	while (!it.AtEnd() && !cIt.AtEnd()) {
		if (it != cIt)
			return false;

		++it; ++cIt;
	}

	if (it.AtEnd() && !cIt.AtEnd())
		return false;

	return true;
}