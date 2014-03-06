/**
 * \file
 * \author jellysheep, ClundXIII, edlervonhuber.
 * \section LICENSE
 * Copyright (c) 2014, jellysheep, ClundXIII, edlervonhuber.
 * All rights reserved.
 * This file is licensed under the "BSD 3-Clause License".
 * Full license text is under the file "LICENSE" provided with this code.
 */

#ifndef _EVALUATOR_HPP_
#define _EVALUATOR_HPP_

#include "Program.hpp"

namespace MutableCode
{

	class Evaluator
	{
	public:
		virtual void calculateScore(ProgramItem& programItem) = 0;

	};

	class SimpleEvaluator : public Evaluator
	{
	public:
		virtual void calculateScore(ProgramItem& programItem) override
		{
			bool emptyOutputChar = false;
			if(programItem.output.find('_') != std::string::npos)
				emptyOutputChar = true;
			programItem.score =
				-std::log(programItem.program.getCode().size()+1)/2
				+std::log(programItem.output.size()+1)
				+std::log(programItem.inputReads+1)
				-(programItem.inputBufferUnderrun?2:0)
				-(emptyOutputChar?1:0)
			;
		}

	};

}

#endif
