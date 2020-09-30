/*-------------------------------------------
Created by Hossein Sadeghi
Project: Simulator of the pedestrian dynamics
Date = 23.09.2020

function VTKwrite to write the output of .vtk type
for visualization
--------------------------------------------*/
#ifndef VTKWriter_H_
#define VTKWriter_H_
#include <fstream>
#include <sstream>
#include <iomanip>

#include <string>
#include <vector>
#include "error.h"
#include "pedestrian.h"

void VTKwrite(std::vector<Pedestrian>& pedestrians, const std::string& baseName, const size_t& counter)
{
    std::stringstream sstream;
    sstream << "# vtk DataFile Version 3.0\n";
    sstream << "Pedestrian simulation VTK output\n";
    sstream << "ASCII\n";
    sstream << "DATASET UNSTRUCTURED_GRID\n"<< std::endl;

    std::string header = sstream.str();

    std::stringstream fileName;
    fileName << "./post_processing/results/New/" << baseName << "_" <<  std::setw(4) << std::setfill( '0') << counter << ".vtk";
    std::ofstream fileStream ( fileName.str().c_str() );
    if (!fileStream.is_open())
	{
		throw FileError("Could not open output file");
	}

    fileStream << header;

    fileStream << "POINTS " << pedestrians.size() << " double\n";
    for (auto pedestrian = pedestrians.begin(); pedestrian != pedestrians.end(); ++pedestrian)
    {
        fileStream << pedestrian->position_x() << " " << pedestrian->position_y() << " " << " 0\n";
    }
    fileStream << "\n";
    fileStream << "CELL_TYPES 1" << "\n";
    fileStream << "1" << "\n";
    fileStream << "\n";
    fileStream << "POINT_DATA " << pedestrians.size() << "\n";

    fileStream << "SCALARS flag int 1\n";
	fileStream << "LOOKUP_TABLE default\n";
    for (auto pedestrian = pedestrians.begin(); pedestrian != pedestrians.end(); ++pedestrian)
    {
        fileStream << pedestrian->groupId() << "\n";
    }
    fileStream << "\n";
    fileStream << "VECTORS velocity double\n";
    for (auto pedestrian = pedestrians.begin(); pedestrian != pedestrians.end(); ++pedestrian)
    {
        fileStream << pedestrian->velocity_x() << " " << pedestrian->velocity_y() << " 0.0\n";
    }
    fileStream << "\n";
    fileStream << "VECTORS acceleration double\n";
    for (auto pedestrian = pedestrians.begin(); pedestrian != pedestrians.end(); ++pedestrian)
    {
        fileStream << pedestrian->acceleration_x() << " " << pedestrian->acceleration_y() << " 0.0\n";
    }
    fileStream << "\n";
    fileStream << "VECTORS f_driving double\n";
    for (auto pedestrian = pedestrians.begin(); pedestrian != pedestrians.end(); ++pedestrian)
    {
        fileStream << pedestrian->force_driving_x() << " " << pedestrian->force_driving_y() << " 0.0\n";
    }
    fileStream << "\n";
    fileStream << "VECTORS f_social double\n";
    for (auto pedestrian = pedestrians.begin(); pedestrian != pedestrians.end(); ++pedestrian)
    {
        fileStream << pedestrian->force_social_x() << " " << pedestrian->force_social_y() << " 0.0\n";
    }
    fileStream << "\n";
    fileStream << "VECTORS f_boundary double\n";
    for (auto pedestrian = pedestrians.begin(); pedestrian != pedestrians.end(); ++pedestrian)
    {
        fileStream << pedestrian->force_boundary_x() << " " << pedestrian->force_boundary_y() << " 0.0\n";
    }
}
#endif // VTKWriter_H_
