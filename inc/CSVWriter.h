/*-------------------------------------------
Created by Hossein Sadeghi
Project: Simulator of the pedestrian dynamics
Date = 23.09.2020

function CSVwrite to write the output of .csv type
for post-processing
--------------------------------------------*/
#ifndef CSVWriter_H_
#define CSVWriter_H_
#include <fstream>
#include <sstream>
#include <direct.h>
#include <string>
#include <vector>
#include "error.h"
#include "pedestrian.h"

void CSVwrite(std::vector<Pedestrian>& pedestrians, const double& t, const std::string& name, const int& count)
{
    std::string OutputFolder = "./post_processing/results/New/";
    _mkdir(OutputFolder.c_str());

    std::stringstream sstream;
    sstream << "time,ID,Group,x,y,v_x,v_y,a_x,a_y,driving force_x,driving force_y,social force_x,social force_y,boundary force_x,boundary force_y"<< std::endl;;
    std::string header = sstream.str();

    std::stringstream fileName;
    fileName << "./post_processing/results/New/" << name << ".csv";
    std::ofstream fileStream (fileName.str().c_str(), std::ios_base::app );
    if (!fileStream.is_open())
	{
		throw FileError("Could not open .csv output file");
	}

    if (count ==0)
        fileStream << header;

    for (auto pedestrian = pedestrians.begin(); pedestrian != pedestrians.end(); ++pedestrian)
    {
        fileStream << t << "," << pedestrian->id() << "," << pedestrian->groupId() << "," << pedestrian->position_x() << "," << pedestrian->position_y()
                   << "," << pedestrian->velocity_x() << "," << pedestrian->velocity_y() << "," << pedestrian->acceleration_x() << ","
                   << pedestrian->acceleration_y() << "," << pedestrian->force_driving_x() << "," << pedestrian->force_driving_y() << ","
                   << pedestrian->force_social_x() << "," << pedestrian->force_social_y() << "," << pedestrian->force_boundary_x() << ","
                   << pedestrian->force_boundary_y() << "\n";
    }
}
#endif // CSVWriter_H_
