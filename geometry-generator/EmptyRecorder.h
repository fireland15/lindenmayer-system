#pragma once

#include "TurtleState.h"
#include "BaseRecorder.h"

class EmptyRecorder : public BaseRecorder {
private:

public:
	virtual void Record(TurtleState state);
};