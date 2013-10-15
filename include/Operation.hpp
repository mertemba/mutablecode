/**
 * \file
 * \author jellysheep, ClundXIII, edlervonhuber.
 * \section LICENSE
 * Copyright (c) 2013, jellysheep, ClundXIII, edlervonhuber.
 * All rights reserved.
 * This file is licensed under the "BSD 3-Clause License".
 * Full license text is under the file "LICENSE" provided with this code.
 */

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
			int divisor = 10;
			
			if(distribution(generator)>CharsetLength/divisor)
				op.currentCondition = BasicCharset[distribution(generator)];
			
			if(distribution(generator)>CharsetLength/divisor || op.currentCondition == 0)
				op.stateCondition = BasicCharset[distribution(generator)];
			
			if(distribution(generator)>CharsetLength/divisor)
				op.currentWrite = BasicCharset[distribution(generator)];
			
			if(distribution(generator)>CharsetLength/divisor)
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
		
		friend std::ostream& operator<<(std::ostream& s, const Operation& op)
		{
			s<<"<Operation: "<<(int)op.currentCondition<<","<<(int)op.stateCondition<<","<<(int)op.currentWrite<<","<<(int)op.stateWrite<<",";
			switch(op.moveCommand)
			{
				case gotoLeft:
					s<<"left";
					break;
				case gotoRight:
					s<<"right";
					break;
				default:
					s<<"stay";
					break;
			}
			s<<">";
			return s;
		}
	};

}

#endif
