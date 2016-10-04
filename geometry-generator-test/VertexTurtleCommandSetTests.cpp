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
			TurtleCommandFunction cmd = pCmdSet->GetYawLeftCommand(90.0f);

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
			TurtleCommandFunction cmd = pCmdSet->GetYawRightCommand(90.0f);

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
			TurtleCommandFunction cmd = pCmdSet->GetPitchDownCommand(90.0f);

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
			TurtleCommandFunction cmd = pCmdSet->GetPitchUpCommand(90.0f);

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
			TurtleCommandFunction cmd = pCmdSet->GetRollLeftCommand(90.0f);

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
			TurtleCommandFunction cmd = pCmdSet->GetRollRightCommand(90.0f);

			cmd(state);

			Assert::AreEqual(0.0f, state.position.x);
			Assert::AreEqual(0.0f, state.position.y);
			Assert::AreEqual(0.0f, state.position.z);

			Assert::IsTrue(abs(-1.0f - state.orientation.x) < FLT_EPSILON);
			Assert::IsTrue(abs(0.0f - state.orientation.y) < FLT_EPSILON);
			Assert::IsTrue(abs(0.0f - state.orientation.z) < FLT_EPSILON);
		}

		TEST_METHOD(TurnAroundTest) {
			TurtleState state = TurtleState();
			state.position = glm::vec3(0.0f, 0.0f, 0.0f);
			state.orientation = glm::normalize(glm::vec3(1.0f, 1.0f, 1.0f));
			ITurtleCommandSet* pCmdSet = new VertexTurtleCommandSet();
			TurtleCommandFunction cmd = pCmdSet->GetTurnAroundCommand();

			cmd(state);

			Assert::AreEqual(0.0f, state.position.x);
			Assert::AreEqual(0.0f, state.position.y);
			Assert::AreEqual(0.0f, state.position.z);

			Assert::IsTrue(abs(-std::sqrt(1.0f / 3.0f) - state.orientation.x) < FLT_EPSILON);
			Assert::IsTrue(abs(-std::sqrt(1.0f / 3.0f) - state.orientation.y) < FLT_EPSILON);
			Assert::IsTrue(abs(-std::sqrt(1.0f / 3.0f) - state.orientation.z) < FLT_EPSILON);
		}

		TEST_METHOD(PushPopStateTest) {
			TurtleState state = TurtleState();
			state.position = glm::vec3(0.0f, 0.0f, 0.0f);
			state.orientation = glm::normalize(glm::vec3(1.0f, 1.0f, 1.0f));
			ITurtleCommandSet* pCmdSet = new VertexTurtleCommandSet();
			TurtleCommandFunction cmd = pCmdSet->GetPushCommand();

			cmd(state);

			state.position = glm::vec3(100.0f, 343.5f, 3434.9f);

			cmd = pCmdSet->GetPopCommand();

			cmd(state);

			Assert::AreEqual(0.0f, state.position.x);
			Assert::AreEqual(0.0f, state.position.y);
			Assert::AreEqual(0.0f, state.position.z);

			Assert::IsTrue(abs(std::sqrt(1.0f / 3.0f) - state.orientation.x) < FLT_EPSILON);
			Assert::IsTrue(abs(std::sqrt(1.0f / 3.0f) - state.orientation.y) < FLT_EPSILON);
			Assert::IsTrue(abs(std::sqrt(1.0f / 3.0f) - state.orientation.z) < FLT_EPSILON);
		}
	};
}