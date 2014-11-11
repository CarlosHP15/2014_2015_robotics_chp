/**
 * @file    MyRobot.cpp
 * @brief   Straight_Odometry.
 *
 * @author  Carlos Hernandez Paz <100292793@alumnos.uc3m.es>
 * @date    2014-11-11
 */

#include "MyRobot.h"
#include <iostream>
using namespace std;

//////////////////////////////////////////////

MyRobot::MyRobot() : DifferentialWheels()
{


    // init the value of time step to 64
    _time_step = 64;
    //init the value of the right and left encoders to zero
    encoderleft=0.0;
    encoderright=0.0;
    //init the values of the right and left speed to zero
    leftspeed=0.0;
    rightspeed=0.0;
    //init the value of the distance to zero
    distance=0.0;
    //enable the encoders
    enableEncoders(_time_step);
}

//////////////////////////////////////////////

MyRobot::~MyRobot()
{
    // the conders in the destructor are disable
    disableEncoders();

}

//////////////////////////////////////////////

void MyRobot::run()
{
    // Main loop:
    // Perform simulation steps of 64 milliseconds
    // and leave the loop when the simulation is over
    while (step(_time_step) != -1) {
        //taking the distance who take the robot
        //first condition
        if(distance<0.087){
            forward(0.087);
        }
        else{
            //this condition stop the robot when it reach the finish of the way
            leftspeed=0.0;
            rightspeed=0.0;
            //set the values of the speed specified in first or second condition
            setSpeed(leftspeed,rightspeed);
        }
        //print the values of the distance on the screen
        cout<<"distancia"<<distance<<endl;

    }
}

//////////////////////////////////////////////

void MyRobot::forward(double distance_requiered){

    //this condition makes the robot moves in a straight way
    //take both values from the left encoder and the right one
    // the resolution is equal to 1000 and tha radius of the wheel is 0.0825
    if(distance<0.087){
        encoderleft=getLeftEncoder();
        encoderright=getRightEncoder();
        distance=encoderleft/1000*0.0825;
        distance_requiered=distance_requiered+distance;
        //inside the first condition locate two more
        //this first condition makes the encoder goes left or right
        //depending on the value of the encoders
        if(encoderleft>encoderright){
            leftspeed=50;
            rightspeed=60;
        }
        else{
            leftspeed=60;
            rightspeed=50;
        }

        setSpeed(leftspeed,rightspeed);


    }

}


