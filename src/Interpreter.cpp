
#include <Interpreter.hpp>
#include <Program.hpp>

using namespace MutableCode;
using namespace std;

Interpreter::Interpreter(Program* prog)
{
	program = prog;
	
	if (program != NULL)
	{
		operations = program->getOperations();
		this->execute();
	}
	else
	{
		cout << "Empty program!" << endl;
	}
}

void Interpreter::doStep()
{
	bool currentMatch = false;
	bool stateMatch = false;
	bool anyMatch = false;
	Operation op;
	for(std::vector<Operation>::iterator it = operations->begin(); it != operations->end(); it++)
	{
		op = *it;
		if(op.currentCondition == 0 || op.currentCondition == program->getCurrent())
		{
			currentMatch = true;
		}
		if(op.stateCondition == 0 || op.stateCondition == program->getState())
		{
			stateMatch = true;
		}
		anyMatch = currentMatch || stateMatch;
		if(anyMatch)
		{
			if(op.currentWrite != 0)
			{
				program->setCurrent(op.currentWrite);
			}
			if(op.stateWrite != 0)
			{
				program->setState(op.stateWrite);
			}
			break;
		}
	}
	if(!anyMatch || isNop(op))
	{
		program->setNotRunnable();
	}
}

bool Interpreter::isNop(Operation op)
{
	return (op.moveCommand == stay &&(op.currentWrite == 0 || op.currentWrite == program->getCurrent())
		&& (op.stateWrite == 0 || op.stateWrite == program->getState()));
}

void Interpreter::execute()
{
	while(program->getIsRunnable())
	{
		doStep();
	}
}
