#define _USE_MATH_DEFINES
#include "stdafx.h"
#include "CppUnitTest.h"

#include <OpenMesh\Core\Mesh\PolyMesh_ArrayKernelT.hh>
#include <OpenMesh\Core\IO\MeshIO.hh>
#include <OpenMesh/Tools/Subdivider/Uniform/CatmullClarkT.hh>
#include <memory>

#include "../geometry-generator/LStringInterpreter.h"
#include "../lindenmayer-system/lindenmayer-string.h"
#include "../lindenmayer-system/lindenmayer-symbol.h"
#include "../lindenmayer-system/factories.h"
#include "../lindenmayer-system/production-rule.h"
#include "../lindenmayer-system/lindenmayer-system.h"
#include "../geometry-generator/Mesh.h"
#include "../geometry-generator/GeometryGenerator.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace fli::geometry_generator;

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
			rules.push_back(std::move(CreateProductionRule(std::string("f(a) : F(a)-p(22.5)-B()-B()-f(a)-b()-P(22.5)-f(a)-b()-P(22.5)-F(a)-B()-P(22.5)-F(a)-f(a)-b()-p(22.5)-f(a)"))));
			rules.push_back(std::move(CreateProductionRule(std::string("F(a) : F(a)-F(a)"))));
			LindenmayerString lString;
			lString.Add(LindenmayerSymbol('f', { 10 }));

			LindenmayerSystem system = LindenmayerSystem(lString, std::move(rules));
			LindenmayerString result = system.Run(3);

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

		TEST_METHOD(GraphRecorderTest) {
			std::vector<ProductionRule> rules;
			rules.push_back(std::move(CreateProductionRule(std::string("f(a) : F(a)-p(22.5)-B()-B()-f(a)-b()-P(22.5)-f(a)-b()-P(22.5)-F(a)-B()-P(22.5)-F(a)-f(a)-b()-p(22.5)-f(a)"))));
			rules.push_back(std::move(CreateProductionRule(std::string("F(a) : F(a)-F(a)"))));
			LindenmayerString lString;
			lString.Add(LindenmayerSymbol('f', { 10 }));

			LindenmayerSystem system = LindenmayerSystem(lString, std::move(rules));
			LindenmayerString result = system.Run(3);

			LStringInterpreter interpreter(GeometryType::Tubes);
			std::unique_ptr<Mesh> mesh = interpreter.Interpret(result);

			try
			{
				if (!OpenMesh::IO::write_mesh(mesh.operator*(), "GraphRecorderTest.obj", OpenMesh::IO::Options::ColorFloat))
				{
					std::cerr << "Cannot write mesh to file 'output.obj'" << std::endl;
				}
			}
			catch (std::exception& x)
			{
				std::cerr << x.what() << std::endl;
			}
		}

		TEST_METHOD(Test6Tubes) {
			std::vector<ProductionRule> rules;
			rules.push_back(std::move(CreateProductionRule(std::string("f(a) : F(a)-B()-P(25.7)-f(a)-b()-B()-p(25.7)-f(a)-b()-F(a)-f(a)"))));
			rules.push_back(std::move(CreateProductionRule(std::string("F(a) : F(a)-F(a)"))));
			LindenmayerString lString;
			lString.Add(LindenmayerSymbol('f', { 10 }));

			LindenmayerSystem system = LindenmayerSystem(lString, std::move(rules));
			LindenmayerString result = system.Run(2);

			LStringInterpreter interpreter(GeometryType::Tubes);
			std::unique_ptr<Mesh> mesh = interpreter.Interpret(result);

			try
			{
				if (!OpenMesh::IO::write_mesh(mesh.operator*(), "test6tubes.obj", OpenMesh::IO::Options::ColorFloat))
				{
					std::cerr << "Cannot write mesh to file 'output.obj'" << std::endl;
				}
			}
			catch (std::exception& x)
			{
				std::cerr << x.what() << std::endl;
			}
		}

		TEST_METHOD(TestSmooth) {
			std::vector<ProductionRule> rules;
			rules.push_back(std::move(CreateProductionRule(std::string("f(a) : F(a)-B()-P(25.7)-f(a)-b()-B()-p(25.7)-f(a)-b()-F(a)-f(a)"))));
			//rules.push_back(std::move(CreateProductionRule(std::string("f(a) : F(a)-B()-P(25.7)-f(a)-b()-B()-p(25.7)-f(a)-b()-B()-Y(25.7)-f(a)-b()-F(a)-f(a)"))));
			rules.push_back(std::move(CreateProductionRule(std::string("F(a) : F(a)-F(a)"))));
			LindenmayerString lString;
			lString.Add(LindenmayerSymbol('f', { 20 }));

			LindenmayerSystem system = LindenmayerSystem(lString, std::move(rules));
			LindenmayerString result = system.Run(4);

			LStringInterpreter interpreter(GeometryType::Smooth);
			std::unique_ptr<Mesh> mesh = interpreter.Interpret(result);

			OpenMesh::Subdivider::Uniform::CatmullClarkT<Mesh> catmull;

			catmull.attach(*mesh);
			catmull(1);
			catmull.detach();

			try
			{
				if (!OpenMesh::IO::write_mesh(mesh.operator*(), "testsmooth.obj", OpenMesh::IO::Options::ColorFloat))
				{
					std::cerr << "Cannot write mesh to file 'output.obj'" << std::endl;
				}
			}
			catch (std::exception& x)
			{
				std::cerr << x.what() << std::endl;
			}
		}

		TEST_METHOD(TestSmooth2) {
			std::vector<ProductionRule> rules;
			rules.push_back(std::move(CreateProductionRule(std::string("f(a) : F(a)-B()-P(10)-Y(30)-F(a/3)-F(a/3)-f(a/2)-b()-B()-p(10)-y(30)-F(a/3)-F(a/3)-f(a/2)-b()-F(a)-f(a)"))));
			rules.push_back(std::move(CreateProductionRule(std::string("F(a) : F(a)"))));
			LindenmayerString lString;
			lString.Add(LindenmayerSymbol('f', { 10 }));

			LindenmayerSystem system = LindenmayerSystem(lString, std::move(rules));
			LindenmayerString result = system.Run(4);

			LStringInterpreter interpreter(GeometryType::Smooth);
			std::unique_ptr<Mesh> mesh = interpreter.Interpret(result);

			OpenMesh::Subdivider::Uniform::CatmullClarkT<Mesh> catmull;

			catmull.attach(*mesh);
			catmull(1);
			catmull.detach();

			try
			{
				if (!OpenMesh::IO::write_mesh(mesh.operator*(), "testsmooth2.obj", OpenMesh::IO::Options::ColorFloat))
				{
					std::cerr << "Cannot write mesh to file 'output.obj'" << std::endl;
				}
			}
			catch (std::exception& x)
			{
				std::cerr << x.what() << std::endl;
			}
		}

		TEST_METHOD(GeomGen) {
			std::vector<ProductionRule> rules;
			rules.push_back(std::move(CreateProductionRule(std::string("F() < f(a) : f(a)-R(44)-B()-P(25)-F(a)-F(a)-b()"))));
			rules.push_back(std::move(CreateProductionRule(std::string("f(a) : R(44)-B()-P(80)-F(a)-F(a)-f(a)-b()-f(a)"))));
			LindenmayerString lString;
			lString.Add(LindenmayerSymbol('f', { 10 }));

			LindenmayerSystem system = LindenmayerSystem(lString, std::move(rules));
			LindenmayerString result = system.Run(8);

			GeometryGenerator geomgen(GeometryType::Smooth);
			geomgen.set_InterpreterRules(TurtleCommandSetType::TurtleCentric);
			std::unique_ptr<Mesh> mesh = geomgen.Generate(result);

			OpenMesh::Subdivider::Uniform::CatmullClarkT<Mesh> catmull;

			//catmull.attach(*mesh);
			//catmull(2);
			//catmull.detach();

			try
			{
				if (!OpenMesh::IO::write_mesh(mesh.operator*(), "GeomGen.obj", OpenMesh::IO::Options::ColorFloat))
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