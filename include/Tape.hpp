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

namespace MutableCode
{
	
	class Tape
	{
	public:
		constexpr static const char* Charset = "_ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+-";
		constexpr static char defaultTapeValue = Charset[0];
	
	private:
		std::list<char> data;
		std::list<char>::iterator current;
		
	public:
		Tape()
		{
			data.push_front(defaultTapeValue);
			current = data.begin();
		}
		
		void moveRight()
		{
			if(current != --data.end())
				++current;
			else
			{
				data.push_back(defaultTapeValue);
				current = --data.end();
			}
		}
		
		void moveLeft()
		{
			if(current != data.begin())
				--current;
			else
			{
				data.push_front(defaultTapeValue);
				current = data.begin();
			}
		}
		
		void write(const char c)
		{
			*current = c;
		}
		
		char read() const
		{
			return *current;
		}
		
		void clear()
		{
			data.clear();
			data.push_front(defaultTapeValue);
			current = data.begin();
		}
		
		friend std::ostream& operator<<(std::ostream& s, const Tape& t)
		{
			s<<"<Tape:";
			for(std::list<char>::const_iterator it = t.data.begin(); it!=t.data.end(); it++)
			{
				s<<" ";
				if(it == t.current)
					s<<"*";
				s<<(int)*it;
				if(it == t.current)
					s<<"*";
			}
			s<<">";
			return s;
		}
		
		friend std::istream& operator>>(std::istream& s, Tape& t)
		{
			int c;
			s>>c;
			t.write((char)c);
			
			return s;
		}
	};

}

#endif
