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

#include <vector>

#include "Random.hpp"
#include "Tape.hpp"

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
		Code code;
		std::string name;
		static Random random;

	public:

		Program(const std::string& name, const Code& code):name(name),code(code)
		{
		}

		const Code& getCode() const
		{
			return code;
		}

		static Operation getRandomOperation()
		{
			int operation = random.get();
			switch(operation)
			{
			case 0:
				return ptrIncrement;
			case 1:
				return ptrDecrement;
			case 2:
				return charIncrement;
			case 3:
				return charDecrement;
			case 4:
				return writeChar;
			case 5:
				return readChar;
			case 6:
				return beginWhile;
			case 7:
				return endWhile;
			default:
				return charIncrement;
			}
		}

		friend std::ostream& operator<<(std::ostream& s, const Program& p)
		{
			s<<"Program '"<<p.name<<"': '";
			for(Operation op : p.code)
			{
				s<<(char)op;
			}
			s<<"'";
			return s;
		}
	};

}

#endif
