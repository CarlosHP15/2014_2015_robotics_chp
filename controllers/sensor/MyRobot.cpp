/**
 * @file    MyRobot.cpp
 * @brief   Sensor
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

       _distancesensor[0]=getDistanceSensor("ds0");
       _distancesensor[0]->enable(_time_step);
       _distancesensor[1] = getDistanceSensor("ds1");
       _distancesensor[1]->enable(_time_step);
       _distancesensor[2]=getDistanceSensor("ds2");
       _distancesensor[2]->enable(_time_step);
       _distancesensor[3]=getDistanceSensor("ds3");
       _distancesensor[3]->enable(_time_step);
       _distancesensor[4]=getDistanceSensor("ds12");
       _distancesensor[4]->enable(_time_step);
       _distancesensor[5]=getDistanceSensor("ds13");
       _distancesensor[5]->enable(_time_step);
       _distancesensor[6]=getDistanceSensor("ds14");
       _distancesensor[6]->enable(_time_step);
       _distancesensor[7]=getDistanceSensor("ds15");
       _distancesensor[7]->enable(_time_step);

}


//////////////////////////////////////////////
//destructor of MyRobot Class who disable the variable _my_compass
MyRobot::~MyRobot()
{
    _my_compass->disable();

    for (int i=0; i<NUM; i++) {
        _distancesensor[i]->disable();
       }
}

//////////////////////////////////////////////
//function who start the move of the robot taking a straight way,
//and helped with the convert bearing to degrees function and sensor distance
void MyRobot::run()
{

    double compass_angle;
    double ir0_val=0.0,ir1_val=0.0,ir2_val=0.0,ir3_val=0.0,ir4_val=0.0,ir5_val=0.0,ir6_val=0.0,ir7_val=0.0;

    while (step(_time_step) != -1) {

        // Read the compass
        const double *compass_val = _my_compass->getValues();
	//Read the _distancesensor
        ir1_val=_distancesensor[1]->getValue();
        ir2_val=_distancesensor[2]->getValue();
        ir3_val=_distancesensor[3]->getValue();
        ir4_val=_distancesensor[4]->getValue();
        ir5_val=_distancesensor[5]->getValue();
        ir6_val=_distancesensor[6]->getValue();
        ir7_val=_distancesensor[7]->getValue();
        ir0_val=_distancesensor[0]->getValue();


        // Convert compass bearing vector to angle, in degrees
        compass_angle = convert_bearing_to_degrees(compass_val);

        // Print sensor values to console
        cout << "Compass angle (degrees): " << compass_angle << endl;
        cout<<"ds0:"<<ir0_val<<"\tds1:"<<ir1_val<<endl;
        cout<<"ds2:"<<ir2_val<<"\tds3:"<<ir3_val<<endl;
        cout<<"ds4:"<<ir4_val<<"\tds5:"<<ir5_val<<endl;
        cout<<"ds6:"<<ir6_val<<"\tds7:"<<ir7_val<<endl;

        // Simple bang-bang control


        if (compass_angle < (DESIRED_ANGLE - 2)) {
            // Turn right
            _left_speed = MAX_SPEED;
            _right_speed = MAX_SPEED - 15;
        }
        else{
        if (compass_angle > (DESIRED_ANGLE + 2)) {
                // Turn left
                _left_speed = MAX_SPEED - 15;
                _right_speed = MAX_SPEED;
            }
        else{
                // Move straight forward
                _left_speed = MAX_SPEED;
                _right_speed = MAX_SPEED;
            }
        if((ir0_val>DISTANCEMAX)||(ir1_val>DISTANCEMAX)||(ir2_val>DISTANCEMAX)||(ir3_val>DISTANCEMAX)||(ir4_val>DISTANCEMAX)||(ir5_val>DISTANCEMAX)||(ir6_val>DISTANCEMAX)||(ir7_val>DISTANCEMAX)){

               _left_speed=0;
               _right_speed=0;
               setSpeed(_left_speed,_right_speed);
           }
        }
        // Set the motor speeds
        setSpeed(_left_speed, _right_speed);
    }
}
//////////////////////////////////////////////
double MyRobot::convert_bearing_to_degrees(const double* in_vector)
{
    double rad = atan2(in_vector[0], in_vector[2]);
    double deg = rad * (180.0 / M_PI);

    return deg;
}

//////////////////////////////////////////////
