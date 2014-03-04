/**
 * \file
 * \author jellysheep, ClundXIII, edlervonhuber.
 * \section LICENSE
 * Copyright (c) 2013, jellysheep, ClundXIII, edlervonhuber.
 * All rights reserved.
 * This file is licensed under the "BSD 3-Clause License".
 * Full license text is under the file "LICENSE" provided with this code.
 */

#include <iostream>

#include "Program.hpp"
#include "ProgramLoader.hpp"
#include "Interpreter.hpp"

using namespace MutableCode;

int main()
{
	std::istringstream code("[,.]");
	Program program("Program1", BrainfuckProgramLoader(code));
	std::cout<<program;
	std::istringstream input("Hallo");
	std::cout<<"Input: '"<<input.str()<<"'.\n";
	Interpreter interpreter(program, input);
	bool stopped = interpreter.run();
	std::cout<<(stopped?"Program stopped":"Program had too few input")<<".\n";
	std::cout<<"Output: '"<<interpreter.getOutput()<<"'.\n";
	return 0;
}
