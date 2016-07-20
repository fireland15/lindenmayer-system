#include "stdafx.h"
#include "CppUnitTest.h"

#include "../lindenmayer-system/string-to-symbols-converter.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace lindenmayersystemtest {
	TEST_CLASS(StringToSymbolsConverter) {
	public:
		TEST_METHOD(ContextConvert1) {
			std::string str = "ABC";

			LindenmayerString* result = StrToLstrConverter::ContextConvert(str);

			Assert::AreEqual((size_t) 3, result->Size());
			Assert::AreEqual('A', (*(*result)[0]).GetSymbol());
			Assert::AreEqual('B', (*(*result)[1]).GetSymbol());
			Assert::AreEqual('C', (*(*result)[2]).GetSymbol());
		}

		TEST_METHOD(ContextConvert2) {
			std::string str = "A()B()C()";

			LindenmayerString* result = StrToLstrConverter::ContextConvert(str);

			Assert::AreEqual((size_t)3, result->Size());
			Assert::AreEqual('A', (*(*result)[0]).GetSymbol());
			Assert::AreEqual('B', (*(*result)[1]).GetSymbol());
			Assert::AreEqual('C', (*(*result)[2]).GetSymbol());
		}

		TEST_METHOD(ContextConvert3) {
			std::string str = "A(x,c)B(5)C(b,l,k)";

			LindenmayerString* result = StrToLstrConverter::ContextConvert(str);

			Assert::AreEqual((size_t)3, result->Size());
			Assert::AreEqual('A', (*(*result)[0]).GetSymbol());
			Assert::AreEqual('B', (*(*result)[1]).GetSymbol());
			Assert::AreEqual('C', (*(*result)[2]).GetSymbol());
		}

		TEST_METHOD(ContextConvert4) {
			std::string str = "";

			LindenmayerString* result = StrToLstrConverter::ContextConvert(str);

			Assert::AreEqual((void*)nullptr, (void*)result);
		}

		TEST_METHOD(ResultConvert1) {
			std::string str = "";

			auto result = StrToLstrConverter::ResultConvert(str);

			Assert::AreEqual((size_t)0, result.size());
		}

		TEST_METHOD(ResultConvert2) {
			std::string str = "A()";

			auto result = StrToLstrConverter::ResultConvert(str);

			Assert::AreEqual((size_t)1, result.size());
			Assert::AreEqual((size_t)0, result[0].second.size());
		}

		TEST_METHOD(ResultConvert3) {
			std::string str = "A(2 + 3)";

			auto result = StrToLstrConverter::ResultConvert(str);

			Assert::AreEqual((size_t)1, result.size());
			Assert::AreEqual((size_t)1, result[0].second.size());
			result[0].second.begin()->Evaluate();
			float res = result[0].second.begin()->GetResult();
			Assert::AreEqual(5.0f, res);
		}

		TEST_METHOD(ResultConvert4) {
			std::string str = "A(2 + 3, 7)";

			auto result = StrToLstrConverter::ResultConvert(str);

			Assert::AreEqual((size_t)1, result.size());
			Assert::AreEqual((size_t)2, result[0].second.size());

			float compare[2] = { 5.0f, 7.0f };
			int i = 0;
			for (auto a : result[0].second) {
				a.Evaluate();
				Assert::AreEqual(compare[i++], a.GetResult());
			}
		}

		TEST_METHOD(ResultConvert5) {
			std::string str = "A(2 + 8, 90, 4)";

			auto result = StrToLstrConverter::ResultConvert(str);

			Assert::AreEqual((size_t)1, result.size());
			Assert::AreEqual((size_t)3, result[0].second.size());

			float compare[3] = { 10.0f, 90.0f, 4.0f };
			int i = 0;
			for (auto a : result[0].second) {
				a.Evaluate();
				Assert::AreEqual(compare[i++], a.GetResult());
			}
		}

		TEST_METHOD(ResultConvert6) {
			std::string str = "A()-B()";

			auto result = StrToLstrConverter::ResultConvert(str);

			Assert::AreEqual((size_t)2, result.size());
			Assert::AreEqual((size_t)0, result[0].second.size());
			Assert::AreEqual((size_t)0, result[1].second.size());
		}

		TEST_METHOD(ResultConvert7) {
			std::string str = "A()-B()-C()";

			auto result = StrToLstrConverter::ResultConvert(str);

			Assert::AreEqual((size_t)3, result.size());
			Assert::AreEqual((size_t)0, result[0].second.size());
			Assert::AreEqual((size_t)0, result[1].second.size());
			Assert::AreEqual((size_t)0, result[2].second.size());
		}

		TEST_METHOD(ResultConvert8) {
			std::string str = "A(3, (4+5)/9)-B(3)";

			auto result = StrToLstrConverter::ResultConvert(str);

			Assert::AreEqual((size_t)2, result.size());
			Assert::AreEqual((size_t)2, result[0].second.size());
			Assert::AreEqual((size_t)1, result[1].second.size());

			float compare1[2] = { 3.0f, 1.0f };
			int i = 0;
			for (auto a : result[0].second) {
				a.Evaluate();
				Assert::AreEqual(compare1[i++], a.GetResult());
			}
			
			float compare2[1] = { 3.0f };
			int j = 0;
			for (auto b : result[1].second) {
				b.Evaluate();
				Assert::AreEqual(compare2[j++], b.GetResult());
			}
		}
	};
}