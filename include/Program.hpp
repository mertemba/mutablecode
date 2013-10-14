
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
		
		bool getIsRunnable()
		{
			return isRunnable;
		}
		
		void setNotRunnable()
		{
			isRunnable = false;
		}
		
		std::vector<Operation>* getOperations()
		{
			return &operations;
		}
		
		char getCurrent()
		{
			return tape.read();
		}
		
		char getState()
		{
			return state;
		}
		
		void setCurrent(char c)
		{
			if(c != tape.read())
			{
				tape.write(c);
				systemChanged = true;
			}
		}
		
		void setState(char c)
		{
			if(state != c)
			{
				state = c;
				systemChanged = true;
			}
		}
		
		void dump()
		{
			std::cout<<"Program: state="<<(int)state<<std::endl;
			std::cout<<"Tape="<<tape;
		}
		
		bool popSystemChanged()
		{
			bool tmp = systemChanged;
			systemChanged = false;
			return tmp;
		}
		
		void move(Move moveCommand)
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
