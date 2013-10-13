
#ifndef _TAPE_HPP_
#define _TAPE_HPP_

#include <list>
#include <iostream>
#include <algorithm>

namespace MutableCode
{

	typedef std::list<char> CharList;
	
	class Tape
	{
	private:
		CharList data;
		CharList::iterator current;
		
	public:
		Tape()
		{
			data.push_front(0);
			current = data.begin();
		}
		
		void moveRight()
		{
			if(current != --data.end())
				current++;
			else
			{
				data.push_back(0);
				current = --data.end();
			}
		}
		
		void moveLeft()
		{
			if(current != data.begin())
				current--;
			else
			{
				data.push_front(0);
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
			data.push_front(0);
			current = data.begin();
		}
		
		friend std::ostream& operator<<(std::ostream& s, const Tape& t)
		{
			s<<"<Tape:"<<std::endl;
			for(CharList::const_iterator it = t.data.begin(); it!=t.data.end(); it++){
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
