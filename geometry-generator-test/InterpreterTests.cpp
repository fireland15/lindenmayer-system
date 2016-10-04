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
			rules.push_back(std::move(CreateProductionRule(std::string("F(a) : F(a/6)-F(a/6)-F(a/6)-B()-P(50)-F(a/6)-F(a/6)-F(a/6)-b()-p(2)-F(a/6)-F(a/6)-F(a/6)"))));
			LindenmayerString lString;
			lString.Add(LindenmayerSymbol('F', { 20 }));

			LindenmayerSystem system = LindenmayerSystem(lString, std::move(rules));
			LindenmayerString result = system.Run(3);

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

		TEST_METHOD(Test6) {
			std::vector<ProductionRule> rules;
			rules.push_back(std::move(CreateProductionRule(std::string("f(a) : F(1)-B()-P(25.7)-f(1)-b()-B()-p(25.7)-f(1)-b()-F(1)-f(1)"))));
			rules.push_back(std::move(CreateProductionRule(std::string("F(a) : F(a)-F(a)"))));
			LindenmayerString lString;
			lString.Add(LindenmayerSymbol('f', { 1 }));

			LindenmayerSystem system = LindenmayerSystem(lString, std::move(rules));
			LindenmayerString result = system.Run(7);

			LStringInterpreter interpreter;
			std::unique_ptr<Mesh> mesh = interpreter.Interpret(result);

			try
			{
				if (!OpenMesh::IO::write_mesh(mesh.operator*(), "test6.obj", OpenMesh::IO::Options::ColorFloat))
				{
					std::cerr << "Cannot write mesh to file 'output.obj'" << std::endl;
				}
			}
			catch (std::exception& x)
			{
				std::cerr << x.what() << std::endl;
			}
		}

		TEST_METHOD(Test7) {
			std::vector<ProductionRule> rules;
			rules.push_back(std::move(CreateProductionRule(std::string("f(a) : F(1)-p(22.5)-B()-B()-f(1)-b()-P(22.5)-f(1)-b()-P(22.5)-F(1)-B()-P(22.5)-F(1)-f(1)-b()-p(22.5)-f(1)"))));
			rules.push_back(std::move(CreateProductionRule(std::string("F(a) : F(a)-F(a)"))));
			LindenmayerString lString;
			lString.Add(LindenmayerSymbol('f', { 1 }));

			LindenmayerSystem system = LindenmayerSystem(lString, std::move(rules));
			LindenmayerString result = system.Run(5);

			LStringInterpreter interpreter;
			std::unique_ptr<Mesh> mesh = interpreter.Interpret(result);

			try
			{
				if (!OpenMesh::IO::write_mesh(mesh.operator*(), "test7.obj", OpenMesh::IO::Options::ColorFloat))
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