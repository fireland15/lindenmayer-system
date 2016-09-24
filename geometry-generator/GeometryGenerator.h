#pragma once

#include "../glm/glm.hpp"
#include <OpenMesh\Core\Mesh\PolyMesh_ArrayKernelT.hh>
#include <vector>

#include "../lindenmayer-system/lindenmayer-string.h"

#include "LStringInterpreter.h"

typedef OpenMesh::PolyMesh_ArrayKernelT<> Mesh;

enum GeometryType {
	Points,
	Lines
};

class GeometryGenerator {
private:
	LStringInterpreter m_interpreter;

public:
	GeometryGenerator() {

	}

	std::unique_ptr<Mesh> Generate(const LindenmayerString& lString, GeometryType type) {
		//Todo: Pass the expected geometry type into the interpreter so it produces the desired results.
		switch (type) {
		case GeometryType::Points:
			return m_interpreter.Interpret(lString);
			break;
		case GeometryType::Lines:
			return m_interpreter.Interpret(lString);
			break;
		default:
			break;
		}
	}
};