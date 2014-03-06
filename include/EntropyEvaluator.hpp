/**
 * \file
 * \author jellysheep, ClundXIII, edlervonhuber.
 * \section LICENSE
 * Copyright (c) 2014, jellysheep, ClundXIII, edlervonhuber.
 * All rights reserved.
 * This file is licensed under the "BSD 3-Clause License".
 * Full license text is under the file "LICENSE" provided with this code.
 */

#ifndef _ENTROPYEVALUATOR_HPP_
#define _ENTROPYEVALUATOR_HPP_

#include <cstring>

#include "Compression.hpp"
#include "Evaluator.hpp"

namespace MutableCode
{

	class EntropyEvaluator : public Evaluator
	{
	public:
		virtual void calculateScore(ProgramItem& programItem) override
		{
			programItem.score = compress_string(programItem.output).size();
		}

	};

}

#endif
