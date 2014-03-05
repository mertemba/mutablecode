/**
 * \file
 * \author jellysheep, ClundXIII, edlervonhuber.
 * \section LICENSE
 * Copyright (c) 2014, jellysheep, ClundXIII, edlervonhuber.
 * All rights reserved.
 * This file is licensed under the "BSD 3-Clause License".
 * Full license text is under the file "LICENSE" provided with this code.
 */

#include "Interpreter.hpp"
#include "Program.hpp"

using namespace MutableCode;

Interpreter::Interpreter(const Program& program, std::istream& input)
	:program(program),code(program.getCode()),input(input)
{
	inputReads = 0;
	programPointer = code.begin();
	verbose = false;
	operationCounter = 0;
	maximumOperationCount = 1000;
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
			++inputReads;
		}
		else
		{
			/// end of input, break program
			return true;
		}
		break;
	case Program::writeChar:
		output<<tape.read();
		break;
	case Program::beginWhile:
		if(tape.read() == '0')
		{
			int whileCounter = 1;
			while((++programPointer != code.end()) && whileCounter>0)
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
			while(programPointer-- != code.begin() && whileCounter>0)
			{
				if(*programPointer == Program::beginWhile)
					--whileCounter;
				else if(*programPointer == Program::endWhile)
					++whileCounter;
			}
		}
		break;
	}
	return false;
}

bool Interpreter::run()
{
	bool inputBufferUnderrun = false;
	do
	{
		char operation = (char)*programPointer;
		inputBufferUnderrun = doStep();
		if(verbose)
		{
			std::cout<<"Interpreter: Operation: "<<operation<<" ";
			std::cout<<"Result: "<<tape<<"\n";
		}
	}
	while((programPointer != code.end()) && (++programPointer != code.end())
		&& !inputBufferUnderrun && (++operationCounter<maximumOperationCount));
	return inputBufferUnderrun;
}
