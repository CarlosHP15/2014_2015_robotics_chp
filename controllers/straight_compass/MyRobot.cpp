/**
 * @file    MyRobot.cpp
 * @brief   Straight compass
 *
 * @author  Carlos Hernández Paz<100292793@alumnos.uc3m.es>
 * @date    2014-28-10
 */


#include "MyRobot.h"

//////////////////////////////////////////////
//Definition of the constructor MyRobot where initialize the parameters of this program
MyRobot::MyRobot() : DifferentialWheels()
{
    _time_step = 64;

    _left_speed = 0;
    _right_speed = 0;

    // Get and enable the compass device
    _my_compass = getCompass("compass");
    _my_compass->enable(_time_step);
}


//////////////////////////////////////////////
//destructor of MyRobot Class who disable the variable _my_compass
MyRobot::~MyRobot()
{
    _my_compass->disable();
}

//////////////////////////////////////////////
//function who start the move of the robot taking a straight way,
//and helped with the convert bearing to degrees function
void MyRobot::run()
{
    int timer=340;
    double compass_angle;


    while (step(_time_step) != -1) {
        timer --;
        // Read the compass
        const double *compass_val = _my_compass->getValues();

        // Convert compass bearing vector to angle, in degrees
        compass_angle = convert_bearing_to_degrees(compass_val);

        // Print sensor values to console
        cout << "Compass angle (degrees): " << compass_angle << endl;

        // Simple bang-bang control
        if (compass_angle < (DESIRED_ANGLE - 2)) {
            // Turn right
            _left_speed = MAX_SPEED;
            _right_speed = MAX_SPEED - 15;
        }
        else {
            if (compass_angle > (DESIRED_ANGLE + 2)) {
                // Turn left
                _left_speed = MAX_SPEED - 15;
                _right_speed = MAX_SPEED;
            }
            else {
                // Move straight forward
                _left_speed = MAX_SPEED;
                _right_speed = MAX_SPEED;
            }
            if(timer<0){
                _left_speed=STOP;
                _right_speed=STOP;
                setSpeed(_left_speed,_right_speed);
            }
        }
        // Set the motor speeds
        setSpeed(_left_speed, _right_speed);
    }
}

//////////////////////////////////////////////

//this function take the curse of the Robot and make a operation to convert it in degrees,
//here we use parameters like M_PI, variables of directory cmath
double MyRobot::convert_bearing_to_degrees(const double* in_vector)
{
    double rad = atan2(in_vector[0], in_vector[2]);
    double deg = rad * (180.0 / M_PI);

    return deg;
}

//////////////////////////////////////////////
