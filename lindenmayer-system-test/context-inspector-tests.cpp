#include "stdafx.h"
#include "CppUnitTest.h"

#include "../lindenmayer-system/context-inspector.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace lindenmayersystemtest {		
	TEST_CLASS(ContextInspectorTests) {
	public:
		TEST_METHOD(NoContext) {
			LindenmayerString str;
			str.Add(LindenmayerSymbol());

			ContextInspector inspector(nullptr, nullptr);
			//bool result = inspector.TestContext();
		}
	};
}