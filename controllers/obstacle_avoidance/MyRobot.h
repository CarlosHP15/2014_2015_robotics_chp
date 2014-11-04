/**
 * @file    main_template.cpp
 * @brief   A template for webots projects.
 *
 * @author  Carlos Hernandez Paz <100292793@alumnos.uc3m.es>
 * @date    2014-11-04
 */

#include <iostream>
#include <cmath>

#include <webots/DifferentialWheels.hpp>

using namespace std;
using namespace webots;

//definition of constant variables

#define NUM_DISTANCE_SENSOR 16
#define DISTANCE_LIMIT      60
#define MAX_SPEED           30
#define DESIRED_ANGLE 45.002

//definition of the class MyRobot

class MyRobot : public DifferentialWheels {

    private:
        int _time_step;

        Compass * _my_compass;
        DistanceSensor * _distance_sensor[NUM_DISTANCE_SENSOR];
        double _left_speed, _right_speed;

//struct of type enum which takes all modes

        enum Mode {
            STOP,
            FORWARD,
            TURN_LEFT,
            TURN_RIGHT,
            FOLLOWER_MAX,
            CORNER_RIGHT,
            COMPASS,
            LESS_LEFT,
            LESS_RIGHT,
            TURN

        };

        Mode _mode;

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
