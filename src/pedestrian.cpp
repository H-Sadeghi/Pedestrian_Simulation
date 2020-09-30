/*-------------------------------------------
Created by Hossein Sadeghi
Project: Simulator of the pedestrian dynamics
Date = 23.09.2020

corresponding header file: pedestrian.h
--------------------------------------------*/
#include "pedestrian.h"

Pedestrian::Pedestrian()
          : id_(0), t_in_(0.0),
            position_x_(0.0), position_y_(0.0),
            velocity_x_(0.0), velocity_y_(0.0),
            acceleration_x_(0.0), acceleration_y_(0.0),
            alpha_x_(0.0), alpha_y_(0.0),
            betta_x_(0.0), betta_y_(0.0),
            force_x_(0.0), force_y_(0.0),
            force_d_x_(0.0), force_d_y_(0.0),
            force_b_x_(0.0), force_b_y_(0.0),
            force_s_x_(0.0), force_s_y_(0.0),
            v_des_x_(0.0), v_des_y_(0.0),
            groupId_ (0)
{
}

Pedestrian::Pedestrian(const int& id, const double& t_in, const double& x, const double& y, const double& v_x, const double& v_y,
                       const double& a_x, const double& a_y, const double& v_des_x, const double& v_des_y, const int& groupId)
          : id_(id), t_in_(t_in),
            position_x_ (x), position_y_ (y),
            velocity_x_ (v_x), velocity_y_ (v_y),
            acceleration_x_ (a_x), acceleration_y_ (a_y),
            alpha_x_(0.0), alpha_y_(0.0),
            betta_x_(0.0), betta_y_(0.0),
            force_x_(0.0), force_y_(0.0),
            force_d_x_(0.0), force_d_y_(0.0),
            force_b_x_(0.0), force_b_y_(0.0),
            force_s_x_(0.0), force_s_y_(0.0),
            v_des_x_ (v_des_x), v_des_y_ (v_des_y),
            groupId_ (groupId)
{
}

Pedestrian::Pedestrian(const int& id, const double& t_in, const double& x, const double& y, const double& v_des_x, const double& v_des_y, const int& groupId)
          : id_(id), t_in_(t_in),
            position_x_ (x), position_y_ (y),
            velocity_x_ (0.0), velocity_y_ (0.0),
            acceleration_x_ (0.0), acceleration_y_ (0.0),
            alpha_x_(0.0), alpha_y_(0.0),
            betta_x_(0.0), betta_y_(0.0),
            force_x_(0.0), force_y_(0.0),
            force_d_x_(0.0), force_d_y_(0.0),
            force_b_x_(0.0), force_b_y_(0.0),
            force_s_x_(0.0), force_s_y_(0.0),
            v_des_x_ (v_des_x), v_des_y_ (v_des_y),
            groupId_ (groupId)
{
}
