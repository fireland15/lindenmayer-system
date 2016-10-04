#pragma once

#include <memory>

#include "BaseRecorder.h"
#include "TurtleState.h"

enum TurtleType {
	Base,
	ListRecorded
};

class TurtleFactory {
private:

public:
	static std::unique_ptr<Turtle> MakeTurtle(std::shared_ptr<BaseRecorder> pRecorder) {
		return std::unique_ptr<Turtle>(new Turtle(MakeInitState(), pRecorder));
	}

private:
	static TurtleState MakeInitState() {
		TurtleState initState;
		initState.position = glm::vec3(0.0f, 0.0f, 0.0f);
		initState.orientation = glm::vec3(0.0f, 1.0f, 0.0f);
		return initState;
	}
};