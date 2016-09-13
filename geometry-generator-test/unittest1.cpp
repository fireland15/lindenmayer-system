#include "stdafx.h"
#include "CppUnitTest.h"

#include <functional>

#include "../geometry-generator/Graph.h"
#include "../geometry-generator/TurtleCommand.h"
#include "../geometry-generator/BaseTurtle.h"
#include "../geometry-generator/RecordedTurtle.h"
#include "../geometry-generator/ListRecorder.h"
#include "../geometry-generator/ListRecordInterpreter.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace geometrygeneratortest
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			Graph<int, int> graph;
			std::shared_ptr<Graph<int, int>::Node> node1 = graph.AddNode(27);
			auto node2 = graph.AddNode(node1, 34, 36);

			
		}

		TEST_METHOD(test2) {
			TurtleCommand<int> cmd([](int& state) { 
				state += 994;
			});

			BaseTurtle<int> turtle(27);
			cmd.Execute(turtle);
			Assert::AreEqual(turtle.GetState(), 27 + 994);
		}

		TEST_METHOD(test3) {
			ListRecorder<int> recorder;

			RecordedTurtle<int> turtle(27, recorder);

			TurtleCommand<int> cmd([](int& state) {
				state += 13;
			});

			std::function<void(int&)> func = [](int& state) { state++; };

			TurtleCommand<int> funcCmd(func);

			cmd.Execute(turtle);
			cmd.Execute(turtle);
			funcCmd.Execute(turtle);

			auto states = recorder.GetStates();

			ListRecordInterpreter<int> interpreter;

			interpreter.Interpret(states);
		}
	};
}