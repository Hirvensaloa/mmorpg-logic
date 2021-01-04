#pragma once

#include "common.h"

//Here are defined useful print functions for logging object creation, actions etc.

namespace Log
{

	//If true all functions are enabled and when false all functions disabled. 
	static bool logEnabled = true;

	//Function prints created object to console. 
	template <typename T>
	void PrintCreation(const T& object)
	{
		if (logEnabled)
		{
			std::cout << "Creating " << object << std::endl;
		}

	}

	//Function prints removed object to console. 
	template <typename T>
	void PrintRemove(const T& object)
	{
		if (logEnabled)
		{
			std::cout << "Removing " << object << std::endl;
		}

	}

	//Function prints actions to console. 
	template <typename T>
	void PrintAction(const std::string& action, const T& object, const bool& success)
	{
		if (logEnabled)
		{
			std::string succesful = "FAILED";

			if (success)
				succesful = "SUCCEEDED";

			std::cout << "Action of type " << action << " by " << object << ": " << succesful << std::endl;
		}
	}

	//Prints the state of object to console. 
	template <typename T>
	void PrintState(const T& object)
	{
		std::cout << "State of " << object << ":" << std::endl;
		object.GetState(std::cout);
		std::cout << std::endl; 
	}

};