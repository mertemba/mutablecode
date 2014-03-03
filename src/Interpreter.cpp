/**
 * \file
 * \author jellysheep, ClundXIII, edlervonhuber.
 * \section LICENSE
 * Copyright (c) 2013, jellysheep, ClundXIII, edlervonhuber.
 * All rights reserved.
 * This file is licensed under the "BSD 3-Clause License".
 * Full license text is under the file "LICENSE" provided with this code.
 */

#include <Interpreter.hpp>
#include <Program.hpp>

using namespace MutableCode;
using namespace std;

Interpreter::Interpreter(const Program& program):program(program)
{
	programPointer = program.getCode().begin();
}

void Interpreter::doStep()
{

}

void Interpreter::run()
{
	for(; programPointer != program.getCode().end(); ++programPointer)
	{
		doStep();
	}
}
