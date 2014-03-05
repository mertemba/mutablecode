/**
 * \file
 * \author jellysheep, ClundXIII, edlervonhuber.
 * \section LICENSE
 * Copyright (c) 2014, jellysheep, ClundXIII, edlervonhuber.
 * All rights reserved.
 * This file is licensed under the "BSD 3-Clause License".
 * Full license text is under the file "LICENSE" provided with this code.
 */

#include <algorithm>

#include "Mutator.hpp"

using namespace MutableCode;

Mutator::Mutator():random(1, 20)
{
	inputStr = getRandomInput();
	gpOperationWeighting[copy] = 0.2;
	gpOperationWeighting[modify] = 0.4;
	gpOperationWeighting[crossover] = 0.2;
	gpOperationWeighting[create] = 0.2;
	populationSize = 50;
	population.reserve(populationSize);
	for(int i = 0; i<populationSize; i++)
	{
		population.emplace_back(getRandomProgram());
	}
}

std::string Mutator::getRandomCode()
{
	std::stringstream code;
	for(int i = random.get(); i>=0; i--)
	{
		code<<(char)Program::getRandomOperation();
	}
	return code.str();
}

std::string Mutator::getRandomInput()
{
	std::stringstream input;
	for(int i = random.get(); i>=0; i--)
	{
		input<<Char::getRandomChar();
	}
	return input.str();
}

void Mutator::calculateScore(ProgramItem& programItem)
{
	programItem.score = std::log(programItem.output.size()+1)
		-std::log(programItem.program.getCode().size());
}

Mutator::ProgramItem Mutator::getRandomProgram()
{
	BrainfuckProgramLoader programLoader;
	programLoader.loadCode(getRandomCode());
	ProgramItem programItem("Program1", programLoader.getCode());
	return programItem;
}

void Mutator::runProgram(ProgramItem& programItem)
{
	std::istringstream input(inputStr);
	Interpreter interpreter(programItem.program, input);
	programItem.inputBufferUnderrun = interpreter.run();
	programItem.input = inputStr;
	programItem.inputReads = interpreter.getInputReads();
	programItem.output = interpreter.getOutput();
	programItem.operationCounter = interpreter.getOperationCounter();
	calculateScore(programItem);
}

void Mutator::runGeneticProgramming()
{
	for(ProgramItem& programItem : population)
	{
		runProgram(programItem);
	}
	std::sort(population.begin(), population.end(), ProgramItem::compare);
}
