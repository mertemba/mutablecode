
#ifndef _TAPE_HPP_
#define _TAPE_HPP_

#include <list>
#include <iostream>
#include <algorithm>

namespace MutableCode
{

	class Tape
	{
	private:
		std::list<char> data;
		std::list<char>::iterator currentElement;
		
	public:
		Tape()
		{
			data.push_front(0);
			currentElement = data.begin();
		}
		
		void moveRight()
		{
			if(currentElement != --data.end())
				currentElement++;
			else
			{
				data.push_back(0);
				currentElement = --data.end();
			}
		}
		
		void moveLeft()
		{
			if(currentElement != data.begin())
				currentElement--;
			else
			{
				data.push_front(0);
				currentElement = data.begin();
			}
		}
		
		void write(const char c)
		{
			*currentElement = c;
		}
		
		char read() const
		{
			return *currentElement;
		}
		
		void clear()
		{
			data.clear();
			data.push_front(0);
			currentElement = data.begin();
		}
		
		friend std::ostream& operator<<(std::ostream& s, const Tape& t)
		{
			s<<"<Tape:"<<std::endl;
			for(auto it = t.data.begin(); it!=t.data.end(); it++){
				s<<"  "<<*it<<std::endl;
			}
			s<<">"<<std::endl;
			return s;
		}
		
		friend std::istream& operator>>(std::istream& s, Tape& t)
		{
			char c;
			s>>c;
			t.write(c);
			
			return s;
		}
	};

}

#endif
