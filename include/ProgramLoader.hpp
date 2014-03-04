/**
 * \file
 * \author jellysheep, ClundXIII, edlervonhuber.
 * \section LICENSE
 * Copyright (c) 2013, jellysheep, ClundXIII, edlervonhuber.
 * All rights reserved.
 * This file is licensed under the "BSD 3-Clause License".
 * Full license text is under the file "LICENSE" provided with this code.
 */

#ifndef _PROGRAMLOADER_HPP_
#define _PROGRAMLOADER_HPP_

#include <sstream>

#include "Program.hpp"

namespace MutableCode
{

	class ProgramLoader
	{
	public:
		virtual ~ProgramLoader(){}
		virtual Program::Code getCode() const = 0;
	};

	class BrainfuckProgramLoader : public ProgramLoader
	{
	private:
		Program::Code code;

	public:
		BrainfuckProgramLoader(std::istream& stream)
		{
			char c;
			stream>>c;
			for(; stream.good(); stream>>c)
			{
				code.push_back((Program::Operation)c);
			}
		}

		virtual Program::Code getCode() const
		{
			return code;
		}
	};

}

#endif
