#pragma once

#include <memory>
#include <OpenMesh\Core\Mesh\PolyMesh_ArrayKernelT.hh>

#include "../lindenmayer-system/lindenmayer-string.h"

#include "TurtleCommandFactory.h"
#include "TurtleFactory.h"
#include "Turtle.h"
#include "BaseRecorder.h"
#include "RecorderFactory.h"
#include "VertexTurtleCommandSet.h"

typedef OpenMesh::PolyMesh_ArrayKernelT<> Mesh;

class LStringInterpreter {
private:
	TurtleCommandFactory m_commandFactory;
	std::unique_ptr<Turtle> mp_turtle;
	std::shared_ptr<BaseRecorder> mp_recorder;

public:
	LStringInterpreter()
		: m_commandFactory(TurtleCommandFactory(VertexTurtleCommandSet())) {

		mp_recorder = RecorderFactory::MakeRecorder(RecorderType::Empty);

		mp_turtle = TurtleFactory::MakeTurtle(mp_recorder);
	}

	std::unique_ptr<Mesh> Interpret(const LindenmayerString& lString) {
		// Todo: Interpret l string.
	}
};