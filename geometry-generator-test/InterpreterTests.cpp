#define _USE_MATH_DEFINES
#include "stdafx.h"
#include "CppUnitTest.h"

#include <OpenMesh\Core\Mesh\PolyMesh_ArrayKernelT.hh>
#include <OpenMesh\Core\IO\MeshIO.hh>
#include <memory>

#include "../geometry-generator/LStringInterpreter.h"
#include "../lindenmayer-system/lindenmayer-string.h"
#include "../lindenmayer-system/lindenmayer-symbol.h"
#include "../lindenmayer-system/factories.h"
#include "../lindenmayer-system/production-rule.h"
#include "../lindenmayer-system/lindenmayer-system.h"
#include "../geometry-generator/Mesh.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace geometrygeneratortest {
	TEST_CLASS(InterpreterTest) {
	public:
		TEST_METHOD(Test1) {
			LindenmayerString lString;
			lString.Add(LindenmayerSymbol('F', { 1.0f }));
			lString.Add(LindenmayerSymbol('F', { 1.0f }));
			lString.Add(LindenmayerSymbol('F', { 1.0f }));
			lString.Add(LindenmayerSymbol('F', { 1.0f }));

			LStringInterpreter interpreter;
			std::unique_ptr<Mesh> mesh = interpreter.Interpret(lString);

			try
			{
				if (!OpenMesh::IO::write_mesh(mesh.operator*(), "test1.obj"))
				{
					std::cerr << "Cannot write mesh to file 'output.obj'" << std::endl;
				}
			}
			catch (std::exception& x)
			{
				std::cerr << x.what() << std::endl;
			}
		}

		TEST_METHOD(Test2) {
			LindenmayerString lString;
			lString.Add(LindenmayerSymbol('F', { 1.0f }));
			lString.Add(LindenmayerSymbol('Y', { 90.0f }));
			lString.Add(LindenmayerSymbol('F', { 1.0f }));
			lString.Add(LindenmayerSymbol('F', { 1.0f }));

			LStringInterpreter interpreter;
			std::unique_ptr<Mesh> mesh = interpreter.Interpret(lString);

			try
			{
				if (!OpenMesh::IO::write_mesh(mesh.operator*(), "test2.obj"))
				{
					std::cerr << "Cannot write mesh to file 'output.obj'" << std::endl;
				}
			}
			catch (std::exception& x)
			{
				std::cerr << x.what() << std::endl;
			}
		}

		TEST_METHOD(Test3) {
			std::vector<ProductionRule> rules;
			rules.push_back(std::move(CreateProductionRule(std::string("F(a) : F(a / 2)-P(90)-F(a / 2)-y(90)-F(a / 2)"))));
			LindenmayerString lString;
			lString.Add(LindenmayerSymbol('F', { 10 }));

			LindenmayerSystem system = LindenmayerSystem(lString, std::move(rules));
			LindenmayerString result = system.Run(1);

			LStringInterpreter interpreter;
			std::unique_ptr<Mesh> mesh = interpreter.Interpret(result);

			try
			{
				if (!OpenMesh::IO::write_mesh(mesh.operator*(), "test3.obj"))
				{
					std::cerr << "Cannot write mesh to file 'output.obj'" << std::endl;
				}
			}
			catch (std::exception& x)
			{
				std::cerr << x.what() << std::endl;
			}
		}

		TEST_METHOD(Test4) {
			std::vector<ProductionRule> rules;
			rules.push_back(std::move(CreateProductionRule(std::string("F(a) : F(a / 3)-R(60)-F(a / 3)-r(60)-r(60)-F(a / 3)-R(60)-F(a/3)"))));
			LindenmayerString lString;
			lString.Add(LindenmayerSymbol('F', { 20 }));

			LindenmayerSystem system = LindenmayerSystem(lString, std::move(rules));
			LindenmayerString result = system.Run(4);

			LStringInterpreter interpreter;
			std::unique_ptr<Mesh> mesh = interpreter.Interpret(result);

			try
			{
				if (!OpenMesh::IO::write_mesh(mesh.operator*(), "test4.obj", OpenMesh::IO::Options::ColorFloat))
				{
					std::cerr << "Cannot write mesh to file 'output.obj'" << std::endl;
				}
			}
			catch (std::exception& x)
			{
				std::cerr << x.what() << std::endl;
			}
		}

		TEST_METHOD(Test5) {
			std::vector<ProductionRule> rules;
			rules.push_back(std::move(CreateProductionRule(std::string("F(a) : F(a/6)-F(a/6)-F(a/6)-B()-P(30)-F(a/6)-F(a/6)-F(a/6)-b()-p(30)-F(a/6)-F(a/6)-F(a/6)"))));
			LindenmayerString lString;
			lString.Add(LindenmayerSymbol('F', { 20 }));

			LindenmayerSystem system = LindenmayerSystem(lString, std::move(rules));
			LindenmayerString result = system.Run(1);

			LStringInterpreter interpreter;
			std::unique_ptr<Mesh> mesh = interpreter.Interpret(result);

			try
			{
				if (!OpenMesh::IO::write_mesh(mesh.operator*(), "test5.obj", OpenMesh::IO::Options::ColorFloat))
				{
					std::cerr << "Cannot write mesh to file 'output.obj'" << std::endl;
				}
			}
			catch (std::exception& x)
			{
				std::cerr << x.what() << std::endl;
			}
		}
	};
}