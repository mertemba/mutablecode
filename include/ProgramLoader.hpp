/**
 * \file
 * \author jellysheep, ClundXIII, edlervonhuber.
 * \section LICENSE
 * Copyright (c) 2014, jellysheep, ClundXIII, edlervonhuber.
 * All rights reserved.
 * This file is licensed under the "BSD 3-Clause License".
 * Full license text is under the file "LICENSE" provided with this code.
 */

#ifndef _PROGRAMLOADER_HPP_
#define _PROGRAMLOADER_HPP_

#include <sstream>
#include <string>

#include "Program.hpp"

namespace MutableCode
{

	class ProgramLoader
	{
	protected:
		Program::Code code;

	public:
		virtual ~ProgramLoader(){}
		virtual void loadCode(std::istream& stream) = 0;
		virtual void loadCode(const std::string& string) = 0;

		Program::Code getCode() const
		{
			return code;
		}
	};

	class BrainfuckProgramLoader : public ProgramLoader
	{
	public:
		virtual void loadCode(std::istream& stream) override
		{
			char c;
			stream>>c;
			for(; stream.good(); stream>>c)
			{
				code.push_back((Program::Operation)c);
			}
		}
		virtual void loadCode(const std::string& string) override
		{
			std::istringstream stream(string);
			this->loadCode(stream);
		}
	};

}

#endif
