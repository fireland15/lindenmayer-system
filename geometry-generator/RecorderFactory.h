#pragma once

#include <memory>

#include "BaseRecorder.h"
#include "EmptyRecorder.h"

enum class RecorderType {
	Empty
};

class RecorderFactory {
public:
	static std::shared_ptr<BaseRecorder> MakeRecorder(RecorderType type) {
		switch (type) {
		case RecorderType::Empty:
			return std::shared_ptr<BaseRecorder>(new EmptyRecorder);
				break;
		default:
			break;
		}
	}
};