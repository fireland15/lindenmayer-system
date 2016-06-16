#include "stdafx.h"
#include "CppUnitTest.h"

#include "../lindenmayer-system/context-inspector.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace lindenmayersystemtest {		
	TEST_CLASS(ContextInspectorTests) {
	public:
		TEST_METHOD(NoContext) {
			LindenmayerString str;
			str.Add(LindenmayerSymbol('a'));
			str.Add(LindenmayerSymbol('b'));
			str.Add(LindenmayerSymbol('c'));
			str.Add(LindenmayerSymbol('d'));
			str.Add(LindenmayerSymbol('e'));
			str.Add(LindenmayerSymbol('f'));

			ContextInspector inspector(nullptr, nullptr);
			bool result = inspector.TestContext(2, str);

			Assert::AreEqual(true, result);
		}

		TEST_METHOD(PreContextMatchOnly) {
			LindenmayerString str;
			str.Add(LindenmayerSymbol('a'));
			str.Add(LindenmayerSymbol('b'));
			str.Add(LindenmayerSymbol('c'));
			str.Add(LindenmayerSymbol('d'));
			str.Add(LindenmayerSymbol('e'));
			str.Add(LindenmayerSymbol('f'));

			LindenmayerString* preContext = new LindenmayerString;
			preContext->Add(LindenmayerSymbol('a'));
			preContext->Add(LindenmayerSymbol('b'));

			ContextInspector inspector(preContext, nullptr);
			bool result = inspector.TestContext(2, str);

			Assert::AreEqual(true, result);
		}

		TEST_METHOD(PreContextNoMatchOnly) {
			LindenmayerString str;
			str.Add(LindenmayerSymbol('a'));
			str.Add(LindenmayerSymbol('b'));
			str.Add(LindenmayerSymbol('c'));
			str.Add(LindenmayerSymbol('d'));
			str.Add(LindenmayerSymbol('e'));
			str.Add(LindenmayerSymbol('f'));

			LindenmayerString* preContext = new LindenmayerString;
			preContext->Add(LindenmayerSymbol('b'));
			preContext->Add(LindenmayerSymbol('b'));

			ContextInspector inspector(preContext, nullptr);
			bool result = inspector.TestContext(2, str);

			Assert::AreEqual(false, result);
		}

		TEST_METHOD(PostContextMatchOnly) {
			LindenmayerString str;
			str.Add(LindenmayerSymbol('a'));
			str.Add(LindenmayerSymbol('b'));
			str.Add(LindenmayerSymbol('c'));
			str.Add(LindenmayerSymbol('d'));
			str.Add(LindenmayerSymbol('e'));
			str.Add(LindenmayerSymbol('f'));

			LindenmayerString* postContext = new LindenmayerString;
			postContext->Add(LindenmayerSymbol('d'));
			postContext->Add(LindenmayerSymbol('e'));

			ContextInspector inspector(nullptr, postContext);
			bool result = inspector.TestContext(2, str);

			Assert::AreEqual(true, result);
		}

		TEST_METHOD(PostContextNoMatchOnly) {
			LindenmayerString str;
			str.Add(LindenmayerSymbol('a'));
			str.Add(LindenmayerSymbol('b'));
			str.Add(LindenmayerSymbol('c'));
			str.Add(LindenmayerSymbol('d'));
			str.Add(LindenmayerSymbol('e'));
			str.Add(LindenmayerSymbol('f'));

			LindenmayerString* postContext = new LindenmayerString;
			postContext->Add(LindenmayerSymbol('d'));
			postContext->Add(LindenmayerSymbol('j'));

			ContextInspector inspector(nullptr, postContext);
			bool result = inspector.TestContext(2, str);

			Assert::AreEqual(false, result);
		}

		TEST_METHOD(FullContextMatch) {
			LindenmayerString str;
			str.Add(LindenmayerSymbol('a'));
			str.Add(LindenmayerSymbol('b'));
			str.Add(LindenmayerSymbol('c'));
			str.Add(LindenmayerSymbol('d'));
			str.Add(LindenmayerSymbol('e'));
			str.Add(LindenmayerSymbol('f'));

			LindenmayerString* preContext = new LindenmayerString;
			preContext->Add(LindenmayerSymbol('a'));
			preContext->Add(LindenmayerSymbol('b'));

			LindenmayerString* postContext = new LindenmayerString;
			postContext->Add(LindenmayerSymbol('d'));
			postContext->Add(LindenmayerSymbol('e'));

			ContextInspector inspector(preContext, postContext);
			bool result = inspector.TestContext(2, str);

			Assert::AreEqual(true, result);
		}

		TEST_METHOD(FullContextNoMatchNoPreContext) {
			LindenmayerString str;
			str.Add(LindenmayerSymbol('a'));
			str.Add(LindenmayerSymbol('b'));
			str.Add(LindenmayerSymbol('c'));
			str.Add(LindenmayerSymbol('d'));
			str.Add(LindenmayerSymbol('e'));
			str.Add(LindenmayerSymbol('f'));

			LindenmayerString* preContext = new LindenmayerString;
			preContext->Add(LindenmayerSymbol('b'));
			preContext->Add(LindenmayerSymbol('b'));

			LindenmayerString* postContext = new LindenmayerString;
			postContext->Add(LindenmayerSymbol('d'));
			postContext->Add(LindenmayerSymbol('e'));

			ContextInspector inspector(preContext, postContext);
			bool result = inspector.TestContext(2, str);

			Assert::AreEqual(false, result);
		}

		TEST_METHOD(FullContextNoMatchNoPostContext) {
			LindenmayerString str;
			str.Add(LindenmayerSymbol('a'));
			str.Add(LindenmayerSymbol('b'));
			str.Add(LindenmayerSymbol('c'));
			str.Add(LindenmayerSymbol('d'));
			str.Add(LindenmayerSymbol('e'));
			str.Add(LindenmayerSymbol('f'));

			LindenmayerString* preContext = new LindenmayerString;
			preContext->Add(LindenmayerSymbol('a'));
			preContext->Add(LindenmayerSymbol('b'));

			LindenmayerString* postContext = new LindenmayerString;
			postContext->Add(LindenmayerSymbol('d'));
			postContext->Add(LindenmayerSymbol('j'));

			ContextInspector inspector(preContext, postContext);
			bool result = inspector.TestContext(2, str);

			Assert::AreEqual(false, result);
		}

		TEST_METHOD(FullContextNoMatch) {
			LindenmayerString str;
			str.Add(LindenmayerSymbol('a'));
			str.Add(LindenmayerSymbol('b'));
			str.Add(LindenmayerSymbol('c'));
			str.Add(LindenmayerSymbol('d'));
			str.Add(LindenmayerSymbol('e'));
			str.Add(LindenmayerSymbol('f'));

			LindenmayerString* preContext = new LindenmayerString;
			preContext->Add(LindenmayerSymbol('n'));
			preContext->Add(LindenmayerSymbol('b'));

			LindenmayerString* postContext = new LindenmayerString;
			postContext->Add(LindenmayerSymbol('d'));
			postContext->Add(LindenmayerSymbol('j'));

			ContextInspector inspector(preContext, postContext);
			bool result = inspector.TestContext(2, str);

			Assert::AreEqual(false, result);
		}
	};
}