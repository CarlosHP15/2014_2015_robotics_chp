/**
 * @file    MyRobot.cpp
 * @brief   Obstacle_avoidance.
 *
 * @author  Carlos Hernandez Paz <100292793@alumnos.uc3m.es>
 * @date    2014-11-11
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

    for(int i=0;i<16;i++){
        // string which will contain the result
        string Result;
        ostringstream convert;   // stream used for the conversion
        convert << i;      // insert the textual representation of 'Number' in the characters in the stream
        Result = convert.str();
        _distance_sensor[i]=getDistanceSensor("ds"+ Result);
        _distance_sensor[i]->enable(_time_step);
    }


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
    //double ir_val[0] = 0.0, ir_val[1] = 0.0,ir_val[2]=0.0,ir_val[3]=0.0, ir_val[4] = 0.0, ir_val[5] = 0.0,ir_val[6]=0.0,ir_val[7]=0.0, ir_val[8] = 0.0, ir_val[9] = 0.0,ir_val[1]0=0.0,ir_val[1]1=0.0, ir_val[1]2 = 0.0, ir_val[1]3 = 0.0,ir_val[1]4=0.0,ir_val[1]5=0.0;
    double ir_val[16];
    for(int i=0;i<16;i++){
        ir_val[i]= 0.0;
    }

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

        for(int i=0;i<16;i++){
            ir_val[i]=_distance_sensor[i]->getValue();

        }

        // Print sensor values to console
        cout << "Compass angle (degrees): " << compass_angle << endl;

        for(int i=0;i<16;i++){
            cout<<"sensor"<<i<<":"<<ir_val[i];
            cout<<endl;
        }

        // Control logic of the robot


        //este if se encarga de conocer si hay algun sensor activo, en caso de que el robot no este,
        //proximo a ningun objeto, seguira el camino atendiendo a la brujula, de lo contrario entraría dentro del if
        if((ir_val[0]>30)||(ir_val[1]>30)||(ir_val[2]>30)||(ir_val[3]>30)||(ir_val[4]>30)||(ir_val[5]>30)||(ir_val[6]>30)||(ir_val[7]>30)||(ir_val[8]>30)||(ir_val[9]>30)||(ir_val[10]>30)||(ir_val[11]>30)||(ir_val[12]>30)||(ir_val[13]>30)||(ir_val[14]>30)||(ir_val[15]>30)){

            //En este caso si los sensores delantero-laterales estan activos
            //el robot retrocederá para evitar colision y mientras se orientará a la izquierda
            if((ir_val[15]>DISTANCE_LIMIT-40)&&((ir_val[14]>DISTANCE_LIMIT-50)&&(ir_val[13]>DISTANCE_LIMIT-60))){
                _mode=FOLLOWER_MAX;
                cout<<"Turn left the robot"<<endl;}

            else{
                //en este caso a contrario que en el anterior si se activan los sensores delantero-laterales
                //el robot retrocedera y se se orientará hacia la izquierda
                if(((ir_val[1]>DISTANCE_LIMIT-50)&&(ir_val[2]>DISTANCE_LIMIT-60)&&(ir_val[0]>DISTANCE_LIMIT-40))){
                    _mode=CORNER_RIGHT;
                    cout<<"Turn right the robot"<<endl;}

                else{
                    //en este otro caso el robot ante la activacion de los sensores laterales,
                    //tendera hacia la izquierda continuando con su movimiento
                    if(((ir_val[11]>DISTANCE_LIMIT-40)&&(ir_val[12]>DISTANCE_LIMIT-30))||(ir_val[13]>DISTANCE_LIMIT-30)){
                        _mode=TURN_LEFT;
                        cout<<"turn left the robot,less grade of turn left "<<endl;}

                    else{
                        //en esta ocasion girara el robot hacia la derecha progresivamente,
                        //avisado por los sensores laterales
                        if(((ir_val[4]>DISTANCE_LIMIT-60)&&(ir_val[3]>DISTANCE_LIMIT-40))||(ir_val[2]>DISTANCE_LIMIT)){
                            _mode=TURN_RIGHT;
                            cout<<"Turn right the robot, less grade of turn right"<<endl;}

                        else{
                            //en caso de que el robot se este desviando en exceso de la trayectoria,
                            //esta declaracion ayuda a que se vuelva a pegar a la pared
                            if((ir_val[11]>DISTANCE_LIMIT)&&(ir_val[10]>DISTANCE_LIMIT)&&(ir_val[9]>DISTANCE_LIMIT-30)){
                                _mode=LESS_RIGHT;
                                cout<<"the route of the robot less right"<<endl;}

                            else{
                                //en caso de que el robot se este desviando en exceso de la trayectoria,
                                //esta declaracion ayuda a que se vuelva a pegar a la pared
                                if((ir_val[4]>DISTANCE_LIMIT)&&(ir_val[5]>DISTANCE_LIMIT)&&(ir_val[6]>DISTANCE_LIMIT-30)){
                                    _mode=LESS_LEFT;
                                    cout<<"the route of the robot less left"<<endl;}

                                else{
                                    //Este if utiliza los sensores delanteros y lee en el entorno si existe un hueco,
                                    //donde poder introducirse
                                    if(((ir_val[15]>DISTANCE_LIMIT-37)||(ir_val[0]>DISTANCE_LIMIT-30))&&(ir_val[4]>DISTANCE_LIMIT-60)){
                                        _mode=CORNER_RIGHT;
                                        cout<<"Turn corner right"<<endl;}

                                    else{
                                        //Este if es el encargado de buscar un hueco en el entorno si existe,
                                        //a contrario que la anterior el hueco que busca este if es el del lado opuesto
                                        if(((ir_val[15]>DISTANCE_LIMIT-30)||(ir_val[0]>DISTANCE_LIMIT-30))&&(ir_val[11]>DISTANCE_LIMIT-60)){
                                            _mode=FOLLOWER_MAX;
                                            cout<<"Turn corner left"<<endl;}

                                        else{
                                            //opcion para seguir la pared y encontrar la ruta ayudado por el resto de declaraciones
                                            if((ir_val[11]>DISTANCE_LIMIT-40)&&(ir_val[12]<DISTANCE_LIMIT)){
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
            _left_speed=-MAX_SPEED;
            _right_speed=0;

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
