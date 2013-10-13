
#ifndef _OPERATIONS_HPP_
#define _OPERATIONS_HPP_

namespace MutableCode
{

	enum Move
	{
		left,
		right,
		none
	};

	class Operation
	{
	public:
		Operation()
		{
			currentCondition = 0;
			statusCondition = 0;
			moveCommand = none;
			currentWrite = 0;
			statusWrite = 0;
		}
		
		//if 0, do not check
		char currentCondition;
		
		//if 0, do not check
		char statusCondition;
		
		Move moveCommand;
		
		//if 0, do not write
		char currentWrite;
		
		//if 0, do not write
		char statusWrite;
	};

}

#endif
