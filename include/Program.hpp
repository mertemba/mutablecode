
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
		char status;
		std::vector<Operation> operations;
		
	public:
		void run()
		{
			Interpreter(this);
		}
	};

}

#endif
