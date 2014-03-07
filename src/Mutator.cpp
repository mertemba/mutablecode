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
#include <cmath>
#include <iomanip>
#include <iostream>

#include "Char.hpp"
#include "Evaluator.hpp"
#include "Interpreter.hpp"
#include "Mutator.hpp"
#include "ProgramLoader.hpp"

using namespace MutableCode;

#define POPULATION_SIZE 30

const int Mutator::populationSize = POPULATION_SIZE;
const int Mutator::maximumCodeSize = 200;

Mutator::Mutator(Evaluator* evaluator):random(1, 30),evaluator(evaluator)
{
	inputStr = getRandomInput();
	gpOperationWeighting[copy] = 3.0/populationSize;
	gpOperationWeighting[modify] = 0.5-gpOperationWeighting[copy];
	gpOperationWeighting[crossover] = 0.1;
	gpOperationWeighting[create] = 0.4;
	populationCounter = 0;
	population.reserve(populationSize);
	for(int i = 0; i<populationSize; i++)
	{
		std::stringstream name;
		name<<"Program"<<(++populationCounter);
		population.emplace_back(getRandomProgram(name.str()));
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

ProgramItem Mutator::getRandomProgram(const std::string& name)
{
	BrainfuckProgramLoader programLoader;
	programLoader.loadCode(getRandomCode());
	ProgramItem programItem(name, programLoader.getCode());
	return programItem;
}

ProgramItem& Mutator::getRandomExistingProgram()
{
	double r = random.getReal();
	int index = r*populationSize;
	return population[index];
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
	evaluator->calculateScore(programItem);
}

void Mutator::nextGeneration(std::vector<ProgramItem>& newPopulation,
	int programItemIndex)
{
	Program::Code code;
	ProgramItem& programItem = newPopulation[programItemIndex];
	do
	{
		double relativePosition = programItemIndex*1.0/populationSize;
		relativePosition -= gpOperationWeighting[copy];
		if(relativePosition < 0)
		{
			/// already copied, nothing to do
			code = programItem.program.getCode();
			goto finish;
		}
		relativePosition -= gpOperationWeighting[modify];
		if(relativePosition < 0)
		{
			ProgramItem& programItem2 = getRandomExistingProgram();
			std::stringstream name;
			name<<"Program"<<(++populationCounter);
			code = programItem2.program.getCode();
			int changed = random.get()+10;
			do
			{
				for(int i = random.get(); i>=0; i--)
				{
					double r = random.getReal();
					code[(int)(code.size()*r)] = Program::getRandomOperation();
					changed--;
				}
				for(int i = random.get(); i>=0 && !code.empty(); i--)
				{
					double r = random.getReal();
					code.erase(code.begin()+(int)(code.size()*r));
					changed--;
				}
				for(int i = random.get(); i>=0; i--)
				{
					double r = random.getReal();
					code.insert(code.begin()+(int)(code.size()*r),
						Program::getRandomOperation());
					changed--;
				}
			}
			while(changed > 0);
			if(code.size()>maximumCodeSize)
				code.erase(code.begin()+maximumCodeSize, code.end());
			programItem = ProgramItem(name.str(), code);
			goto finish;
		}
		relativePosition -= gpOperationWeighting[crossover];
		if(relativePosition < 0)
		{
			ProgramItem& programItem2 = getRandomExistingProgram();
			std::stringstream name;
			name<<"Program"<<(++populationCounter);
			code = programItem.program.getCode();
			const Program::Code& code2 = programItem2.program.getCode();
			int minLength = std::min(code.size(), code2.size());
			double r = random.getReal();
			r = std::min(r, 0.65);
			r = std::max(r, 0.35);
			int mid = (int)(r*minLength);
			code.erase(code.begin()+mid, code.end());
			code.insert(code.begin()+mid, code2.begin()+mid, code2.end());
			if(code.size()>maximumCodeSize)
				code.erase(code.begin()+maximumCodeSize, code.end());
			programItem = ProgramItem(name.str(), code);
			goto finish;
		}
		relativePosition -= gpOperationWeighting[create];
		/// if(relativePosition < 0) should not be necessary
		{
			std::stringstream name;
			name<<"Program"<<(++populationCounter);
			programItem = getRandomProgram(name.str());
			code = programItem.program.getCode();
			goto finish;
		}
	finish:
		std::vector<ProgramItem>::const_iterator it =
			std::find(newPopulation.begin(), newPopulation.end(), code);
		if(it == newPopulation.begin()+programItemIndex)
			it = std::find(newPopulation.begin()+programItemIndex+1, newPopulation.end(), code);
		if(it == newPopulation.end())
			break;
	}
	while(true);
}

void Mutator::runGeneticProgramming(int generations)
{
	for(int i = 0; i<generations; i++)
	{
		std::cout<<"Generation "<<(i+1)<<'|'<<generations<<" ...\r"<<std::flush;
		if(generations > 10 && i%(generations/10) == 0)
			inputStr = getRandomInput();
		#if POPULATION_SIZE>80
		#pragma omp parallel for
		#endif
		for(int j = 0; j<populationSize; j++)
		{
			ProgramItem& programItem = population[j];
			runProgram(programItem);
		}
		std::sort(population.begin(), population.end(), ProgramItem::compare);
		if(i != generations-1)
		{
			std::vector<ProgramItem> newPopulation(population);
			#if POPULATION_SIZE>80
			#pragma omp parallel for
			#endif
			for(int j = 0; j<populationSize; j++)
				nextGeneration(newPopulation, j);
			population.swap(newPopulation);
		}
	}
	std::cout<<"\nBest of population:\n";
	std::cout<<std::setprecision(2)<<std::fixed;
	for(int j = 0; j<populationSize && j<10; j++)
	{
		ProgramItem& programItem = population[j];
		std::cout<<"Score: "<<programItem.score<<"  \t";
		std::cout<<programItem.program<<"\n";
	}
}
