/**
 * \file
 * \author jellysheep, ClundXIII, edlervonhuber.
 * \section LICENSE
 * Copyright (c) 2014, jellysheep, ClundXIII, edlervonhuber.
 * All rights reserved.
 * This file is licensed under the "BSD 3-Clause License".
 * Full license text is under the file "LICENSE" provided with this code.
 */

#include <iostream>

#include "Program.hpp"
#include "ProgramLoader.hpp"
#include "Interpreter.hpp"

using namespace MutableCode;

int main(int argc, char *argv[])
{
	BrainfuckProgramLoader programLoader;
	if(argc > 1)
		programLoader.loadCode(argv[1]);
	else
		programLoader.loadCode(std::cin);
	Program program("Program1", programLoader);
	std::cout<<program;
	std::istringstream input("Input");
	std::cout<<"Input: '"<<input.str()<<"'.\n";
	Interpreter interpreter(program, input);
	interpreter.setVerbose(true);
	bool stopped = interpreter.run();
	std::cout<<(stopped?"Program stopped":"Program had too few input")<<".\n";
	std::cout<<"Output: '"<<interpreter.getOutput()<<"'.\n";
	return 0;
}
