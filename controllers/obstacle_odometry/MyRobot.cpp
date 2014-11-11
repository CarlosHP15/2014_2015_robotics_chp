/**
 * @file    MyRobot.cpp
 * @brief   Obstacle_Odometry.
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
    // Need to specify the time_step with the value 64.
    _time_step = 64;
    //initialize the encoders with value 0.0.
    encoderleft=0.0;
    encoderright=0.0;
    //define the initial speed to 0.0.
    leftspeed=0.0;
    rightspeed=0.0;
    //initial distance 0.0.
    distance=0.0;
    //get enable the encoders
    enableEncoders(_time_step);
}

//////////////////////////////////////////////

MyRobot::~MyRobot()
{
    // Enter here exit cleanup code such as
    disableEncoders();

}

//////////////////////////////////////////////

void MyRobot::run()
{

    // Loop who Perform simulation steps of 64 milliseconds
    // and leave the loop when the simulation is over

    while (step(_time_step) != -1) {

        //functions of the encoder to get their values

        encoderleft=getLeftEncoder();
        encoderright=getRightEncoder();

        //with the parametres of the wheels and encoders,implement them in the line
        //been 0.0825 the size of the wheel

        distance += encoderleft/1000*0.0825;

        //first condition, taking the distances of the robot
        //take the robot an straight way but with the direction of 45º
        //this angle is followed by the robot until the obstacle appeared

        if((distance<1.8)||((distance>7.5)&&(distance<41))){
            forward(distance);}

        else{
            //with this second condition the robot turn right in the rank of distances

            if((distance>1.8)&&(distance<2.36)){
                Turnright(distance);
            }
            else{
                //in the third condition the robot takes a straight way

                if((distance>2.36)&&(distance<7)){
                    straight(distance);
                }
                else{
                    //in this fourth condition the robot can turn left, when the obstacle is overcomed

                    if((distance>7)&&(distance<7.5)){
                        Turnleft(distance);
                    }

                    else{
                        //this is the last condition and can stop the robot, when the way is finished
                        leftspeed=0.0;
                        rightspeed=0.0;
                        setSpeed(leftspeed,rightspeed);

                    }
                }
            }
        }
        //print the distance covered by the robot

        cout<<"distancia"<<distance<<endl;

    }
}

//////////////////////////////////////////////

void MyRobot::forward(double distance_requiered){

    //condition who allow the robot take a straight way
    //switching the values of each encoder

    if(encoderleft>encoderright){
        leftspeed=50;
        rightspeed=60;
    }
    else{
        leftspeed=60;
        rightspeed=50;
    }
    //function who put the velocities specified in the wheels of the robot

    setSpeed(leftspeed,rightspeed);

}

///////////////////////////////////////////////

void MyRobot::Turnright(double distance_requiered){

    //set the left speed and the right one in order to turn the robot right

    leftspeed=MAX_SPEED/1;
    rightspeed=0;
    setSpeed(leftspeed,rightspeed);

}

////////////////////////////////////////////////

void MyRobot::straight(double distance_requiered){

    //set the left and the right speed to MAX SPEED,
    //to take a straight line with any other condition

    leftspeed=MAX_SPEED;
    rightspeed=MAX_SPEED;
    setSpeed(leftspeed,rightspeed);
}

////////////////////////////////////////////////

void MyRobot::Turnleft(double distance_requiered){

    leftspeed=0;
    rightspeed=MAX_SPEED/1;
    setSpeed(leftspeed,rightspeed);

}

