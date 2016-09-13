#pragma once

#include <vector>
#include "../glm/glm.hpp"

template <typename TContainer>
class BaseRecordInterpreter { 
public:
	virtual std::vector<glm::vec3> Interpret(TContainer container) = 0;
};