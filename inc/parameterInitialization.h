/*-------------------------------------------
Created by Hossein Sadeghi
Project: Simulator of the pedestrian dynamics
Date = 23.09.2020

Function parameterInitialization for reading the
parameters employing the ParameterReader class
*declaring and initialization of some counters
--------------------------------------------*/
#ifndef parameterInitialization_H_
#define parameterInitialization_H_
#include <vector>
#include <string>
#include "parameterReader.h"

//declaring the parameters of the system
double flux, r_ped, v_des_min, v_des_max, a_max, t_end, delta_t,
       t_relax, iStrength_p, iRange_p, iStrength_b, iRange_b, lambda, k, kappa, factor_respect;
//visualization steps
size_t vis_spacing;
//the number of waiting pedestrians in each queue
int n_queue = flux * t_end;

//counters of the time loop
size_t count = 0;
size_t count_tA = 0;
size_t count_tC = 0;
size_t count_VTK = 0;
//base name for outputting files
std::string baseName = "PedSim";

//container of the walls and their starting and end points
std::map<std::string,std::vector<double> > boundaries;

void parameterInitialization()
{
    ParameterReader parameter;

    // read the parameters
    parameter.readParameters("./data/parameters.dat");

    // store the values
    //reading the positions of the walls
    std::vector<double> bPoints(4,0.0); //The two points of the walls
    parameter.getParameter("b1_start_x",bPoints[0]);
    parameter.getParameter("b1_start_y",bPoints[1]);
    parameter.getParameter("b1_end_x",bPoints[2]);
    parameter.getParameter("b1_end_y",bPoints[3]);
    boundaries["b1"] = bPoints;
    parameter.getParameter("b2_start_x",bPoints[0]);
    parameter.getParameter("b2_start_y",bPoints[1]);
    parameter.getParameter("b2_end_x",bPoints[2]);
    parameter.getParameter("b2_end_y",bPoints[3]);
    boundaries["b2"] = bPoints;
    parameter.getParameter("b3_start_x",bPoints[0]);
    parameter.getParameter("b3_start_y",bPoints[1]);
    parameter.getParameter("b3_end_x",bPoints[2]);
    parameter.getParameter("b3_end_y",bPoints[3]);
    boundaries["b3"] = bPoints;
    parameter.getParameter("b4_start_x",bPoints[0]);
    parameter.getParameter("b4_start_y",bPoints[1]);
    parameter.getParameter("b4_end_x",bPoints[2]);
    parameter.getParameter("b4_end_y",bPoints[3]);
    boundaries["b4"] = bPoints;
    parameter.getParameter("b5_start_x",bPoints[0]);
    parameter.getParameter("b5_start_y",bPoints[1]);
    parameter.getParameter("b5_end_x",bPoints[2]);
    parameter.getParameter("b5_end_y",bPoints[3]);
    boundaries["b5"] = bPoints;
    parameter.getParameter("b6_start_x",bPoints[0]);
    parameter.getParameter("b6_start_y",bPoints[1]);
    parameter.getParameter("b6_end_x",bPoints[2]);
    parameter.getParameter("b6_end_y",bPoints[3]);
    boundaries["b6"] = bPoints;
    parameter.getParameter("b7_start_x",bPoints[0]);
    parameter.getParameter("b7_start_y",bPoints[1]);
    parameter.getParameter("b7_end_x",bPoints[2]);
    parameter.getParameter("b7_end_y",bPoints[3]);
    boundaries["b7"] = bPoints;
    parameter.getParameter("b8_start_x",bPoints[0]);
    parameter.getParameter("b8_start_y",bPoints[1]);
    parameter.getParameter("b8_end_x",bPoints[2]);
    parameter.getParameter("b8_end_y",bPoints[3]);
    boundaries["b8"] = bPoints;

    //reading the parameters and constants
    parameter.getParameter("flux",flux);
    parameter.getParameter("radius_of_pedestrians", r_ped);
    parameter.getParameter("desired_velocity_min", v_des_min);
    parameter.getParameter("desired_velocity_max", v_des_max);
    parameter.getParameter("maximum_acceleration", a_max);
    parameter.getParameter("duration",t_end);
    parameter.getParameter("time_step_size",delta_t);
    parameter.getParameter("visualization_spacing",vis_spacing);
    parameter.getParameter("relaxation_time",t_relax);
    parameter.getParameter("interaction_strength_pedestrians",iStrength_p);
    parameter.getParameter("interaction_range_pedestrians",iRange_p);
    parameter.getParameter("interaction_strength_boundaries",iStrength_b);
    parameter.getParameter("interaction_range_boundaries",iRange_b);
    parameter.getParameter("lambda",lambda);
    parameter.getParameter("k",k);
    parameter.getParameter("kappa",kappa);
    parameter.getParameter("respect_factor",factor_respect);

    //number of waiting particles in each queue
    n_queue = flux * t_end;

    //delete the previous .csv file if exits
    remove(("./post_processing/results/New/"+baseName+".csv").c_str());
}

#endif // parameterInitialization_H_
