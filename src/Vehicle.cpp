//
// Created by Ziming on 2021/12/7.
//

#include "Vehicle.h"
#include <iostream>

Vehicle::Vehicle() {
    status=0;
    stop=false;
    warn_type=0;
    vehicle=NULL;
}

void Vehicle::change_status() {
    status++;
    switch(status)
    {
        ///if the time reaches
        ///enter into the plot
        case 1:{


            ///print the enter ticket

            /// find the plot for the current car
            //specially remember that if the current floor is full, there is also chance that the car would eventually find its plot at othe floors
            ///begin the self-detect process
            //self-detect process for the front car to decide whether to stop
            ///begin the straight auto-move process
            // if the stop signs remains false, do move for constant speed per unit


            break;
        }
        ///if reach the turning point --> calculating for the turning point
        ///then enter into the side road
        case 2:{
            /// send continuous signal to the following car to **wait behind**
            //   if their distance to the *branch* is less than the normal car distance


            ///signal to the following car to stop Anyway! to prevent further trouble

            ///begin the curving the auto-move process

            ///begin the auto-rotate process
            break;
        }
        /// if the anchor point totally enter into the side road
        case 3:{
            ///self detect process

            ///signal to the **possible** car staying in the plot aside the car and prevent them from going out


            ///begin the straight auto-move process
            //change back -> move straight

            ///end the auto-rotate process

            ///SPECIAL: once the car move past the parking lot,
            // send continuous signal to the following car to **wait behind**
            // if their distance to the *plot* is less than the normal car distance

            break;
        }
        ///if reach the plotting point --> calculating for the plotting point
        ///enter into the planned plotting place
        case 4:{

            /// CONTINUE from case 3
            /// send continuous signal to the following car to **wait behind**
            //   if their distance to the *plot* is less than the normal car distance

            ///begin the curving auto-move process (reverse version)

            ///begin the auto-rotate process


            break;
        }
        /// the anchor point of the car is set right in the center of the plot
        /// staying the plot (inert state)
        case 5:{
            ///wait for the time to change the status


            break;
        }
        /// after triggered by case 5
        /// exit the plot and reach the side road
        case 6:{
            /// send continuous signal to the following car to **wait behind**
            //   if their distance to the *plot* is less than the normal car distance

            ///begin the curving auto-move process

            ///begin the auto-rotate process

            break;
        }
        /// after reach the plotting point
        /// move straight at the side road
        case 7:{
            ///self-detect process

            ///change the self-detect process
            // change -> back the the original one // keep the distance with the front

            ///signal to the **possible** car staying in the plot aside the car and prevent them from going out


            ///begin the straight auto-move process
            //change back -> move straight

            ///end the auto-rotate process
            break;
        }
        /// after reach the boundary of the side road
        ///move from the side road to the main road
        case 8:{

            /// send continuous signal to the following car to **wait behind**
            //   if their distance to the *branch* is less than the normal car distance

            break;
        }
        ///after reach the turning point
        ///move straight on the main road
        case 9:{
            ///self-detect process
            //self-detect process for the front car to decide whether to stop
            ///straight auto-move process
            // if the stop signs remains false, do move for constant speed per unit
            break;
        }
        ///after having reached the exit
        /// relevant functions with the exit of a car
        case 10:{

            ///print_ticket
            //...
            break;
        }
        default:{
            std::cerr<<"Abnormal State! Please check out for the error"<<std::endl;
        }
    }
}

#ifdef OPEN_GL
void Vehicle::create_vehicle() {
    switch (type) {
        case 1:{
            //init_car
            vehicle=new Car;

            break;
        }
        case 2:{
            vehicle=new UFO;
            break;
        }
        case 3:{
            vehicle=new Spacecraft;
            break;
        }
        case 4:{
            vehicle=new Teleported;
            break;
        }

    }
}
#endif