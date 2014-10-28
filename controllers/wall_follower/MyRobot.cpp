/**
 * @file    Myrobot.cpp
 * @brief   Wall_Follower
 *
 * @author  Carlos Hernández Paz<100292793@alumnos.uc3m.es>
 * @date    2014-28-10
 */

#include "MyRobot.h"

//////////////////////////////////////////////

MyRobot::MyRobot() : DifferentialWheels()//initializacion of empty constructor
{
    _time_step = 64;

    _left_speed = 0;
    _right_speed = 0;

    _mode = FORWARD;

    //get and enable of each sensor
    _distance_sensor[0] = getDistanceSensor("ds1");
    _distance_sensor[0]->enable(_time_step);
    _distance_sensor[1] = getDistanceSensor("ds2");
    _distance_sensor[1]->enable(_time_step);
    _distance_sensor[2] = getDistanceSensor("ds13");
    _distance_sensor[2]->enable(_time_step);
    _distance_sensor[3]=getDistanceSensor("ds14");
    _distance_sensor[3]->enable(_time_step);
}

//////////////////////////////////////////////

MyRobot::~MyRobot()//destructor of the class MyRobot
{
    //loop use to disable each sensor
    for (int i=0; i<NUM_DISTANCE_SENSOR; i++) {
        _distance_sensor[i]->disable();
    }
}

//////////////////////////////////////////////

void MyRobot::run()
{
    //initializacion of each variable with value 0.0

    double ir1_val = 0.0, ir2_val = 0.0, ir13_val = 0.0, ir14_val=0.0;

    //loop who don't break until the variable _time_step is -1

    while (step(_time_step) != -1) {

        // Read the sensors and call function getValue
        //each function works sending the value of each sensor to variable iri_val.

        ir1_val = _distance_sensor[0]->getValue();
        ir2_val = _distance_sensor[1]->getValue();
        ir13_val = _distance_sensor[2]->getValue();
        ir14_val = _distance_sensor[3]->getValue();

        //print value of variable iri_val

        cout<<"ds0:"<<ir1_val<<"\tds1:"<<ir2_val<<endl;
        cout<<"ds2:"<<ir13_val<<"\tds3:"<<ir14_val<<endl;


        // Control logic of the robot using nested if's

        if (_mode == FORWARD) {
            // Move forward without any condition
            //if the variables comply the "if condition"the do the next instruction
            //Turn right makes robot stay near of the wall without touching,
            //is the instruction who makes the robot change the mode to wall following
            if ((ir1_val > DISTANCE_LIMIT) || (ir2_val > DISTANCE_LIMIT)) {
                _mode =TURN_RIGHT;
                cout << "Mode " << TURN_RIGHT << ": Wall following mode activated" << endl;}
                                }
        else {
            // Wall following
            //instruction who helps the robot not to crash with the wall
            if ((ir13_val > DISTANCE_LIMIT) || (ir14_val > DISTANCE_LIMIT)) {
                _mode = WALL_FOLLOWER;
                cout << "Backing up and turning left." << endl;
            }
            else {
                if(ir13_val>DISTANCE_LIMIT -75){
                    _mode=TURN_LEFT;
                    cout<<"Turning left"<<endl;}
                else{
                    if ((ir14_val > DISTANCE_LIMIT)&&(ir1_val>DISTANCE_LIMIT)) {
                    _mode = FOLLOWER_MAX;
                    cout << "Corner" << endl;}
                    else {
                        if ((ir13_val < DISTANCE_LIMIT +75)||(ir14_val>DISTANCE_LIMIT +75)) {
                        _mode = TURN_RIGHT;
                        cout << "Turning right." << endl;}
                        else {
                        _mode = FORWARD;
                        cout << "Moving forward." << endl;}
                    }
                }
            }
        }

        // Send actuators commands according to the mode
        //The mode is specificied in the MyRobot.h
        switch (_mode){

        //Stop the speed of the robot sending two values of zero to each wheel
            case STOP:
                _left_speed = 0;
                _right_speed = 0;
                break;
        //The robot move forward sending two values of max speed to each wheel
            case FORWARD:
                _left_speed = MAX_SPEED;
                _right_speed = MAX_SPEED;
                break;
        //The right wheel have a higher speed than the left one, to turn in the direction
            case TURN_LEFT:
                _left_speed = MAX_SPEED / 1.15;
                _right_speed = MAX_SPEED;
                break;
        //The left wheel have a higher speed than the right one, to turn in the direction
            case TURN_RIGHT:
                _left_speed = MAX_SPEED;
                _right_speed = MAX_SPEED / 1.05;
                break;
        //just turn in a slow speed,with less angle
            case WALL_FOLLOWER:
                _left_speed = -MAX_SPEED  /3.0;
                _right_speed = -MAX_SPEED /20.0;
                break;
        //this mode is use to turn faster, with a higher angle
            case FOLLOWER_MAX:
                 _left_speed=-MAX_SPEED/2.0;
                 _right_speed=-MAX_SPEED/30.0;
            default:
                break;
        }

        // Set the motor speeds
        setSpeed(_left_speed, _right_speed);
    }
}

//////////////////////////////////////////////
