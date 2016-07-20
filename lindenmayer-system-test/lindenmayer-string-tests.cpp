#include "stdafx.h"
#include "CppUnitTest.h"

#include "../lindenmayer-system/lindenmayer-string.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace lindenmayersystemtest {
	TEST_CLASS(LindenmayerStringTests) {
	public:
		TEST_METHOD(Swap) {
			LindenmayerString str1;
			LindenmayerString str2;

			str1.Add(LindenmayerSymbol('A', {}));
			str1.Add(LindenmayerSymbol('A', {}));
			str1.Add(LindenmayerSymbol('A', {}));
			str1.Add(LindenmayerSymbol('A', {}));

			str2.Add(LindenmayerSymbol('B', {}));

			std::swap(str1, str2);

			Assert::AreEqual((unsigned int)1, str1.Size());
			Assert::AreEqual((unsigned int)4, str2.Size());
		}
	};
}