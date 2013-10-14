
#include <Interpreter.hpp>
#include <Program.hpp>

using namespace MutableCode;
using namespace std;

Interpreter::Interpreter(Program* prog)
{
	program = prog;
	operations = NULL;
	
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
	cout<<*program<<"\t";
	bool allMatch = false;
	Operation op;
	for(std::vector<Operation>::iterator it = operations->begin(); it != operations->end(); it++)
	{
		bool currentMatch = false;
		bool stateMatch = false;
		op = *it;
		if(op.currentCondition == 0 || op.currentCondition == program->getCurrent())
		{
			currentMatch = true;
		}
		if(op.stateCondition == 0 || op.stateCondition == program->getState())
		{
			stateMatch = true;
		}
		allMatch = currentMatch && stateMatch && !isNop(op);
		if(allMatch)
		{
			cout<<op<<"\tmatch!"<<endl;
			if(op.currentWrite != 0)
			{
				program->setCurrent(op.currentWrite);
			}
			if(op.stateWrite != 0)
			{
				program->setState(op.stateWrite);
			}
			program->move(op.moveCommand);
			break;
		}
	}
	if(!allMatch)
	{
		cout<<"no match!\n"<<endl;
		program->setNotRunnable();
	}
	else if(!program->popSystemChanged())
	{
		cout<<"no system change!\n"<<endl;
		program->setNotRunnable();
	}
	else if(++stepCounter>10)
	{
		cout<<"enough steps done!\n"<<endl;
		program->setNotRunnable();
	}
}

bool Interpreter::isNop(Operation op)
{
	return (op.moveCommand == stay && (op.currentWrite == 0 || op.currentWrite == program->getCurrent())
		&& (op.stateWrite == 0 || op.stateWrite == program->getState()));
}

void Interpreter::execute()
{
	stepCounter = 0;
	while(program->getIsRunnable())
	{
		doStep();
	}
}
