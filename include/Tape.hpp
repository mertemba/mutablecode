/**
 * \file
 * \author jellysheep, ClundXIII, edlervonhuber.
 * \section LICENSE
 * Copyright (c) 2013, jellysheep, ClundXIII, edlervonhuber.
 * All rights reserved.
 * This file is licensed under the "BSD 3-Clause License".
 * Full license text is under the file "LICENSE" provided with this code.
 */

#ifndef _TAPE_HPP_
#define _TAPE_HPP_

#include <iostream>
#include <list>
#include <string>

#include "Char.hpp"

namespace MutableCode
{

	class Tape
	{
	private:
		std::list<Char> data;
		/// the "current" iterator defines the current position on the tape
		/// "*current" defines the current char
		std::list<Char>::iterator current;

	public:
		Tape()
		{
			data.emplace_back();
			current = data.begin();
		}

		void moveRight()
		{
			if(current != --data.end())
				++current;
			else
			{
				data.emplace_back();
				current = --data.end();
			}
		}

		void moveLeft()
		{
			if(current != data.begin())
				--current;
			else
			{
				data.emplace_back();
				current = data.begin();
			}
		}

		void increment()
		{
			++(*current);
		}

		void decrement()
		{
			--(*current);
		}

		void write(const char c)
		{
			*current = c;
		}

		char read() const
		{
			return current->toChar();
		}

		void clear()
		{
			data.clear();
			data.emplace_back();
			current = data.begin();
		}

		friend std::ostream& operator<<(std::ostream& s, const Tape& t)
		{
			s<<"<Tape:";
			for(std::list<Char>::const_iterator it = t.data.begin(); it!=t.data.end(); it++)
			{
				s<<" ";
				/// mark current Char with *c*
				if(it == t.current)
					s<<"*";
				s<<it->toChar();
				if(it == t.current)
					s<<"*";
			}
			s<<">";
			return s;
		}
	};

}

#endif
