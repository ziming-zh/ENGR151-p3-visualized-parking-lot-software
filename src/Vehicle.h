//
// Created by Ziming on 2021/12/7.
//

#ifndef P3_VEHICLE_H
#define P3_VEHICLE_H

#include "vec.h"
#include "Figure.h"
#include <queue>
class Vehicle {
private:
    int status;
    /**
     * 0 waiting to enter the parking lot
     * 1 entering the road stay on the main road
     * 2 entering the side road haven't reached the plot yet --> signal to other related cars(behind main road) to stop
     * 3 moving straight on the side road until meeting the plotting point
     * 4 reaching the planned plotting place signal to other related cars(behind side road) to stop
     * 5 remaining in the plot without motive to leave
     * 6 preparing to leave the plot for the side road
     * 7 move straight in the side road
     * 8 preparing to leave the side road for the main road
     * 9 move staight on the main road
     * 10 having already left the parking lot
     */
     bool stop;
     /**
      * whether or not having received the signal to stop
      * unlock itself automatically
      */

      int warn_type;
      /**
       * 0 no warning
       * 1 warn main road
       * 2 warn side road
       * 3 warn plot
       * 4 warn side road(reverse)
       * 5 warn main road(reverse)
       */
      std::queue<unit> warn_plot;
      int type;
      /**
       * 1 Car
       * 2 UFO
       * 3 Spacecraft
       * 4 Teleported
       */
       int enter_time,exit_time;
       Group *vehicle;
       void status_effect(int status);
       void send_signal(Vehicle *v);
        Vehicle();
        ~Vehicle(){
            if(vehicle!=NULL)
                delete vehicle;
        }


public:
    void change_status();
    int get_type(){
        return type;
    }
    void create_vehicle();
    void receive_signal();
};


#endif //P3_VEHICLE_H
