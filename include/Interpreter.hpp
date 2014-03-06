/**
 * \file
 * \author jellysheep, ClundXIII, edlervonhuber.
 * \section LICENSE
 * Copyright (c) 2014, jellysheep, ClundXIII, edlervonhuber.
 * All rights reserved.
 * This file is licensed under the "BSD 3-Clause License".
 * Full license text is under the file "LICENSE" provided with this code.
 */

#ifndef _INTERPRETER_HPP_
#define _INTERPRETER_HPP_

#include <sstream>

#include "Program.hpp"
#include "Tape.hpp"

namespace MutableCode
{

	class Interpreter
	{
	private:
		const Program& program;
		const Program::Code& code;
		Tape tape;
		std::istream& input;
		int inputReads;
		std::ostringstream output;
		Program::Code::const_iterator programPointer;
		bool verbose;
		int operationCounter;
		int maximumOperationCount;

		/// returns true if input buffer underrun occurred
		bool doStep();

	public:
		Interpreter(const Program& program, std::istream& input);

		void setVerbose(bool flag)
		{
			verbose = flag;
		}
		/// returns true if input buffer underrun occurred
		bool run();

		int getInputReads()
		{
			return inputReads;
		}
		std::string getOutput()
		{
			return output.str();
		}
		int getOperationCounter()
		{
			return operationCounter;
		}
	};

}

#endif
