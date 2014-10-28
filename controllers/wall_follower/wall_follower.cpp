/**
 * @file    wall_follower.cpp
 * @brief   Wall_Follower
 *
 * @author  Carlos Hernández Paz<100292793@alumnos.uc3m.es>
 * @date    2014-28-10
 */
#include "MyRobot.h"

// This is the main program of my controller.
// It creates an objet of class Robot, launches its
// function(s) and destroys it at the end of the execution.
// The arguments of the main function can be specified by the
// "controllerArgs" field of the Robot node

int main(int argc, char **argv)
{
    MyRobot* my_robot = new MyRobot();

    my_robot->run();

    delete my_robot;

    return 0;
}
