/*-------------------------------------------
Created by Hossein Sadeghi
Project: Simulator of the pedestrian dynamics
Date = 23.09.2020

class ParameterReader for reading the parameter
file
--------------------------------------------*/
#ifndef parameterReader_H_
#define parameterReader_H_
#include <fstream>
#include <map>
#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include "error.h"

class ParameterReader
{
public:
	std::map<std::string,double> parameters()
	{
		return parameter_;
	}
	std::map<std::string,double> parameters() const
	{
		return parameter_;
	}
bool readParameters(const std::string& filename);

template <typename T>
inline T getParameter(const std::string& key, T& value);

private:
	std::map<std::string,double> parameter_;
};

template <typename T>
inline T ParameterReader::getParameter(const std::string& key, T& value)
{
	return value =  parameter_[key];
}
#endif // parameterReader_H_
