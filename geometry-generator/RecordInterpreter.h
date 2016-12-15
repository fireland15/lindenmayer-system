#pragma once

#include <vector>
#include <memory>
#include <OpenMesh\Core\Mesh\PolyMesh_ArrayKernelT.hh>
#include "../glm/glm.hpp"

#include "BaseRecorder.h"
#include "EmptyRecorder.h"
#include "PointRecorder.h"
#include "GraphRecorder.h"
#include "Mesh.h"
#include "Enums.h"
#include "TileTree.h"

namespace fli {
	namespace geometry_generator {
		typedef Graph<float, glm::vec3>::Node Node;

		class RecordInterpreter {
		private:
			const float m_leafRadius = 0.5f;

		public:
			std::unique_ptr<Mesh> Interpret(std::shared_ptr<BaseRecorder> recorder, GeometryType geometryType);

		private:
			std::unique_ptr<Mesh> InterpretEmptyRecorder(EmptyRecorder* emptyRecorder);

			std::unique_ptr<Mesh> InterpretPointRecorderWithTriangles(PointRecorder* pointRecorder);

			std::unique_ptr<Mesh> InterpretGraphRecorderPoints(GraphRecorder* graphRecorder);

			std::unique_ptr<Mesh> InterpretGraphRecorderTubes(GraphRecorder* graphRecorder);

			std::unique_ptr<Mesh> InterpretGraphRecorderSmooth(GraphRecorder* graphRecorder);

			float DrawChild(Mesh* mesh, std::shared_ptr<Node> current, std::shared_ptr<Node> parent);

			void MakeTubeBetweenPoints(Mesh* mesh, glm::vec3 a, glm::vec3 b, float radius);
		};
	}
}