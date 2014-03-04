/**
 * \file
 * \author jellysheep, ClundXIII, edlervonhuber.
 * \section LICENSE
 * Copyright (c) 2014, jellysheep, ClundXIII, edlervonhuber.
 * All rights reserved.
 * This file is licensed under the "BSD 3-Clause License".
 * Full license text is under the file "LICENSE" provided with this code.
 */

#ifndef _MUTATOR_HPP_
#define _MUTATOR_HPP_

#include <string>

#include "Char.hpp"
#include "Interpreter.hpp"
#include "Program.hpp"
#include "ProgramLoader.hpp"

namespace MutableCode
{

	class Mutator
	{
	private:
		void runProgram(const std::string& programName, const std::string& programStr, const std::string& inputStr)
		{
			BrainfuckProgramLoader programLoader;
			programLoader.loadCode(programStr);
			Program program(programName, programLoader);
			std::cout<<program;
			std::istringstream input(inputStr);
			std::cout<<"Input: '"<<input.str()<<"'.\n";
			Interpreter interpreter(program, input);
			bool stopped = interpreter.run();
			std::cout<<(stopped?"Program stopped":"Program had too few input")<<".\n";
			std::cout<<"Output: '"<<interpreter.getOutput()<<"'.\n";
		}

	public:
		void runRandomProgram()
		{
			Random random(1, 20);
			std::stringstream code;
			for(int i = random.get(); i>=0; i--)
			{
				code<<(char)Program::getRandomOperation();
			}
			std::stringstream input;
			for(int i = random.get(); i>=0; i--)
			{
				input<<Char::getRandomChar();
			}
			runProgram("Program1", code.str(), input.str());
		}
	};

}

#endif
