#include "stdafx.h"
#include "CppUnitTest.h"

#include "../lindenmayer-system/ContextInspector.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace lindenmayersystemtest
{		
	TEST_CLASS(ContextInspectorTests)
	{
	public:
		
		TEST_METHOD(TestPreContext)
		{
			std::list<LindenmayerSymbol> preContext;
			preContext.push_back(LindenmayerSymbol{'a'});
		}

	};
}