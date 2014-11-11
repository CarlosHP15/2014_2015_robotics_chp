/**
 * @file    MyRobot.h
 * @brief   Obstacle_Odometry.
 *
 * @author  Carlos Hernandez Paz <100292793@alumnos.uc3m.es>
 * @date    2014-11-11
 */



#include<iostream>
#include <cmath>



#include <webots/DifferentialWheels.hpp>

// All the webots classes are defined in the "webots" namespace
using namespace webots;
using namespace std;

// You may need to define some macros, only if it is necessary, like
#define MAX_SPEED 45



class MyRobot : public DifferentialWheels {
private:


    int _time_step;
    double encoderleft;
    double encoderright;
    double leftspeed;
    double rightspeed;
    double distance;


public:
    /**
     * @brief Function who moves forward the robot using encoders.
     * @param Distance requiered.
     * @return Empty.
     */
    void forward(double distance_requiered);
    /**
     * @brief Function who turn right the robot.
     * @param Distance requiered.
     * @return Empty.
     */
    void Turnright (double distance_requiered);
    /**
     * @brief Function who turn left the robot.
     * @param Distance requiered.
     * @return Empty.
     */
    void Turnleft (double distance_requiered);
    /**
     * @brief Moves the robot in a straight line.
     * @param Distance requiered.
     * @return Empty.
     */
    void straight(double distance_requiered);

    /**
     * @brief Empty constructor of the class.
     * @param
     * @return
     */
    MyRobot();

    /**
     * @brief Destructor of the class.
     * @param
     * @return
     */
    ~MyRobot();

    /**
     * @brief User defined function for initializing and running the template class.
     * @param
     * @return
     */
    void run();
};
