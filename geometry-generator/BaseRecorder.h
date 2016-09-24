#pragma once

#include "TurtleState.h"

class BaseRecorder {
private:

public:
	virtual void Record(TurtleState state) = 0;
};