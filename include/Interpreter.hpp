
#ifndef _INTERPRETER_HPP_
#define _INTERPRETER_HPP_

#include <Operation.hpp>

#include <vector>

namespace MutableCode
{
	class Program;

	class Interpreter
	{
	private:
		Program* program;
		std::vector<Operation>* operations;
		
		void doStep();
		
	public:
		Interpreter(Program* prog);
		
		bool isNop(Operation op);
	};

}

#endif
