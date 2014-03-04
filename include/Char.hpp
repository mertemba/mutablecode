/**
 * \file
 * \author jellysheep, ClundXIII, edlervonhuber.
 * \section LICENSE
 * Copyright (c) 2013, jellysheep, ClundXIII, edlervonhuber.
 * All rights reserved.
 * This file is licensed under the "BSD 3-Clause License".
 * Full license text is under the file "LICENSE" provided with this code.
 */

#ifndef _CHAR_HPP_
#define _CHAR_HPP_

#include <iostream>
#include <list>
#include <string>

namespace MutableCode
{

	class Char
	{
	public:
		static const std::string charset;

	private:
		int charsetPosition;

	public:
		Char():charsetPosition(0)
		{
		}

		char toChar() const
		{
			return charset[charsetPosition];
		}

		Char& operator++()
		{
			if(charset[++charsetPosition] == '\0')
			{
				charsetPosition = 1;
			}
			return *this;
		}

		Char& operator--()
		{
			if(--charsetPosition < 1)
			{
				charsetPosition = charset.size()-1;
			}
			return *this;
		}

		Char& operator=(char c)
		{
			for(int i = 0; charset[i] != '\0'; i++)
			{
				if(c == charset[i])
				{
					charsetPosition = i;
					return *this;
				}
			}
			charsetPosition = 0;
			return *this;
		}
	};

}

#endif
