/*-------------------------------------------
Created by Hossein Sadeghi
Project: Simulator of the pedestrian dynamics
Date = 23.09.2020

Solver of the pedestrian simulation based on
the social force model and following a prediction-
correction algorithm
--------------------------------------------*/
#ifndef Solver_H_
#define Solver_H_

#include "pedestrian.h"
#include "queue.h"
#include <iostream>
#include <vector>
#include <math.h>

void predictor(Pedestrian& pedestrian, double& position_x_p, double& position_y_p, double& velocity_x_p, double& velocity_y_p,
               double& acceleration_x_p, double& acceleration_y_p, double& alpha_x_p, double& alpha_y_p, const double& delta_t,
               const double& delta_t2, const double& delta_t3, const double& delta_t4)
{
    //calculating the predicted position, velocity, acceleration and first derivative of acceleration from the values from previous time step
    position_x_p = pedestrian.position_x() + delta_t * pedestrian.velocity_x() + delta_t2/2.0 * pedestrian.acceleration_x()
                   + delta_t3/6.0 * pedestrian.alpha_x() + delta_t4/24.0 * pedestrian.betta_x();
    position_y_p = pedestrian.position_y() + delta_t * pedestrian.velocity_y() + delta_t2/2.0 * pedestrian.acceleration_y()
                   + delta_t3/6.0 * pedestrian.alpha_y() + delta_t4/24.0 * pedestrian.betta_y();
    velocity_x_p = pedestrian.velocity_x() + delta_t * pedestrian.acceleration_x() + delta_t2/2.0 * pedestrian.alpha_x()
                   + delta_t3/6.0 * pedestrian.betta_x();
    velocity_y_p = pedestrian.velocity_y() + delta_t * pedestrian.acceleration_y() + delta_t2/2.0 * pedestrian.alpha_y()
                   + delta_t3/6.0 * pedestrian.betta_y();
    acceleration_x_p = pedestrian.acceleration_x() + delta_t * pedestrian.alpha_x() + delta_t2/2.0 * pedestrian.betta_x();
    acceleration_y_p = pedestrian.acceleration_y() + delta_t * pedestrian.alpha_y() + delta_t2/2.0 * pedestrian.betta_y();
    alpha_x_p = pedestrian.alpha_x() + delta_t * pedestrian.betta_x();
    alpha_y_p = pedestrian.alpha_y() + delta_t * pedestrian.betta_y();
}

void collisionDetector(Pedestrian& pedestrian, Pedestrian& anotherPedestrian, const double& position_x_p, const double& position_y_p, const double& r_ped, const double& factor_respect, bool& flag_collision)
{
    //calculating the radius of the respect area
    double d_respect = factor_respect * r_ped;

    //calculating the center of the respect area
    double center_respect_x;
    double center_respect_y;
    if(pedestrian.v_des_x() > 0)
    {
        center_respect_x = position_x_p + d_respect;
        center_respect_y = position_y_p;
    }
    else
    {
        center_respect_x = position_x_p;
        center_respect_y = position_y_p + d_respect;
    }

    //calculating the distance between the respect area and the other pedestrian
    double distance = sqrt((center_respect_x-anotherPedestrian.position_x())*(center_respect_x-anotherPedestrian.position_x())
                           +(center_respect_y-anotherPedestrian.position_y())*(center_respect_y-anotherPedestrian.position_y()));

    //if the distance between the other pedestrian and respect area is less than the sum of their radii
    if (distance <= d_respect+r_ped)
        flag_collision = true;
}

void calcSocialForce(Pedestrian& pedestrian, Pedestrian& anotherPedestrian, double& force_social_x, double& force_social_y, const double& position_x_p,
                     const double& position_y_p, const double& velocity_x_p, const double& velocity_y_p, const double& r_ped,
                     const double& iStrength_p, const double& iRange_p, const double& lambda, const double& k, const double& kappa)
{
    //calculating the distance between the two pedestrians
    double distance = sqrt((position_x_p-anotherPedestrian.position_x())*(position_x_p-anotherPedestrian.position_x())
                           +(position_y_p-anotherPedestrian.position_y())*(position_y_p-anotherPedestrian.position_y()));

    //normal direction of the force exerted by the other pedestrian
    double dir_n_x = (position_x_p-anotherPedestrian.position_x())/distance;
    double dir_n_y = (position_y_p-anotherPedestrian.position_y())/distance;

    //tangential direction of the force exerted by the other pedestrian (the one which is more in the desired direction)
    double dir_t_x, dir_t_y;
    if ((pedestrian.v_des_x() > 0 && position_y_p >= anotherPedestrian.position_y()) || (pedestrian.v_des_y() > 0 && position_x_p <= anotherPedestrian.position_x()))
    {
        dir_t_x = dir_n_y;
        dir_t_y = -dir_n_x;
    }
    else
    {
        dir_t_x = -dir_n_y;
        dir_t_y = dir_n_x;
    }

    double cosPhi; //angle between the desired direction of motion and the direction of repulsive force
    if(pedestrian.v_des_x() > 0)
        cosPhi = (anotherPedestrian.position_x()-position_x_p) / distance;
    else
        cosPhi = (anotherPedestrian.position_y()-position_y_p) / distance;

    double factor_form = lambda + (1.0-lambda) * (1.0+cosPhi)/2.0; //to consider the field of view of the pedestrian

    //socio-psychological force
    force_social_x = iStrength_p * exp((2*r_ped-distance)/iRange_p) * dir_n_x * factor_form;
    force_social_y = iStrength_p * exp((2*r_ped-distance)/iRange_p) * dir_n_y * factor_form;

    //physical forces (body force + sliding force)
    double force_body_x = 0.0;
    double force_body_y = 0.0;
    if (2.0*r_ped-distance > 0)
    {
        force_body_x = k * (2.0*r_ped-distance) * dir_n_x;
        force_body_y = k * (2.0*r_ped-distance) * dir_n_y;
    }

    double force_sliding_x = 0.0;
    double force_sliding_y = 0.0;
    //calculating the velocity difference in the tangential direction between the two pedestrians
    double deltaVel_t = (anotherPedestrian.velocity_x() - velocity_x_p) * dir_t_x + (anotherPedestrian.velocity_y() - velocity_y_p) * dir_t_y; //tangential component of the relative velocity
    if (2.0*r_ped-distance > 0)
    {
        force_sliding_x = kappa * (2.0*r_ped-distance) * deltaVel_t * dir_t_x;
        force_sliding_y = kappa * (2.0*r_ped-distance) * deltaVel_t * dir_t_y;
    }
    force_social_x += force_sliding_x + force_body_x;
    force_social_y += force_sliding_y + force_body_y;
}

void calcBoundaryForce(Pedestrian& pedestrian, const std::vector<double>& bPoints, double& force_boundary_x, double& force_boundary_y,
                       const double& position_x_p, const double& position_y_p, const double& velocity_x_p, const double& velocity_y_p,
                       const double& r_ped, const double& iStrength_b, const double& iRange_b, const double& k, const double& kappa)
{
    //bPoints[0]->b_start_x, [1]->b_start_y, [2]->b_end_x, [3]->b_end_y
    double length_b = sqrt((bPoints[2]-bPoints[0])*(bPoints[2]-bPoints[0]) + (bPoints[3]-bPoints[1])*(bPoints[3]-bPoints[1])); //length of the wall

    //tangential direction of the wall
    double dir_t_x = (bPoints[2]-bPoints[0]) / length_b;
    double dir_t_y = (bPoints[3]-bPoints[1]) / length_b;

    //a condition to be used when defining shortest distance to the wall (inner product of the vector from b_start to pedestrian (1) and direction vector of wall(2))
    double condition = (position_x_p-bPoints[0]) * dir_t_x + (position_y_p-bPoints[1]) * dir_t_y;

    //shortest distance to the wall
    double distance_x;
    double distance_y;
    if (condition <= 0) //the angel between (1) and (2) > 90
    {
        //distance between the pedestrian and one end of the wall
        distance_x = position_x_p - bPoints[0];
        distance_y = position_y_p - bPoints[1];
    }
    else if (condition >= length_b)
    {
        //distance between the pedestrian and other end of the wall
        distance_x = position_x_p - bPoints[2];
        distance_y = position_y_p - bPoints[3];
    }
    else
    {
        //normal distance to the wall
        distance_x = position_x_p - bPoints[0] - condition * dir_t_x;
        distance_y = position_y_p - bPoints[1] - condition * dir_t_y;
    }
    double distance = sqrt(distance_x*distance_x + distance_y*distance_y);

    //the socio-psychological force from the wall
    force_boundary_x = iStrength_b * exp((r_ped-distance)/iRange_b) * distance_x/distance;
    force_boundary_y = iStrength_b * exp((r_ped-distance)/iRange_b) * distance_y/distance;

    //physical forces
    double force_body_x = 0.0;
    double force_body_y = 0.0;
    if (r_ped-distance > 0)
    {
        force_body_x = k * (r_ped-distance) * distance_x/distance;
        force_body_y = k * (r_ped-distance) * distance_y/distance;
    }

    double force_sliding_x = 0.0;
    double force_sliding_y = 0.0;
    double velocity_t = velocity_x_p * dir_t_x + velocity_y_p * dir_t_y; //tangential component of the velocity
    if (r_ped - distance > 0)
    {
        force_sliding_x = kappa * (r_ped-distance) * velocity_t * dir_t_x;
        force_sliding_y = kappa * (r_ped-distance) * velocity_t * dir_t_y;
    }
    force_boundary_x += force_body_x + force_sliding_x;
    force_boundary_y += force_body_y + force_sliding_y;
}

void calcDrivingForce(Pedestrian& pedestrian, const double& position_x_p, const double& position_y_p, const double& velocity_x_p,
                      const double& velocity_y_p, const double& t_relax, const bool& flag_collision)
{
    if (flag_collision)
    {
        //setting desired velocity temporarily to zero in case of collision
        pedestrian.force_driving_x() = -velocity_x_p / t_relax;
        pedestrian.force_driving_y() = -velocity_y_p / t_relax;
    }
    else
    {
        pedestrian.force_driving_x() = (pedestrian.v_des_x() - velocity_x_p) / t_relax;
        pedestrian.force_driving_y() = (pedestrian.v_des_y() - velocity_y_p) / t_relax;
    }
}

void corrector(Pedestrian& pedestrian, double& position_x_p, double& position_y_p, double& velocity_x_p, double& velocity_y_p, double& alpha_x_p,
               double& alpha_y_p, const double& delta_t, const double& delta_t2, const double& factor_corr_x, const double& factor_corr_y)
{
    //calculating the actual position, velocity, acceleration and first and second derivative of acceleration
    pedestrian.position_x() = position_x_p + factor_corr_x * delta_t2/2.0 * 19.0/120.0;
    pedestrian.position_y() = position_y_p + factor_corr_y * delta_t2/2.0 * 19.0/120.0;
    pedestrian.velocity_x() = velocity_x_p + factor_corr_x * delta_t/2.0 * 3.0/4.0;
    pedestrian.velocity_y() = velocity_y_p + factor_corr_y * delta_t/2.0 * 3.0/4.0;
    pedestrian.alpha_x() = alpha_x_p + factor_corr_x * 3.0/delta_t * 1.0/2.0;
    pedestrian.alpha_y() = alpha_y_p + factor_corr_y * 3.0/delta_t * 1.0/2.0;
    pedestrian.betta_x() = pedestrian.betta_x() + factor_corr_x * 12.0/delta_t2 * 1.0/12.0;
    pedestrian.betta_y() = pedestrian.betta_y() + factor_corr_y * 12.0/delta_t2 * 1.0/12.0;
}

void solve(std::vector<Pedestrian>& activPedestrians, std::map<std::string,std::vector<double> >& boundaries, const double& t, const double& delta_t, const double& r_ped, const double& a_max,
           const double& t_relax, const double& iStrength_p, const double& iRange_p, const double& iStrength_b, const double& iRange_b,
           const double& lambda, const double& k, const double& kappa, const double& factor_respect)
{
    double delta_t2 = pow(delta_t, 2);
    double delta_t3 = pow(delta_t, 3);
    double delta_t4 = pow(delta_t, 4);

	for (auto pedestrian = activPedestrians.begin(); pedestrian != activPedestrians.end(); ++pedestrian)
    {
        //some auxiliary variables (e.g. for predicted values)
        double position_x_p, position_y_p, velocity_x_p, velocity_y_p, acceleration_x_p, acceleration_y_p, alpha_x_p, alpha_y_p,
               force_social_x, force_social_y, force_boundary_x, force_boundary_y;

        bool flag_collision;
        //prediction step
        predictor(*pedestrian, position_x_p, position_y_p, velocity_x_p, velocity_y_p, acceleration_x_p, acceleration_y_p, alpha_x_p, alpha_y_p,
                  delta_t, delta_t2, delta_t3, delta_t4);

        //setting the forces from the previous time step to zero
        pedestrian->force_social_x() = 0.0;
        pedestrian->force_social_y() = 0.0;
        pedestrian->force_boundary_x() = 0.0;
        pedestrian->force_boundary_y() = 0.0;
        pedestrian->force_x() = 0.0;
        pedestrian->force_y() = 0.0;
        //calculating social forces from other pedestrians
        for (auto anotherPedestrian = activPedestrians.begin(); anotherPedestrian != activPedestrians.end(); ++anotherPedestrian)
        {
            flag_collision = false;
            if(anotherPedestrian != pedestrian)
            {
                //checking if the respect area of the pedestrian is respected by the other pedestrian
                if (!flag_collision) //
                    collisionDetector(*pedestrian, *anotherPedestrian, position_x_p, position_y_p, r_ped, factor_respect, flag_collision);

                calcSocialForce(*pedestrian, *anotherPedestrian, force_social_x, force_social_y, position_x_p, position_y_p, velocity_x_p, velocity_y_p,
                                r_ped, iStrength_p, iRange_p, lambda, k, kappa);

                //superposition of the social forces exerted from all other pedestrian and adding to the total force
                pedestrian->force_social_x() += force_social_x;
                pedestrian->force_social_y() += force_social_y;
            }
        }
        //adding the social force to the total force
        pedestrian->force_x() += pedestrian->force_social_x();
        pedestrian->force_y() += pedestrian->force_social_y();

        //calculating forces from boundaries
        for (auto const& boundary : boundaries)
        {
            calcBoundaryForce(*pedestrian, boundary.second, force_boundary_x, force_boundary_y, position_x_p, position_y_p, velocity_x_p, velocity_y_p,
                              r_ped, iStrength_b, iRange_b, k, kappa);
            //superposition of the forces exerted from all the boundaries
            pedestrian->force_boundary_x() += force_boundary_x;
            pedestrian->force_boundary_y() += force_boundary_y;
        }
        //adding the boundary force to the total force
        pedestrian->force_x() += pedestrian->force_boundary_x();
        pedestrian->force_y() += pedestrian->force_boundary_y();

        //calculation driving force
        calcDrivingForce(*pedestrian, position_x_p, position_y_p, velocity_x_p, velocity_y_p, t_relax, flag_collision);

        pedestrian->force_x() += pedestrian->force_driving_x();
        pedestrian->force_y() += pedestrian->force_driving_y();

        //calculating the acceleration
        pedestrian->acceleration_x() = pedestrian->force_x(); //Newton's second law of motion considering unit mass based on the social force model
        pedestrian->acceleration_y() = pedestrian->force_y();

        //checking the acceleration of the pedestrian not to be greater than the maximum acceleration
        double acceleration = sqrt(pedestrian->acceleration_x()*pedestrian->acceleration_x() + pedestrian->acceleration_y()*pedestrian->acceleration_y());
        if (acceleration >= a_max)
        {
            pedestrian->acceleration_x() *= a_max/acceleration;
            pedestrian->acceleration_y() *= a_max/acceleration;
        }

        //calculating correction factors for the correction step
        double factor_corr_x = pedestrian->acceleration_x() - acceleration_x_p;
        double factor_corr_y = pedestrian->acceleration_y() - acceleration_y_p;

        //correction step
        corrector(*pedestrian, position_x_p, position_y_p, velocity_x_p, velocity_y_p, alpha_x_p, alpha_y_p, delta_t, delta_t2, factor_corr_x, factor_corr_y);

        //erase pedestrians which go out of the corridors from region B and D
        if (pedestrian->position_x() > boundaries["b5"][2] || pedestrian->position_y() > boundaries["b3"][3])
            activPedestrians.erase(pedestrian);
    }
}

#endif // Solver_H_
