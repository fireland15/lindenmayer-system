#pragma once

#include "../glm/glm.hpp"
#include <vector>

#include "../lindenmayer-system/lindenmayer-string.h"
#include "ITurtleCommandSet.h"
#include "TurtleCommandFactory.h"
#include "BaseTurtle.h"
#include "TurtleFactory.h"
#include "VertexTurtleCommandSet.h"

enum GeometryType {
	Points,
	Lines
};

class GeometryGenerator {
private:
	TurtleCommandFactory& m_commandFactory;
	BaseTurtle m_turtle;

public:
	GeometryGenerator(TurtleCommandFactory& commandFactory, BaseTurtle turtle)
		: m_commandFactory(commandFactory), m_turtle(turtle) { }

	std::vector<glm::vec3> Generate(LindenmayerString& string) {
		for (int i = 0; i < string.Size; i++) {

		}
	}

	static GeometryGenerator MakeGeometryGenerator(GeometryType type) {
		TurtleFactory turtleFactory;

		switch (type) {
		case GeometryType::Points:
		{
			return GeometryGenerator(TurtleCommandFactory(VertexTurtleCommandSet()), turtleFactory.MakeTurtle(TurtleType::ListRecorded));
		}
		break;
		case GeometryType::Lines:
		{

		}
		break;
		}
	}
};