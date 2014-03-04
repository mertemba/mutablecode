/**
 * \file
 * \author jellysheep, ClundXIII, edlervonhuber.
 * \section LICENSE
 * Copyright (c) 2014, jellysheep, ClundXIII, edlervonhuber.
 * All rights reserved.
 * This file is licensed under the "BSD 3-Clause License".
 * Full license text is under the file "LICENSE" provided with this code.
 */

#include "Program.hpp"
#include "ProgramLoader.hpp"

using namespace MutableCode;

Random Program::random(0, 7);

Program::Program(const std::string& name, const ProgramLoader& programLoader)
	:name(name),code((&programLoader)->getCode())
{
}
