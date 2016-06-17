#pragma once

#include <string>

#include "context-inspector.h"
#include "lindenmayer-string.h"
#include "string-to-symbols-converter.h"

class ContextInspectorBuilder {
private:
	StrToLstrConverter m_converter;

public:
	ContextInspector Build(std::string preContext, std::string postContext) {
		LindenmayerString* pPreLstr = m_converter.ContextConvert(preContext);
		LindenmayerString* pPostLstr = m_converter.ContextConvert(postContext);

		ContextInspector inspector(pPreLstr, pPostLstr);

		return inspector;
	}
};