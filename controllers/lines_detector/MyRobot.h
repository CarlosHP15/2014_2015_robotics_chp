#ifndef MY_ROBOT_H_
#define MY_ROBOT_H_

/**
 * @file    MyRobot.h
 * @brief   Controller the robot with a spherical camera.
 *
 * @author  Carlos Hernandez Paz<100292793@alumnos.uc3m.es>
 * @date    2014-11
 */

#include <iostream>
#include <webots/DifferentialWheels.hpp>
#include<cmath>

using namespace std;
using namespace webots;

#define NUM_DISTANCE_SENSOR 2
#define DISTANCE_LIMIT      100
#define MAX_SPEED           100
#define DESIRED_ANGLE 45.002

class MyRobot : public DifferentialWheels {
public:
    // You may need to define your private methods or variables, like
    //  Constructors, helper functions, etc.

    /**
     * @brief Empty constructor of the class.
     */
    MyRobot();

    /**
     * @brief Destructor of the class.
     */
    ~MyRobot();

    /**
     * @brief Function with the logic of the controller.
     * @param Empty
     * @return Empty
     */
    void run();

    /**
     * @brief Function for converting bearing vector from compass to angle (in degrees).
     * @param in_vector Input vector with the values to convert.
     * @return The value in degrees.
     */
    double convert_bearing_to_degrees(const double* in_vector);

private:

    //variable _time_step initialization
    int _time_step;
    // velocities
    double _left_speed, _right_speed;

    // sensor _spherical camera
    Camera *_spherical_camera;

    // sensors compass
    Compass * _my_compass;
};

#endif

