/**
 * @file    MyRobot.h
 * @brief   Straight_Odometry.
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
#define MAX_SPEED 100
//#define DESIRED_ANGLE 4.0


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
     * @brief
     * @param it takes the distance_requiered of the encoders
     * @return Empty
     */
     void forward(double distance_requiered);
    /**
     * @brief Empty constructor of the class.
     */
    MyRobot();

    /**
     * @brief Destructor of the class.
     */
    ~MyRobot();

    /**
     * @brief User defined function for initializing and running the template class.
     * @param
     * @return
     */
    void run();
};
