
#ifndef _PROGRAM_HPP_
#define _PROGRAM_HPP_

#include <Tape.hpp>
#include <Operation.hpp>
#include <Interpreter.hpp>

#include <vector>

namespace MutableCode
{

	class Program
	{
	private:
		Tape tape;
		char state;
		std::vector<Operation> operations;
		bool isRunnable;
		bool systemChanged;
		
	public:
		Program():tape(), state(0), operations(), isRunnable(true), systemChanged(false)
		{
		}
		
		void run()
		{
			Interpreter(this);
		}
		
		inline bool getIsRunnable()
		{
			return isRunnable;
		}
		
		inline void setNotRunnable()
		{
			isRunnable = false;
		}
		
		inline std::vector<Operation>* getOperations()
		{
			return &operations;
		}
		
		inline char getCurrent()
		{
			return tape.read();
		}
		
		inline char getState()
		{
			return state;
		}
		
		inline void setCurrent(char c)
		{
			if(c != tape.read())
			{
				tape.write(c);
				systemChanged = true;
			}
		}
		
		inline void setState(char c)
		{
			if(state != c)
			{
				state = c;
				systemChanged = true;
			}
		}
		
		friend std::ostream& operator<<(std::ostream& s, const Program& p)
		{
			s<<"Program: state="<<(int)p.state<<"\t";
			s<<"Tape="<<p.tape;
			return s;
		}
		
		inline bool popSystemChanged()
		{
			bool tmp = systemChanged;
			systemChanged = false;
			return tmp;
		}
		
		inline void move(Move moveCommand)
		{
			switch(moveCommand)
			{
				case gotoLeft:
					tape.moveLeft();
					systemChanged = true;
					break;
				case gotoRight:
					tape.moveRight();
					systemChanged = true;
					break;
				default:
					break;
			}
		}
	};

}

#endif
