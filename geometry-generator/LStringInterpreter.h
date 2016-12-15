#pragma once

//#define _USE_MATH_DEFINES

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
#include "Enums.h"

namespace fli {
	namespace geometry_generator {
		class LStringInterpreter {
		private:
			TurtleCommandFactory m_commandFactory;
			std::unique_ptr<Turtle> mp_turtle;
			std::shared_ptr<BaseRecorder> mp_recorder;

			GeometryType m_geometryType;

		public:
			LStringInterpreter();

			LStringInterpreter(RecorderType recorderType);

			LStringInterpreter(GeometryType geometryType);

			std::unique_ptr<Mesh> Interpret(const LindenmayerString& lString);
		};
	}
}