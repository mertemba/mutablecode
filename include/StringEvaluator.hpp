/**
 * \file
 * \author jellysheep, ClundXIII, edlervonhuber.
 * \section LICENSE
 * Copyright (c) 2014, jellysheep, ClundXIII, edlervonhuber.
 * All rights reserved.
 * This file is licensed under the "BSD 3-Clause License".
 * Full license text is under the file "LICENSE" provided with this code.
 */

#ifndef _STRINGEVALUATOR_HPP_
#define _STRINGEVALUATOR_HPP_

#include <cmath>
#include <string>
#include <vector>

#include "Evaluator.hpp"

namespace std
{
	#include "LevenshteinDistance.hpp"
}

namespace MutableCode
{

	class StringEvaluator : public Evaluator
	{
	private:
		std::string str;
	public:
		StringEvaluator(const std::string& str):str(str)
		{
		}

		virtual void calculateScore(ProgramItem& programItem) override
		{
			programItem.score = -(int)levenshtein_distance(programItem.output, str)
				-std::log(std::abs(programItem.output.size()-str.size())+1)/2;
		}

	};

}

#endif
