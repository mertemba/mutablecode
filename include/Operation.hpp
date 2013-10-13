
#ifndef _OPERATIONS_HPP_
#define _OPERATIONS_HPP_

namespace MutableCode
{

	enum Move
	{
		gotoLeft,
		gotoRight,
		stay
	};

	class Operation
	{
	public:
		Operation()
			:Operation(0, 0, stay, 0, 0)
		{
		}
		
		Operation(char curCond, char stateCond, Move move, char writeCur, char writeState)
			:currentCondition(curCond), stateCondition(stateCond), moveCommand(move),
			currentWrite(writeCur), stateWrite(writeState)
		{
		}
		
		//if 0, do not check
		char currentCondition;
		
		//if 0, do not check
		char stateCondition;
		
		Move moveCommand;
		
		//if 0, do not write
		char currentWrite;
		
		//if 0, do not write
		char stateWrite;
	};

}

#endif
