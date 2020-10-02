/*-------------------------------------------
Created by Hossein Sadeghi
Project: Simulator of the pedestrian dynamics
Date = 23.09.2020

class Queue represents queue of pedestrians
waiting to enter the system from inlet corridors
--------------------------------------------*/
#ifndef Queue_H_
#define Queue_H_

#include <vector>
#include <string>
#include "error.h"
#include "pedestrian.h"

class Queue
{
public:
    Queue();

    Queue(const int& n, const double& flux, const double& delta_t, const int& groupId, const char& normal, const double& v_des_min, const double& v_des_max, const double& xyMin, const double& xyMax);

    std::vector<Pedestrian> getQueue()
    {
        return pedestriansPool_;
    }
private:
    std::vector<Pedestrian> pedestriansPool_; //a pool of pedestrian
    int nPedestrian_; //number of pedestrians waiting in the queue
    int groupId_; //ID of the group
    double flux_;
    char normal_; //normal direction of the inlet
};

#endif // Queue_H_
