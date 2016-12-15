#pragma once

#include <memory>

#include "TurtleCommand.h"
#include "../lindenmayer-system/lindenmayer-symbol.h"
#include "ITurtleCommandSet.h"

namespace fli {
	namespace geometry_generator {
		class TurtleCommandFactory {
		private:
			std::unique_ptr<ITurtleCommandSet> m_commandSet;

		public:
			TurtleCommandFactory(std::unique_ptr<ITurtleCommandSet> commandSet);

			TurtleCommand BuildCommand(LindenmayerSymbol symbol);
		};
	}
}