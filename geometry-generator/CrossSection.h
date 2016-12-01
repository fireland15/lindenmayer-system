#pragma once

#include "Mesh.h"

namespace fli {
	namespace geometry_generator {
		struct CrossSection {
			Mesh::VertexHandle vertices[4];
		};
	}
}