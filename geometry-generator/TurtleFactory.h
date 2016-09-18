#pragma once

#include "BaseTurtle.h"
#include "RecordedTurtle.h"
#include "ListRecorder.h"
#include "TurtleState.h"

enum TurtleType {
	Base,
	ListRecorded
};

class TurtleFactory {
private:

public:
	BaseTurtle MakeTurtle(TurtleType type) {
		switch (type) {
		case TurtleType::Base: {
			return BaseTurtle(MakeInitState());
		}
		break;
		case TurtleType::ListRecorded: {
			return RecordedTurtle(MakeInitState(), ListRecorder());
		}
		break;
		default:
			break;
		}
	}

private:
	BaseTurtleState MakeInitState() {
		BaseTurtleState initState;
		initState.up = glm::vec3(0.0f, 1.0f, 0.0f);
		initState.position = glm::vec3(0.0f, 0.0f, 0.0f);
		initState.orientation = glm::vec3(0.0f, 1.0f, 0.0f);
		return initState;
	}
};