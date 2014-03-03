/**
 * \file
 * \author jellysheep, ClundXIII, edlervonhuber.
 * \section LICENSE
 * Copyright (c) 2013, jellysheep, ClundXIII, edlervonhuber.
 * All rights reserved.
 * This file is licensed under the "BSD 3-Clause License".
 * Full license text is under the file "LICENSE" provided with this code.
 */

#ifndef _INTERPRETER_HPP_
#define _INTERPRETER_HPP_

#include "Program.hpp"

#include <list>
#include <sstream>

namespace MutableCode
{

	class Interpreter
	{
	private:
		const Program& program;
		Tape tape;
		std::istream& input;
		std::ostringstream output;
		Program::Code::const_iterator programPointer;

		bool doStep();

	public:
		Interpreter(const Program& program, std::istream& input);

		bool run();

		std::string getOutput()
		{
			return output.str();
		}
	};

}

#endif
