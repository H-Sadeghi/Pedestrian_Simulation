/*-------------------------------------------
Created by Hossein Sadeghi
Project: Simulator of the pedestrian dynamics
Date = 23.09.2020

corresponding header file: parameterReader.h
--------------------------------------------*/
#include "parameterReader.h"

bool ParameterReader::readParameters(const std::string& filename)
{
	std::ifstream parameterFile;
	std::string temp;
	std::string key;
    double value;

	parameterFile.open(filename.c_str());
	if (!parameterFile.is_open())
	{
		throw FileError("Could not find parameter file with the name " + filename);
	}
	else
	{
		// to ignore the first line of the parameter's file
		std::getline(parameterFile,temp);

		while(!parameterFile.eof())
		{
			parameterFile >> key >> value;
			parameter_[key] = value;
		}

		parameterFile.close();
	}
	return true;
}
