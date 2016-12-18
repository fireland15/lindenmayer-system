#pragma once

#include "../glm/glm.hpp"
#include <OpenMesh\Core\Mesh\PolyMesh_ArrayKernelT.hh>
#include <vector>

#include "../lindenmayer-system/lindenmayer-string.h"

#include "LStringInterpreter.h"
#include "Mesh.h"
#include "Enums.h"

namespace fli {
	namespace geometry_generator {
		class GeometryGenerator {
		private:
			LStringInterpreter m_interpreter;
			GeometryType m_geometryType;

		public:
			GeometryGenerator(GeometryType geometryType);

			std::unique_ptr<Mesh> Generate(const LindenmayerString& lString);

			void set_InterpreterRules(TurtleCommandSetType commandSetType);
		};
	}
}