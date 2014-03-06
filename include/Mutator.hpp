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
#include <vector>

#include "Program.hpp"

namespace MutableCode
{
	class Evaluator;

	class Mutator
	{
	private:
		Random random;
		std::string inputStr;
		static const int populationSize;
		std::vector<ProgramItem> population;
		int populationCounter;
		static const int maximumCodeSize;

		Evaluator* evaluator;

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

		void runProgram(ProgramItem& programItem);

		void nextGeneration(std::vector<ProgramItem>& newPopulation,
			int programItemIndex);

	public:
		Mutator(Evaluator* evaluator);

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
