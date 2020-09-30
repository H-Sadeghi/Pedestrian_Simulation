/*-------------------------------------------
Created by Hossein Sadeghi
Project: Simulator of the pedestrian dynamics
Date = 23.09.2020

class Pedestrian represents individual pedestrian
--------------------------------------------*/
#ifndef Pedestrian_H_
#define Pedestrian_H_

class Pedestrian
{
public:
	Pedestrian();

	Pedestrian(const int& id, const double& t_in, const double& x, const double& y, const double& v_x, const double& v_y, const double& a_x,
               const double& a_y, const double& v_des_x, const double& v_des_y, const int& groupId);

	Pedestrian(const int& id, const double& t_in, const double& x, const double& y, const double& v_des_x, const double& v_des_y, const int& groupId);

    //getter/setter functions
	int& id()
	{
	    return id_;
	}
	double& time_in()
	{
		return t_in_;
	}
	double& position_x()
	{
		return position_x_;
	}
	double& position_y()
	{
		return position_y_;
	}
	double& velocity_x()
	{
		return velocity_x_;
	}
	double& velocity_y()
	{
		return velocity_y_;
	}
	double& acceleration_x()
	{
		return acceleration_x_;
	}
	double& acceleration_y()
	{
		return acceleration_y_;
	}
	double& alpha_x()
	{
		return alpha_x_;
	}
	double& alpha_y()
	{
		return alpha_y_;
	}
	double& betta_x()
	{
		return betta_x_;
	}
	double& betta_y()
	{
		return betta_y_;
	}
	double& force_x()
	{
		return force_x_;
	}
	double& force_y()
	{
		return force_y_;
	}
	double& force_driving_x()
	{
		return force_d_x_;
	}
	double& force_driving_y()
	{
		return force_d_y_;
	}
	double& force_social_x()
	{
		return force_s_x_;
	}
	double& force_social_y()
	{
		return force_s_y_;
	}
	double& force_boundary_x()
	{
		return force_b_x_;
	}
	double& force_boundary_y()
	{
		return force_b_y_;
	}
	double& v_des_x()
	{
		return v_des_x_;
	}
	double& v_des_y()
	{
		return v_des_y_;
	}
	int& groupId()
	{
		return groupId_;
	}

private:
    int id_; //id of pedestrians for post-processing
    double t_in_; //time that the pedestrian enter the corridor
	double position_x_;
	double position_y_;
	double velocity_x_;
	double velocity_y_;
	double acceleration_x_;
	double acceleration_y_;
	double alpha_x_; //first derivative of acceleration
	double alpha_y_;
	double betta_x_; //second derivative of acceleration
	double betta_y_;
	double force_x_;
	double force_y_;
	double force_d_x_; //driving force
	double force_d_y_;
	double force_b_x_; //boundary force
	double force_b_y_;
	double force_s_x_; //social force
	double force_s_y_;
	double v_des_x_; //desired velocity in direction x for pedestrian entering from region C
	double v_des_y_; //desired velocity in direction y for pedestrian entering from region A
	int groupId_; //ID of the queue, the pedestrian belongs to before entering the system
};

#endif // Pedestrian_H_
