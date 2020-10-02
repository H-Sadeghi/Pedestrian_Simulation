/*-------------------------------------------
Created by Hossein Sadeghi
Project: Simulator of the pedestrian dynamics
Date = 23.09.2020
--------------------------------------------*/
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <math.h>
#include "error.h"
#include "parameterInitialization.h"
#include "pedestrian.h"
#include "queue.h"
#include "solver.h"
#include "VTKWriter.h"
#include "CSVWriter.h"

int main()
{
	try
	{
	    //reading and initializing parameters of the simulation
	    parameterInitialization();

        //creating two queues for regions A and C with group IDs 0 and 1 and normals in y and x directions, respectively
        Queue queueA(n_queue, flux, delta_t, 0, 'y', v_des_min, v_des_max, boundaries["b7"][0], boundaries["b8"][0]);
        Queue queueC(n_queue, flux, delta_t, 1, 'x', v_des_min, v_des_max, boundaries["b2"][1], boundaries["b1"][1]);

        std::vector<Pedestrian> activePedestrians; //container of the pedestrians which are active in the system
        activePedestrians.reserve(n_queue*2); //reserve total number of pedestrians in this container

        //delta_t -> time_step
        for (double t = 0.0; t <= t_end + delta_t; t += delta_t)
        {
            std::cout << "Time: " << t << " s" << std::endl;

            //checking if any particles in any of the two queues are ready to enter the system
            if (abs(t - queueA.getQueue()[count_tA].time_in()) < 1e-06)
            {
                activePedestrians.push_back(queueA.getQueue()[count_tA]);
                ++count_tA;
            }
            if (abs(t - queueC.getQueue()[count_tC].time_in()) < 1e-06)
            {
                activePedestrians.push_back(queueC.getQueue()[count_tC]);
                ++count_tC;
            }

            //solving the equations of the social force model
            solve(activePedestrians, boundaries, t, delta_t, r_ped, a_max, t_relax, iStrength_p, iRange_p, iStrength_b, iRange_b, lambda, k, kappa, factor_respect);

            //writing .vtk files for visualization (by vis_spacing frequency)
            if (count % vis_spacing == 0)
            {
                VTKwrite(activePedestrians, baseName, count_VTK);
                ++count_VTK;
            }
            //writing .csv file for post processing
            CSVwrite(activePedestrians, t, baseName, count);

            ++count;
        }
        return 0;
    }
    catch(const FileError & e)
    {
        std::cerr << "ERROR: " << e.what() << std::endl;
        return 1;
    }
    catch(...)
    {
        std::cerr << "ERROR: unknown exception" << std::endl;
        return 2;
    }
}
