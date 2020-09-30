/*-------------------------------------------
Created by Hossein Sadeghi
Project: Simulator of the pedestrian dynamics
Date = 23.09.2020

corresponding header file: queue.h
--------------------------------------------*/
#include "queue.h"
#include <random>

Queue::Queue()
     : nPedestrian_(0), groupId_(0), normal_(' '), flux_(0.0)
{
    Pedestrian newPedestrian;
    pedestriansPool_.push_back(newPedestrian);
}

Queue::Queue(const int& n, const double& flux, const int& groupId, const char& normal, const double& v_des_min, const double& v_des_max, const double& xyMin, const double& xyMax)
     : nPedestrian_(n), groupId_(groupId), normal_(normal), flux_(flux)
{
    pedestriansPool_.reserve(n); //reserve number of pedestrian in the container
    static int id = 1; //ID of each pedestrian
    double v_des_x, v_des_y, x, y, t_in; //auxiliary variables

    //random generator seeding by the ID of the queues for reproducibility
    std::mt19937 gen(groupId);
    //random values for position of the pedestrian (x or y) and their desired velocity
    std::uniform_real_distribution<> distr_xy(xyMin+0.5, xyMax-0.5);
    std::uniform_real_distribution<> distr_v(v_des_min, v_des_max);

    //creating n pedestrians and inserting them to the queue container
    switch(normal){
        case 'y':
            for(int i=0; i<n; i++)
            {
                //random entering time of the pedestrian based on the flux
                std::uniform_int_distribution<> distr_t(i*10/flux+1, (i+1)*10/flux);
                t_in = double(distr_t(gen)/10.0);
                x = distr_xy(gen);
                y = 0.0;
                v_des_x = 0.0;
                v_des_y = distr_v(gen);
                //creating a new pedestrian using the calculated values
                Pedestrian newPedestrian(id, t_in, x, y, v_des_x, v_des_y, groupId);
                //adding the pedestrian to the queue
                pedestriansPool_.push_back(newPedestrian);
                ++id;
            }
            break;
        case 'x':
            for(int i=0; i<n; i++)
            {
                std::uniform_int_distribution<> distr_t(i*10/flux+1, (i+1)*10/flux);
                t_in = double(distr_t(gen)/10.0);
                x = 0.0;
                y = distr_xy(gen);
                v_des_x = distr_v(gen);
                v_des_y = 0.0;
                Pedestrian newPedestrian(id, t_in, x, y, v_des_x, v_des_y, groupId);
                pedestriansPool_.push_back(newPedestrian);
                ++id;
            }
            break;
        default:
            throw FileError("bad state");
    }
}
