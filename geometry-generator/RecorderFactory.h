#pragma once

#include <memory>

#include "BaseRecorder.h"
#include "EmptyRecorder.h"
#include "PointRecorder.h"
#include "GraphRecorder.h"

enum class RecorderType {
	Empty,
	Point,
	Graph
};

class RecorderFactory {
public:
	static std::shared_ptr<BaseRecorder> MakeRecorder(RecorderType type) {
		switch (type) {
		case RecorderType::Empty:
			return std::shared_ptr<BaseRecorder>(new EmptyRecorder);
		case RecorderType::Point:
			return std::shared_ptr<BaseRecorder>(new PointRecorder);
		case RecorderType::Graph:
			return std::shared_ptr<BaseRecorder>(new GraphRecorder);
		default:
			break;
		}
	}
};