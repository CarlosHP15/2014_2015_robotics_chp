/**
 * @file    MyRobot.h
 * @brief   Sensor
 *
 * @author  Carlos Hernández Paz<100292793@alumnos.uc3m.es>
 * @date    2014-28-10
 */

#include <iostream>
#include <cmath>
#include <webots/DifferentialWheels.hpp>

using namespace std;
using namespace webots;

#define MAX_SPEED       40
#define DESIRED_ANGLE   45
#define STOP 0
#define DISTANCEMAX 100
#define NUM 8

class MyRobot : public DifferentialWheels {
    private:
        int _time_step;

        Compass * _my_compass;
        double _left_speed, _right_speed;
        DistanceSensor * _distancesensor[NUM];


    public:
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
         */
        void run();

        /**
          * @brief An example for converting bearing vector from compass to angle (in degrees).
          * @param double in_vector
          * @return value of variable convert bearing to degrees
          */
        double convert_bearing_to_degrees(const double* in_vector);
};
