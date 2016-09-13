#pragma once

#include <vector>
#include "../glm/glm.hpp"

#include "BaseRecordInterpreter.h"

template <typename TState>
class ListRecordInterpreter : public BaseRecordInterpreter<std::vector<TState>> {
public:
	virtual std::vector<glm::vec3> Interpret(std::vector<glm::vec3> container) {
		return std::vector<glm::vec3>();
	}

	virtual std::vector<glm::vec3> Interpret(std::vector<int> container) {
		return std::vector<glm::vec3>();
	}
};