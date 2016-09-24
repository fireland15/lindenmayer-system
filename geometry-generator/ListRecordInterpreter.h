#pragma once

#include <vector>
#include "../glm/glm.hpp"

#include "TurtleState.h"
#include "BaseRecordInterpreter.h"

class ListRecordInterpreter : public BaseRecordInterpreter<std::vector<TurtleState>> {
public:
	virtual std::vector<glm::vec3> Interpret(std::vector<glm::vec3> container) {
		return std::vector<glm::vec3>();
	}

	virtual std::vector<glm::vec3> Interpret(std::vector<int> container) {
		return std::vector<glm::vec3>();
	}
};