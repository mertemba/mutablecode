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

namespace MutableCode
{

	class Interpreter
	{
	private:
		const Program& program;
		Program::Code::const_iterator programPointer;

		void doStep();

	public:
		Interpreter(const Program& program);

		void run();
	};

}

#endif
