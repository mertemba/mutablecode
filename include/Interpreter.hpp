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

#include <Operation.hpp>

#include <vector>

namespace MutableCode
{
	class Program;

	class Interpreter
	{
	private:
		Program* program;
		std::vector<Operation>* operations;
		
		void doStep();
		
		int stepCounter;
		
	public:
		Interpreter(Program* prog);
		
		inline bool isNop(Operation op);
		
		void execute();
	};

}

#endif
