#pragma once

#define _USE_MATH_DEFINES

#include <memory>
#include <OpenMesh\Core\Mesh\PolyMesh_ArrayKernelT.hh>

#include "../lindenmayer-system/lindenmayer-string.h"
#include "../lindenmayer-system/lindenmayer-symbol.h"

#include "TurtleCommandFactory.h"
#include "TurtleFactory.h"
#include "Turtle.h"
#include "ITurtleCommandSet.h"
#include "BaseRecorder.h"
#include "RecorderFactory.h"
#include "VertexTurtleCommandSet.h"
#include "RecordInterpreter.h"
#include "Mesh.h"

class LStringInterpreter {
private:
	TurtleCommandFactory m_commandFactory;
	std::unique_ptr<Turtle> mp_turtle;
	std::shared_ptr<BaseRecorder> mp_recorder;

public:
	LStringInterpreter()
		: m_commandFactory(TurtleCommandFactory(std::unique_ptr<ITurtleCommandSet>(new VertexTurtleCommandSet()))) {
		mp_recorder = RecorderFactory::MakeRecorder(RecorderType::Point);
		mp_turtle = TurtleFactory::MakeTurtle(mp_recorder);
	}

	LStringInterpreter(RecorderType recorderType)
		: m_commandFactory(TurtleCommandFactory(std::unique_ptr<ITurtleCommandSet>(new VertexTurtleCommandSet()))) {
		mp_recorder = RecorderFactory::MakeRecorder(recorderType);
		mp_turtle = TurtleFactory::MakeTurtle(mp_recorder);
	}

	std::unique_ptr<Mesh> Interpret(const LindenmayerString& lString) {
		// Todo: Interpret l string.
		LindenmayerString::ConstIterator it = lString.Begin();
		while (!it.AtEnd()) {
			TurtleCommand command = m_commandFactory.BuildCommand(*it);
			command.Execute(*mp_turtle);
			it.operator++();
		}

		RecordInterpreter interpreter;
		std::unique_ptr<Mesh> mesh = interpreter.Interpret(mp_recorder);
		return mesh;
	}
};