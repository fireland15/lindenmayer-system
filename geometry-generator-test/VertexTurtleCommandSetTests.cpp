#include "stdafx.h"
#include "CppUnitTest.h"

#include "../geometry-generator/VertexTurtleCommandSet.h"
#include "../geometry-generator/TurtleState.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace geometrygeneratortest{
	TEST_CLASS(VertexTurtleCommandSetTests) {
	public:
		TEST_METHOD(ForwardTest) {
			TurtleState state = TurtleState();
			ITurtleCommandSet* pCmdSet = new VertexTurtleCommandSet();
			auto cmd = pCmdSet->GetForwardCommand(1.0f);

			cmd(state);

			Assert::AreEqual(0.0f, state.position.x);
			Assert::AreEqual(0.0f, state.position.y);
			Assert::AreEqual(1.0f, state.position.z);
		}

		TEST_METHOD(YawLeftTest) {
			TurtleState state = TurtleState();
			state.position = glm::vec3(0.0f, 0.0f, 0.0f);
			state.orientation = glm::vec3(0.0f, 0.0f, 1.0f);
			ITurtleCommandSet* pCmdSet = new VertexTurtleCommandSet();
			BaseStateCmd cmd = pCmdSet->GetYawLeftCommand(90.0f);

			cmd(state);

			Assert::AreEqual(0.0f, state.position.x);
			Assert::AreEqual(0.0f, state.position.y);
			Assert::AreEqual(0.0f, state.position.z);

			Assert::IsTrue(abs(1.0f - state.orientation.x) < FLT_EPSILON);
			Assert::IsTrue(abs(0.0f - state.orientation.y) < FLT_EPSILON);
			Assert::IsTrue(abs(0.0f - state.orientation.z) < FLT_EPSILON);
		}

		TEST_METHOD(YawRightTest) {
			TurtleState state = TurtleState();
			state.position = glm::vec3(0.0f, 0.0f, 0.0f);
			state.orientation = glm::vec3(0.0f, 0.0f, 1.0f);
			ITurtleCommandSet* pCmdSet = new VertexTurtleCommandSet();
			BaseStateCmd cmd = pCmdSet->GetYawRightCommand(90.0f);

			cmd(state);

			Assert::AreEqual(0.0f, state.position.x);
			Assert::AreEqual(0.0f, state.position.y);
			Assert::AreEqual(0.0f, state.position.z);

			Assert::IsTrue(abs(-1.0f - state.orientation.x) < FLT_EPSILON);
			Assert::IsTrue(abs(0.0f - state.orientation.y) < FLT_EPSILON);
			Assert::IsTrue(abs(0.0f - state.orientation.z) < FLT_EPSILON);
		}

		TEST_METHOD(PitchDownTest) {
			TurtleState state = TurtleState();
			state.position = glm::vec3(0.0f, 0.0f, 0.0f);
			state.orientation = glm::vec3(0.0f, 0.0f, 1.0f);
			ITurtleCommandSet* pCmdSet = new VertexTurtleCommandSet();
			BaseStateCmd cmd = pCmdSet->GetPitchDownCommand(90.0f);

			cmd(state);

			Assert::AreEqual(0.0f, state.position.x);
			Assert::AreEqual(0.0f, state.position.y);
			Assert::AreEqual(0.0f, state.position.z);

			Assert::IsTrue(abs(0.0f - state.orientation.x) < FLT_EPSILON);
			Assert::IsTrue(abs(-1.0f - state.orientation.y) < FLT_EPSILON);
			Assert::IsTrue(abs(0.0f - state.orientation.z) < FLT_EPSILON);
		}

		TEST_METHOD(PitchUpTest) {
			TurtleState state = TurtleState();
			state.position = glm::vec3(0.0f, 0.0f, 0.0f);
			state.orientation = glm::vec3(0.0f, 0.0f, 1.0f);
			ITurtleCommandSet* pCmdSet = new VertexTurtleCommandSet();
			BaseStateCmd cmd = pCmdSet->GetPitchUpCommand(90.0f);

			cmd(state);

			Assert::AreEqual(0.0f, state.position.x);
			Assert::AreEqual(0.0f, state.position.y);
			Assert::AreEqual(0.0f, state.position.z);

			Assert::IsTrue(abs(0.0f - state.orientation.x) < FLT_EPSILON);
			Assert::IsTrue(abs(1.0f - state.orientation.y) < FLT_EPSILON);
			Assert::IsTrue(abs(0.0f - state.orientation.z) < FLT_EPSILON);
		}

		TEST_METHOD(RollLeftTest) {
			TurtleState state = TurtleState();
			state.position = glm::vec3(0.0f, 0.0f, 0.0f);
			state.orientation = glm::vec3(0.0f, 1.0f, 0.0f);
			ITurtleCommandSet* pCmdSet = new VertexTurtleCommandSet();
			BaseStateCmd cmd = pCmdSet->GetRollLeftCommand(90.0f);

			cmd(state);

			Assert::AreEqual(0.0f, state.position.x);
			Assert::AreEqual(0.0f, state.position.y);
			Assert::AreEqual(0.0f, state.position.z);

			Assert::IsTrue(abs(1.0f - state.orientation.x) < FLT_EPSILON);
			Assert::IsTrue(abs(0.0f - state.orientation.y) < FLT_EPSILON);
			Assert::IsTrue(abs(0.0f - state.orientation.z) < FLT_EPSILON);
		}

		TEST_METHOD(RollRightTest) {
			TurtleState state = TurtleState();
			state.position = glm::vec3(0.0f, 0.0f, 0.0f);
			state.orientation = glm::vec3(0.0f, 1.0f, 0.0f);
			ITurtleCommandSet* pCmdSet = new VertexTurtleCommandSet();
			BaseStateCmd cmd = pCmdSet->GetRollRightCommand(90.0f);

			cmd(state);

			Assert::AreEqual(0.0f, state.position.x);
			Assert::AreEqual(0.0f, state.position.y);
			Assert::AreEqual(0.0f, state.position.z);

			Assert::IsTrue(abs(-1.0f - state.orientation.x) < FLT_EPSILON);
			Assert::IsTrue(abs(0.0f - state.orientation.y) < FLT_EPSILON);
			Assert::IsTrue(abs(0.0f - state.orientation.z) < FLT_EPSILON);
		}
	};
}