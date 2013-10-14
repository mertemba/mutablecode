
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
		
	public:
		Program()
		{
			isRunnable = true;
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
			tape.write(c);
		}
		
		void setState(char c)
		{
			state = c;
		}
		
		Tape* getTape()
		{
			return &tape;
		}
		
		void dump()
		{
			std::cout<<"Program: state="<<(int)state<<std::endl;
			std::cout<<"Tape="<<tape;
		}
	};

}

#endif
