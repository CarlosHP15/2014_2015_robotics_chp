/**
 * @file    MyRobot.cpp
 * @brief   Controller for the forward camera of the robot.
 *
 * @author  Carlos Hernandez Paz <100292793@alumnos.uc3m.es>
 * @date    2014-11
 */

#include "MyRobot.h"

//////////////////////////////////////////////

MyRobot::MyRobot() : DifferentialWheels()
{
    // init default values
    _time_step = 64;

    _left_speed = 0;
    _right_speed = 0;

    // get distance sensor array and enable each one
    _forward_camera = getCamera("camera_f");
    _forward_camera->enable(_time_step);
    /* _spherical_camera = getCamera("camera_s");
    _spherical_camera->enable(_time_step);*/
}

//////////////////////////////////////////////

MyRobot::~MyRobot()
{
    // disable devices
    _forward_camera->disable();
    //_spherical_camera->disable();
}

//////////////////////////////////////////////

void MyRobot::run()
{
    int sum = 0;
    unsigned char green = 0, red = 0, blue = 0;
    double percentage_white = 0.0;

    // get size of images for forward camera

    int image_width_f = _forward_camera->getWidth();
    int image_height_f = _forward_camera->getHeight();
    cout << "Size of forward camera image: " << image_width_f << ", " <<  image_height_f << endl;

    /* // get size of images for spherical camera

    int image_width_s = _spherical_camera->getWidth();
    int image_height_s = _spherical_camera->getHeight();
    cout << "Size of spherical camera image: " << image_width_s << ", " << image_height_s << endl;*/

    while (step(_time_step) != -1) {
        sum = 0;

        // get current image from forward camera
        const unsigned char *image_f = _forward_camera->getImage();

        // count number of pixels that are white
        // (here assumed to have pixel value > 245 out of 255 for all color components)
        for (int x = 0; x < image_width_f; x++) {
            for (int y = 0; y < image_height_f; y++) {
                green = _forward_camera->imageGetGreen(image_f, image_width_f, x, y);
                red = _forward_camera->imageGetRed(image_f, image_width_f, x, y);
                blue = _forward_camera->imageGetBlue(image_f, image_width_f, x, y);

                if ((green > 226) && (red > 226) && (blue > 226)) {
                    sum = sum + 1;
                }
            }
        }

        percentage_white = (sum / (float) (image_width_f * image_height_f)) * 100;
        cout << "Percentage of white in forward camera image: " << percentage_white << endl;

        //turn around slowly
        _left_speed = 5;
        _right_speed = -5;

        //a mayor numero conseguido mas blanco detecta

        if(percentage_white>87){
            cout<<"pared delante de robot"<<endl;
        }

        else{

            cout<<"no pared delante de robot"<<endl;

        }
        // set the motor speeds
        setSpeed(_left_speed, _right_speed);
    }
}

//////////////////////////////////////////////
