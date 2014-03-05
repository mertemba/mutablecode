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

#include "Mutator.hpp"

using namespace MutableCode;

int main(int argc, char *argv[])
{
	Mutator mutator;
	mutator.runGeneticProgramming();
	Mutator::ProgramItem programItem = mutator.getBestProgramItem();
	std::cout<<"Best program item: "<<programItem.program<<"\n";
	std::cout<<"Program input: '"<<mutator.getInput()<<"'\n";
	std::cout<<"Program output: '"<<programItem.output<<"'\n";
	std::cout<<"Program item score: "<<programItem.score<<"\n";
	return 0;
}
