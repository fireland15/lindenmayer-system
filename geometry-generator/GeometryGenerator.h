#pragma once

#include "../glm/glm.hpp"
#include <OpenMesh\Core\Mesh\PolyMesh_ArrayKernelT.hh>
#include <vector>

#include "../lindenmayer-system/lindenmayer-string.h"
#include "ITurtleCommandSet.h"
#include "TurtleCommandFactory.h"
#include "BaseTurtle.h"
#include "TurtleFactory.h"
#include "VertexTurtleCommandSet.h"

typedef OpenMesh::PolyMesh_ArrayKernelT<> Mesh;

enum GeometryType {
	Points,
	Lines
};

class GeometryGenerator {
private:
	TurtleCommandFactory& m_commandFactory;
	BaseTurtle m_turtle;

public:
	GeometryGenerator(TurtleCommandFactory&& commandFactory, BaseTurtle&& turtle)
		: m_commandFactory(commandFactory), m_turtle(turtle) { }

	Mesh Generate(LindenmayerString& string) {
		for (int i = 0; i < string.Size; i++) {

		}
	}

	static GeometryGenerator MakeGeometryGenerator(GeometryType type) {
		switch (type) {
		case GeometryType::Points: 
		{
			return GeometryGenerator(TurtleCommandFactory(VertexTurtleCommandSet()), TurtleFactory::MakeTurtle(TurtleType::ListRecorded));
		}
		break;
		case GeometryType::Lines:
		{

		}
		break;
		}
	}
};