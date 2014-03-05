/**
 * \file
 * \author jellysheep, ClundXIII, edlervonhuber.
 * \section LICENSE
 * Copyright (c) 2014, jellysheep, ClundXIII, edlervonhuber.
 * All rights reserved.
 * This file is licensed under the "BSD 3-Clause License".
 * Full license text is under the file "LICENSE" provided with this code.
 */

#ifndef _RANDOM_HPP_
#define _RANDOM_HPP_

#include <chrono>
#include <random>

namespace MutableCode
{

	class Random
	{
	private:
		std::uniform_int_distribution<int> distribution;
		std::uniform_real_distribution<double> realDistribution;
		std::default_random_engine randomEngine;
		std::random_device* randomDevice;
		bool randomDeviceConstructed;

	public:
		Random(int min, int max):distribution(min,max),realDistribution(0,1),
			randomEngine(std::chrono::system_clock::now().time_since_epoch().count())
		{
			randomDevice = NULL;
			randomDeviceConstructed = false;
			try
			{
				randomDevice = new std::random_device();
				randomDeviceConstructed = true;
				(*randomDevice)();
			}
			catch(...)
			{
				if(randomDeviceConstructed)
				{
					delete randomDevice;
					randomDevice = NULL;
					randomDeviceConstructed = false;
				}
			}
		}
		~Random()
		{
			if(randomDeviceConstructed && randomDevice != NULL)
				delete randomDevice;
		}

		bool hasRandomDevice()
		{
			return randomDeviceConstructed;
		}

		int get()
		{
			if(randomDeviceConstructed)
				return distribution(*randomDevice);
			else
				return distribution(randomEngine);
		}
		double getReal()
		{
			if(randomDeviceConstructed)
				return realDistribution(*randomDevice);
			else
				return realDistribution(randomEngine);
		}
	};

}

#endif
