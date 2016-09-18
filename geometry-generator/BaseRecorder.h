#pragma once

#include "TurtleState.h"

class BaseRecorder {
private:

public:
	virtual void Record(BaseTurtleState state) = 0;
};