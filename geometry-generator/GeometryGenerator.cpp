#include "GeometryGenerator.h"

GeometryGenerator::GeometryGenerator() { }

std::unique_ptr<Mesh> GeometryGenerator::Generate(const LindenmayerString& lString, GeometryType type) {
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