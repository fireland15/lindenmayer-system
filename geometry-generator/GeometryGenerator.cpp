#include "GeometryGenerator.h"

namespace fli {
	namespace geometry_generator {
		GeometryGenerator::GeometryGenerator(GeometryType geometryType) {
			switch (geometryType) {
			case GeometryType::Points:
				m_interpreter = LStringInterpreter(RecorderType::Point);
				break;
			case GeometryType::Lines:
				m_interpreter = LStringInterpreter(RecorderType::Graph);
				break;
			case GeometryType::Tubes:
				m_interpreter = LStringInterpreter(RecorderType::Graph);
				break;
			case GeometryType::Smooth:
				m_interpreter = LStringInterpreter(RecorderType::Graph);
				break;
			default:
				break;
			}
		}

		std::unique_ptr<Mesh> GeometryGenerator::Generate(const LindenmayerString& lString) {
			return m_interpreter.Interpret(lString);
		}
	}
}