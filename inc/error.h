/*-------------------------------------------
Created by Hossein Sadeghi
Project: Simulator of the pedestrian dynamics
Date = 23.09.2020

class FileError as a subclass of default stdexcept
for exception handling
--------------------------------------------*/
#ifndef Error_H_
#define Error_H_
#include<string>
#include<stdexcept>
class FileError : public std::runtime_error{
public:
    FileError(const std::string & emsg)
    : std::runtime_error(emsg){
    }
};
#endif // Error_H_
