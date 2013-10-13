
#ifndef _INTERPRETER_HPP_
#define _INTERPRETER_HPP_

namespace MutableCode
{
	class Program;

	class Interpreter
	{
	private:
		Program* program;
		
	public:
		Interpreter(Program* prog);
	};

}

#endif
