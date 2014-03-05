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

#include <cmath>
#include <string>
#include <vector>

#include "Char.hpp"
#include "Interpreter.hpp"
#include "Program.hpp"
#include "ProgramLoader.hpp"

namespace MutableCode
{

	class Mutator
	{
	public:
		/// inputs and results of a tested program
		struct ProgramItem
		{
			Program program;
			std::string input;
			int inputReads;
			std::string output;
			int operationCounter;
			bool inputBufferUnderrun;
			double score;

			ProgramItem(const std::string& name, const Program::Code& code)
				:program(name, code),inputReads(0),operationCounter(0),
				inputBufferUnderrun(false),score(0){}

			static bool compare(const ProgramItem& first, const ProgramItem& second)
			{
				return first.score > second.score;
			}
		};

	private:
		Random random;
		std::string inputStr;
		static const int populationSize;
		std::vector<ProgramItem> population;
		int populationCounter;
		static const int maximumCodeSize;

		/// Genetic Programming options
		enum GPOperation
		{
			copy,
			modify,
			crossover,
			create
		};
		double gpOperationWeighting[4];

		std::string getRandomCode();
		std::string getRandomInput();

		ProgramItem getRandomProgram(const std::string& name);
		ProgramItem& getRandomExistingProgram();

		static void calculateScore(ProgramItem& programItem);

		void runProgram(ProgramItem& programItem);

		void nextGeneration(std::vector<ProgramItem>& newPopulation,
			int programItemIndex);

	public:
		Mutator();

		void runGeneticProgramming(int generations);

		ProgramItem getBestProgramItem()
		{
			return population.front();
		}

		std::string getInput()
		{
			return inputStr;
		}
	};

}

#endif
