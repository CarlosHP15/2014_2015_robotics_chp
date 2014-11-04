/**
 * @file    main_template.cpp
 * @brief   A template for webots projects.
 *
 * @author  Carlos Hernandez Paz <100292793@alumnos.uc3m.es>
 * @date    2014-11-04
 */

#include "MyRobot.h"

//////////////////////////////////////////////

//Definition of the constructor MyRobot where initialize the parameters of this program
MyRobot::MyRobot() : DifferentialWheels()
{

    _time_step = 64;

    //set both speed to 0

    _left_speed = 0;
    _right_speed = 0;


    //initial movement
    _mode = COMPASS;

    //Get and enable distances sensors

    _distance_sensor[0] = getDistanceSensor("ds0");
    _distance_sensor[0]->enable(_time_step);
    _distance_sensor[1] = getDistanceSensor("ds1");
    _distance_sensor[1]->enable(_time_step);
    _distance_sensor[2] = getDistanceSensor("ds2");
    _distance_sensor[2]->enable(_time_step);
    _distance_sensor[3] = getDistanceSensor("ds3");
    _distance_sensor[3]->enable(_time_step);
    _distance_sensor[4] = getDistanceSensor("ds4");
    _distance_sensor[4]->enable(_time_step);
    _distance_sensor[5] = getDistanceSensor("ds5");
    _distance_sensor[5]->enable(_time_step);
    _distance_sensor[6] = getDistanceSensor("ds6");
    _distance_sensor[6]->enable(_time_step);
    _distance_sensor[7] = getDistanceSensor("ds7");
    _distance_sensor[7]->enable(_time_step);
    _distance_sensor[8] = getDistanceSensor("ds8");
    _distance_sensor[8]->enable(_time_step);
    _distance_sensor[9] = getDistanceSensor("ds9");
    _distance_sensor[9]->enable(_time_step);
    _distance_sensor[10] = getDistanceSensor("ds10");
    _distance_sensor[10]->enable(_time_step);
    _distance_sensor[11] = getDistanceSensor("ds11");
    _distance_sensor[11]->enable(_time_step);
    _distance_sensor[12] = getDistanceSensor("ds12");
    _distance_sensor[12]->enable(_time_step);
    _distance_sensor[13] = getDistanceSensor("ds13");
    _distance_sensor[13]->enable(_time_step);
    _distance_sensor[14] = getDistanceSensor("ds14");
    _distance_sensor[14]->enable(_time_step);
    _distance_sensor[15] = getDistanceSensor("ds15");
    _distance_sensor[15]->enable(_time_step);

    // Get and enable the compass device
    _my_compass = getCompass("compass");
    _my_compass->enable(_time_step);
}

//////////////////////////////////////////////

//destructor of MyRobot Class who disable the variable _my_compass
MyRobot::~MyRobot()
{
    for (int i=0; i<NUM_DISTANCE_SENSOR; i++) {
        _distance_sensor[i]->disable();
    }
    _my_compass->disable();
}

//////////////////////////////////////////////

//function who start the move of the robot taking a straight way qith the compass device,
//and helped with the convert bearing to degrees function and sensor distance to reach the end
void MyRobot::run()
{
    //empty declaration of each value of the sensors
    double ir0_val = 0.0, ir1_val = 0.0,ir2_val=0.0,ir3_val=0.0, ir4_val = 0.0, ir5_val = 0.0,ir6_val=0.0,ir7_val=0.0, ir8_val = 0.0, ir9_val = 0.0,ir10_val=0.0,ir11_val=0.0, ir12_val = 0.0, ir13_val = 0.0,ir14_val=0.0,ir15_val=0.0;
    //declaration of the compass variable
    double compass_angle;

    //loop who finsih when the time step get the value of -1
    while (step(_time_step) != -1) {

        // Read the compass
        const double *compass_val = _my_compass->getValues();

        // Convert compass bearing vector to angle, in degrees
        compass_angle = convert_bearing_to_degrees(compass_val);

        //print the compass value
        cout << "Compass angle (degrees): " << compass_angle << endl;

        // Read the sensors
        ir0_val= _distance_sensor[0]->getValue();
        ir1_val = _distance_sensor[1]->getValue();
        ir2_val = _distance_sensor[2]->getValue();
        ir3_val= _distance_sensor[3]->getValue();
        ir4_val = _distance_sensor[4]->getValue();
        ir5_val = _distance_sensor[5]->getValue();
        ir6_val= _distance_sensor[6]->getValue();
        ir7_val = _distance_sensor[7]->getValue();
        ir8_val = _distance_sensor[8]->getValue();
        ir9_val= _distance_sensor[9]->getValue();
        ir10_val = _distance_sensor[10]->getValue();
        ir11_val = _distance_sensor[11]->getValue();
        ir12_val= _distance_sensor[12]->getValue();
        ir13_val = _distance_sensor[13]->getValue();
        ir14_val = _distance_sensor[14]->getValue();
        ir15_val = _distance_sensor[15]->getValue();

        // Print sensor values to console
        cout << "Compass angle (degrees): " << compass_angle << endl;
        cout<<"ds0:"<<ir0_val<<"\tds1:"<<ir1_val<<endl;
        cout<<"ds2:"<<ir2_val<<"\tds3:"<<ir3_val<<endl;
        cout<<"ds4:"<<ir4_val<<"\tds5:"<<ir5_val<<endl;
        cout<<"ds6:"<<ir6_val<<"\tds7:"<<ir7_val<<endl;
        cout<<"ds8:"<<ir8_val<<"\tds9:"<<ir9_val<<endl;
        cout<<"ds10:"<<ir10_val<<"\tds11:"<<ir11_val<<endl;
        cout<<"ds12:"<<ir12_val<<"\tds13:"<<ir13_val<<endl;
        cout<<"ds14:"<<ir14_val<<"\tds15:"<<ir15_val<<endl;

        // Control logic of the robot


        //este if se encarga de conocer si hay algun sensor activo, en caso de que el robot no este,
        //proximo a ningun objeto, seguira el camino atendiendo a la brujula, de lo contrario entraría dentro del if
        if((ir0_val>30)||(ir1_val>30)||(ir2_val>30)||(ir3_val>30)||(ir4_val>30)||(ir5_val>30)||(ir6_val>30)||(ir7_val>30)||(ir8_val>30)||(ir9_val>30)||(ir10_val>30)||(ir11_val>30)||(ir12_val>30)||(ir13_val>30)||(ir14_val>30)||(ir15_val>30)){

        //En este caso si los sensores delantero-laterales estan activos
        //el robot retrocederá para evitar colision y mientras se orientará a la izquierda
        if((ir15_val>DISTANCE_LIMIT-40)&&((ir14_val>DISTANCE_LIMIT-50)&&(ir13_val>DISTANCE_LIMIT-60))){
            _mode=FOLLOWER_MAX;
            cout<<"Turn left the robot"<<endl;}

        else{
            //en este caso a contrario que en el anterior si se activan los sensores delantero-laterales
            //el robot retrocedera y se se orientará hacia la izquierda
            if(((ir1_val>DISTANCE_LIMIT-50)&&(ir2_val>DISTANCE_LIMIT-60)&&(ir0_val>DISTANCE_LIMIT-40))){
                _mode=CORNER_RIGHT;
                cout<<"Turn right the robot"<<endl;}

            else{
                //en este otro caso el robot ante la activacion de los sensores laterales,
                //tendera hacia la izquierda continuando con su movimiento
                if(((ir11_val>DISTANCE_LIMIT-40)&&(ir12_val>DISTANCE_LIMIT-30))||(ir13_val>DISTANCE_LIMIT-30)){
                    _mode=TURN_LEFT;
                    cout<<"turn left the robot,less grade of turn left "<<endl;}

                else{
                    //en esta ocasion girara el robot hacia la derecha progresivamente,
                    //avisado por los sensores laterales
                    if(((ir4_val>DISTANCE_LIMIT-60)&&(ir3_val>DISTANCE_LIMIT-40))||(ir2_val>DISTANCE_LIMIT)){
                        _mode=TURN_RIGHT;
                        cout<<"Turn right the robot, less grade of turn right"<<endl;}

                    else{
                        //en caso de que el robot se este desviando en exceso de la trayectoria,
                        //esta declaracion ayuda a que se vuelva a pegar a la pared
                        if((ir11_val>DISTANCE_LIMIT)&&(ir10_val>DISTANCE_LIMIT)&&(ir9_val>DISTANCE_LIMIT-30)){
                            _mode=LESS_RIGHT;
                            cout<<"the route of the robot less right"<<endl;}

                        else{
                            //en caso de que el robot se este desviando en exceso de la trayectoria,
                            //esta declaracion ayuda a que se vuelva a pegar a la pared
                            if((ir4_val>DISTANCE_LIMIT)&&(ir5_val>DISTANCE_LIMIT)&&(ir6_val>DISTANCE_LIMIT-30)){
                                _mode=LESS_LEFT;
                                cout<<"the route of the robot less left"<<endl;}

                            else{
                                //Este if utiliza los sensores delanteros y lee en el entorno si existe un hueco,
                                //donde poder introducirse
                                if(((ir15_val>DISTANCE_LIMIT-30)||(ir0_val>DISTANCE_LIMIT-30))&&(ir4_val>DISTANCE_LIMIT-60)){
                                    _mode=CORNER_RIGHT;
                                    cout<<"Turn corner right"<<endl;}

                                else{
                                    //Este if es el encargado de buscar un hueco en el entorno si existe,
                                    //a contrario que la anterior el hueco que busca este if es el del lado opuesto
                                    if(((ir15_val>DISTANCE_LIMIT-30)||(ir0_val>DISTANCE_LIMIT-30))&&(ir11_val>DISTANCE_LIMIT-60)){
                                        _mode=FOLLOWER_MAX;
                                        cout<<"Turn corner left"<<endl;}

                                    else{
                                        //opcion para seguir la pared y encontrar la ruta ayudado por el resto de declaraciones
                                        if((ir11_val>DISTANCE_LIMIT-60)&&(ir12_val<DISTANCE_LIMIT)){
                                            _mode=TURN;
                                            cout<<"follow the wall"<<endl;}
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
        else{
            _mode=COMPASS;
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

            _left_speed = MAX_SPEED / 1.45;
            _right_speed = MAX_SPEED;
            break;

            //The left wheel have a higher speed than the right one, to turn in the direction
        case TURN_RIGHT:

            _left_speed = MAX_SPEED;
            _right_speed = MAX_SPEED / 2.05;
            break;

            //this mode is use to turn faster, with a higher angle
        case FOLLOWER_MAX:
            _left_speed=-MAX_SPEED/1.0;
            _right_speed=-MAX_SPEED/20.0;
            break;

            //this mode is use to turn right faster, with a higher angle
        case CORNER_RIGHT:
            _left_speed=-MAX_SPEED/20.0;
            _right_speed= -MAX_SPEED/1.0;
            break;

            //this mode turn right the robot progressive
        case LESS_RIGHT:
            _left_speed=MAX_SPEED;
            _right_speed=MAX_SPEED/1.15;
            break;

            //this mode turn left the robot progressive
        case LESS_LEFT:
            _left_speed=MAX_SPEED/1.15;
            _right_speed=MAX_SPEED;
            break;

            //this mode help us to reach the end
        case TURN:
            _left_speed=MAX_SPEED;
            _right_speed=MAX_SPEED/10;
            break;

            //this mode help us to stright the robot with a 45 angle
        case COMPASS:
            if (compass_angle < (DESIRED_ANGLE - 2)) {
                // Turn right
                _left_speed = MAX_SPEED;
                _right_speed = MAX_SPEED - 15;
                cout<<"aqui"<<endl;
            }
            else {
                if (compass_angle > (DESIRED_ANGLE + 2)) {
                    // Turn left
                    _left_speed = MAX_SPEED - 15;
                    _right_speed = MAX_SPEED;
                    cout<<"here"<<endl;
                }
                else {
                    // Move straight forward
                    _left_speed = MAX_SPEED;
                    _right_speed = MAX_SPEED;
                }
            }

            break;

        default:
            break;
        }


        // Set the motor speeds
        setSpeed(_left_speed, _right_speed);
    }
}

//this function take the curse of the Robot and make a operation to convert it in degrees,
//here we use parameters like M_PI, variables of directory cmath

double MyRobot::convert_bearing_to_degrees(const double* in_vector)
{
    double rad = atan2(in_vector[0], in_vector[2]);
    double deg = rad * (180.0 / M_PI);

    return deg;
}

//////////////////////////////////////////////
