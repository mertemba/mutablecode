/**
 * \file
 * \author jellysheep, ClundXIII, edlervonhuber.
 * \section LICENSE
 * Copyright (c) 2013, jellysheep, ClundXIII, edlervonhuber.
 * All rights reserved.
 * This file is licensed under the "BSD 3-Clause License".
 * Full license text is under the file "LICENSE" provided with this code.
 */

#ifndef _PROGRAM_HPP_
#define _PROGRAM_HPP_

#include <vector>

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

	public:
		Program(const std::string& name, const Code& code):name(name),code(code)
		{
		}

		Program(const std::string& name, const ProgramLoader& programLoader);

		const Code& getCode() const
		{
			return code;
		}

		friend std::ostream& operator<<(std::ostream& s, const Program& p)
		{
			s<<"Program '"<<p.name<<"': '";
			for(Operation op : p.code)
			{
				s<<(char)op;
			}
			s<<"'\n";
			return s;
		}
	};

}

#endif
