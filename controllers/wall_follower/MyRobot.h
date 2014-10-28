/**
 * @file    Myrobot.h
 * @brief   Wall_Follower
 *
 * @author  Carlos Hernández Paz<100292793@alumnos.uc3m.es>
 * @date    2014-28-10
 */
#include <iostream>

#include <webots/DifferentialWheels.hpp>

using namespace std;
using namespace webots;

#define NUM_DISTANCE_SENSOR 4
#define DISTANCE_LIMIT      150
#define MAX_SPEED           50

class MyRobot : public DifferentialWheels {
    private:
        int _time_step;

        DistanceSensor * _distance_sensor[NUM_DISTANCE_SENSOR];
        double _left_speed, _right_speed;

        /**
         * @struct structure Mode
         * @brief represent a structure with some variables
         */
        enum Mode {
            STOP,
            FORWARD,
            TURN_LEFT,
            TURN_RIGHT,
            WALL_FOLLOWER,
            FOLLOWER_MAX

        };

        Mode _mode;

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
};
