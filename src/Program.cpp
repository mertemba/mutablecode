/**
 * \file
 * \author jellysheep, ClundXIII, edlervonhuber.
 * \section LICENSE
 * Copyright (c) 2014, jellysheep, ClundXIII, edlervonhuber.
 * All rights reserved.
 * This file is licensed under the "BSD 3-Clause License".
 * Full license text is under the file "LICENSE" provided with this code.
 */

#include "Program.hpp"

using namespace MutableCode;

Random Program::random(0, 7);

Program::Operation Program::getRandomOperation()
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

namespace MutableCode
{
	std::ostream& operator<<(std::ostream& s, const Program& p)
	{
		s<<"Program '"<<p.name<<"': '";
		for(Program::Operation op : p.code)
		{
			s<<(char)op;
		}
		s<<"'";
		return s;
	}
}
