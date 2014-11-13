/**
 * @file    MyRobot.cpp
 * @brief   Controll the robot with a spherical cameras.
 *
 * @author  Carlos Hernandez Paz<100292793@alumnos.uc3m.es>
 * @date    2014-11
 */

#include "MyRobot.h"

//////////////////////////////////////////////

MyRobot::MyRobot() : DifferentialWheels()
{
    // init default values
    _time_step = 64;
    //init velocities of each wheel
    _left_speed = 0;
    _right_speed = 0;
    //Get and enable the spherical camera proccesses
    _spherical_camera = getCamera("camera_s");
    _spherical_camera->enable(_time_step);

    //Get and enable the compass sensor
    _my_compass = getCompass("compass");
    _my_compass->enable(_time_step);

}

//////////////////////////////////////////////

MyRobot::~MyRobot()
{
    //destructor of the class Myrobot
    _spherical_camera->disable();
    // disable devices
    _my_compass->disable();
}

//////////////////////////////////////////////

void MyRobot::run()
{
    //init the variable used by the compass
    double compass_angle;
    //init a variable sum and put inside the value zero
    int sum = 0;
    //init all kind of colours who can take the image of the spherical camera
    unsigned char green = 0, red = 0, blue = 0;
    //init the percentage of yellow
    double percentage_yellow = 0.0;

    // get size of images for spherical camera
    int image_width_s = _spherical_camera->getWidth();
    int image_height_s = _spherical_camera->getHeight();

    cout << "Size of spherical camera image: " << image_width_s << ", " << image_height_s << endl;

    //loop until robot disconect
    while (step(_time_step) != -1) {

        //init inside the loop the value of sum to zero
        sum = 0;
        // get current image from forward camera
        const unsigned char *image_s= _spherical_camera->getImage();
        // count number of pixels that are yellow in the screen
        //the pixel values goes until 255, from 245 for all colour components
        for (int x = 0; x < image_width_s; x++) {
            for (int y = 0; y < image_height_s; y++) {
                green = _spherical_camera->imageGetGreen(image_s, image_width_s, x, y);

                red = _spherical_camera->imageGetRed(image_s, image_width_s, x, y);

                blue = _spherical_camera->imageGetBlue(image_s, image_width_s, x, y);
                //depending on the RGB rank the values of each color should change
                //in this case a completely yellow screen reach when green is iqual to 255,red to 255 and finally blue zero
                //but the spherical camera screen does not caught only yellow,
                //for this reason the rank of the values are less restrictive
                if ((green > 245) && (red > 245) && (blue <51)) {
                    sum = sum + 1;
                }
            }
        }

        //here percentage yellow takes the width and the height of the image to discover his percentage
        percentage_yellow = (sum / (float) (image_width_s * image_height_s)) * 100;
        cout << "Percentage of yellow in spherical camera image: " << percentage_yellow << endl;

        //if the percentage of yellow is higher than 0.25 the screen put the code: yellow line detected
        if(percentage_yellow>0.25){
            cout<<"linea amarilla detectada"<<endl;

        }
        else{
            cout<<"linea amarilla no detectada"<<endl;
        }
        //now the robot is following a straight way with the compass
        //Usefull to detect the other yellow line
        const double *compass_val = _my_compass->getValues();

        // convert compass bearing vector to angle, in degrees
        compass_angle = convert_bearing_to_degrees(compass_val);

        // print sensor values to console
        cout << "Compass angle (degrees): " << compass_angle << endl;

        if (compass_angle < (DESIRED_ANGLE - 2)) {
            // turn right
            _left_speed = MAX_SPEED;
            _right_speed = MAX_SPEED - 15;
        }
        else {
            if (compass_angle > (DESIRED_ANGLE + 2)) {
                // turn left
                _left_speed = MAX_SPEED - 15;
                _right_speed = MAX_SPEED;
            }
            else {
                // move straight forward
                _left_speed = MAX_SPEED;
                _right_speed = MAX_SPEED;
            }
        }
        // set the motor speeds
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
