#pragma once

template <typename TState>
class BaseRecorder {
private:

public:
	virtual void Record(TState state) = 0;
};