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
				:program(name, code),inputReads(0),score(0),
				operationCounter(0),inputBufferUnderrun(false){}
		};

	private:
		Random random;
		std::string inputStr;
		int populationSize;

		/// Genetic Programming options
		enum GPOperation
		{
			copy,
			modify,
			crossover,
			create
		};
		double gpOperationWeighting[4];

		std::string getRandomCode()
		{
			std::stringstream code;
			for(int i = random.get(); i>=0; i--)
			{
				code<<(char)Program::getRandomOperation();
			}
			return code.str();
		}

		std::string getRandomInput()
		{
			std::stringstream input;
			for(int i = random.get(); i>=0; i--)
			{
				input<<Char::getRandomChar();
			}
			return input.str();
		}

		static void calculateScore(ProgramItem& programItem)
		{
			programItem.score = std::log(programItem.output.size()+1)
				-std::log(programItem.program.getCode().size());
		}

		void runProgram(ProgramItem& programItem)
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

	public:
		Mutator():random(1, 20)
		{
			inputStr = getRandomInput();
			populationSize = 50;
			gpOperationWeighting[copy] = 0.2;
			gpOperationWeighting[modify] = 0.4;
			gpOperationWeighting[crossover] = 0.2;
			gpOperationWeighting[create] = 0.2;
		}

		ProgramItem runRandomProgram()
		{
			BrainfuckProgramLoader programLoader;
			programLoader.loadCode(getRandomCode());
			ProgramItem programItem("Program1", programLoader.getCode());
			runProgram(programItem);
			return programItem;
		}

		std::string getInput()
		{
			return inputStr;
		}
	};

}

#endif
