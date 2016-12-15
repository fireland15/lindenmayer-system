#include "LStringInterpreter.h"

namespace fli {
	namespace geometry_generator {
		LStringInterpreter::LStringInterpreter()
			: m_commandFactory(TurtleCommandFactory(std::unique_ptr<ITurtleCommandSet>(new VertexTurtleCommandSet()))) {
			mp_recorder = RecorderFactory::MakeRecorder(RecorderType::Point);
			mp_turtle = TurtleFactory::MakeTurtle(mp_recorder);
		}

		LStringInterpreter::LStringInterpreter(RecorderType recorderType)
			: m_commandFactory(TurtleCommandFactory(std::unique_ptr<ITurtleCommandSet>(new VertexTurtleCommandSet()))) {
			mp_recorder = RecorderFactory::MakeRecorder(recorderType);
			mp_turtle = TurtleFactory::MakeTurtle(mp_recorder);
		}

		LStringInterpreter::LStringInterpreter(GeometryType geometryType)
			: m_commandFactory(TurtleCommandFactory(std::unique_ptr<ITurtleCommandSet>(new VertexTurtleCommandSet()))) {
			m_geometryType = geometryType;

			switch (geometryType) {
			case GeometryType::Points:
				mp_recorder = RecorderFactory::MakeRecorder(RecorderType::Point);
				break;
			case GeometryType::Tubes:
			case GeometryType::Smooth:
				mp_recorder = RecorderFactory::MakeRecorder(RecorderType::Graph);
				break;
			default:
				mp_recorder = RecorderFactory::MakeRecorder(RecorderType::Empty);
				break;
			}
			mp_turtle = TurtleFactory::MakeTurtle(mp_recorder);
		}

		std::unique_ptr<Mesh> LStringInterpreter::Interpret(const LindenmayerString& lString) {
			LindenmayerString::ConstIterator it = lString.Begin();
			while (!it.AtEnd()) {
				TurtleCommand command = m_commandFactory.BuildCommand(*it);
				command.Execute(*mp_turtle);
				it.operator++();
			}

			RecordInterpreter interpreter;
			std::unique_ptr<Mesh> mesh = interpreter.Interpret(mp_recorder, m_geometryType);
			return mesh;
		}
	}
}