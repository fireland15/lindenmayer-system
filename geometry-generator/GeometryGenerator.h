#pragma once

#include "../glm/glm.hpp"
#include <OpenMesh\Core\Mesh\PolyMesh_ArrayKernelT.hh>
#include <vector>

#include "../lindenmayer-system/lindenmayer-string.h"

#include "LStringInterpreter.h"
#include "Mesh.h"

enum GeometryType {
	Points,
	Lines
};

class GeometryGenerator {
private:
	LStringInterpreter m_interpreter;

public:
	GeometryGenerator();

	std::unique_ptr<Mesh> Generate(const LindenmayerString& lString, GeometryType type);
};