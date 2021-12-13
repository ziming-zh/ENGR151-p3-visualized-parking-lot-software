//
// Created by Ziming on 2021/12/7.
//

#ifndef P3_VEHICLE_H
#define P3_VEHICLE_H

#include "vec.h"
#include "Figure.h"
#include "Ticket.h"
#include <vector>
class Vehicle {
private:
    int status;
    /**
     * 0 waiting to enter the parking lot
     * 1 entering the road stay on the main road
     * 2 entering the side road haven't reached the slot yet --> signal to other related cars(behind main road) to stop
     * 3 moving straight on the side road until meeting the slotting point
     * 4 reaching the planned slotting place signal to other related cars(behind side road) to stop
     * 5 remaining in the slot without motive to leave
     * 6 preparing to leave the slot for the side road
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

      std::vector<unit> warn_slot;
      std::vector<Vehicle*> vp;
      int type;
      int final_enter_time;
      unit plot;
      Ticket enter_ticket;
      Ticket exit_ticket;
      bool exit;

      /**
       * 1 Car
       * 2 UFO
       * 3 Spacecraft
       * 4 Teleported
       */
       int enter_time,interval;
       float speed;
#ifdef OPEN_GL
       Group *vehicle;
#endif
#ifndef OPEN_GL
       Vec anchor;
       float w,l;
#endif


       void send_signal(Vehicle *v); //send signal to a specific car, tell it to stop
       ///the most important task find out which car to send signal to





public:
    void self_detect();
    //void change_status(int time);
    int get_type(){
        return type;
    }
    Vehicle();
    ~Vehicle(){}
    void create_vehicle(Vec anchor,int type,int enter,int interval);
#ifdef OPEN_GL
     // create a specific car
    void delete_vehicle();
#endif
    void receive_signal(); //when the car receive a signal, it would stop immediately
    int get_enter_time();
    int get_interval();
    unit get_plot();
    void set_plot(unit p);
    float get_speed();
    void set_speed(float speed);
    bool get_stop();
    /// move related functions
    void move_straight(int dir);
    void move_curly(Vec spin,int dir);
    int get_final_enter_time();
    void set_final_enter_time(int mtime);
    int get_status();
    Vec get_anchor();
    void set_status(int st);
    Group *get_vehicle();
    void set_exit(bool flag);
    bool get_exit();
};


#endif //P3_VEHICLE_H
