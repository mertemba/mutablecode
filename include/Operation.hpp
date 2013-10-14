
#ifndef _OPERATIONS_HPP_
#define _OPERATIONS_HPP_

#include <random>
#include <chrono>
#include <iostream>

namespace MutableCode
{
	
	const int CharsetLength = 64;
	const char BasicCharset[CharsetLength+1] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+-";

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
		
		static Operation randomOp()
		{
			Operation op;
			
			std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
			std::chrono::system_clock::duration timepoint = now.time_since_epoch();
			std::default_random_engine generator(timepoint.count());
			std::uniform_int_distribution<int> distribution(0, CharsetLength-1);
			
			if(distribution(generator)>CharsetLength/4)
				op.currentCondition = BasicCharset[distribution(generator)];
			
			if(distribution(generator)>CharsetLength/4 || op.currentCondition == 0)
				op.stateCondition = BasicCharset[distribution(generator)];
			
			if(distribution(generator)>CharsetLength/4)
				op.currentWrite = BasicCharset[distribution(generator)];
			
			if(distribution(generator)>CharsetLength/4)
				op.stateWrite = BasicCharset[distribution(generator)];
			
			int move = distribution(generator)%3;
			switch(move)
			{
				case 0:
					op.moveCommand = gotoLeft;
					break;
				case 1:
					op.moveCommand = gotoRight;
					break;
				default:
					op.moveCommand = stay;
					break;
			}
			
			return op;
		}
		
		//if 0, do not check
		char currentCondition;
		
		//if 0, do not check
		char stateCondition;
		
		//if 0, do not write
		char currentWrite;
		
		//if 0, do not write
		char stateWrite;
		
		Move moveCommand;
		
		void dump()
		{
			std::cout<<"Operation<"<<(int)currentCondition<<","<<(int)stateCondition<<","<<(int)currentWrite<<","<<(int)stateWrite<<",";
			switch(moveCommand)
			{
				case gotoLeft:
					std::cout<<"left";
					break;
				case gotoRight:
					std::cout<<"right";
					break;
				default:
					std::cout<<"stay";
					break;
			}
			std::cout<<">"<<std::endl;
		}
	};

}

#endif
