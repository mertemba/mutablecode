/**
 * \file
 * \author jellysheep, ClundXIII, edlervonhuber.
 * \section LICENSE
 * Copyright (c) 2014, jellysheep, ClundXIII, edlervonhuber.
 * All rights reserved.
 * This file is licensed under the "BSD 3-Clause License".
 * Full license text is under the file "LICENSE" provided with this code.
 */

#ifndef _PROGRAM_HPP_
#define _PROGRAM_HPP_

#include <iostream>
#include <string>
#include <vector>

#include "Random.hpp"

namespace MutableCode
{
	class ProgramLoader;

	class Program
	{
	public:
		enum Operation
		{
			ptrIncrement = '>',
			ptrDecrement = '<',
			charIncrement = '+',
			charDecrement = '-',
			writeChar = '.',
			readChar = ',',
			beginWhile = '[',
			endWhile = ']'
		};
		typedef std::vector<Operation> Code;

	private:
		std::string name;
		Code code;
		static Random random;

	public:
		Program(const std::string& name, const Code& code):name(name),code(code)
		{
		}

		std::string getName() const
		{
			return name;
		}
		const Code& getCode() const
		{
			return code;
		}

		static Operation getRandomOperation();

		friend std::ostream& operator<<(std::ostream& s, const Program& p);

	};

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

		bool operator==(const Program::Code& code) const;

	};

}

#endif
