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

Interpreter::Interpreter(const Program& program, std::istream& input)
	:program(program),input(input)
{
	programPointer = program.getCode().begin();
}

bool Interpreter::doStep()
{
	Program::Operation operation = *programPointer;
	switch(operation)
	{
	case Program::ptrIncrement:
		tape.moveRight();
		break;
	case Program::ptrDecrement:
		tape.moveLeft();
		break;
	case Program::charIncrement:
		tape.increment();
		break;
	case Program::charDecrement:
		tape.decrement();
		break;
	case Program::readChar:
		char c;
		input>>c;
		if(input.good())
		{
			tape.write(c);
		}
		else
		{
			/// end of input, break program
			return false;
		}
		break;
	case Program::writeChar:
		output<<tape.read();
		break;
	case Program::beginWhile:
		if(tape.read() == '0')
		{
			int whileCounter = 1;
			while(++programPointer != program.getCode().end() && whileCounter>0)
			{
				if(*programPointer == Program::beginWhile)
					++whileCounter;
				else if(*programPointer == Program::endWhile)
					--whileCounter;
			}
		}
		break;
	case Program::endWhile:
		if(tape.read() != '0')
		{
			int whileCounter = 1;
			while(--programPointer != program.getCode().begin() && whileCounter>0)
			{
				if(*programPointer == Program::beginWhile)
					--whileCounter;
				else if(*programPointer == Program::endWhile)
					++whileCounter;
			}
		}
		break;
	}
	return true;
}

bool Interpreter::run()
{
	bool stopped = true;
	for(; programPointer != program.getCode().end() && stopped; ++programPointer)
	{
		stopped = doStep();
	}
	return stopped;
}
