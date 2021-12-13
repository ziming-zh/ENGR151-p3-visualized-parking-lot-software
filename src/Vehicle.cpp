//
// Created by Ziming on 2021/12/7.
//

#include "Vehicle.h"
#include "Ticket.h"
#include <iostream>

Vehicle::Vehicle() {
    status=0;
    stop=false;
    exit= false;
    speed=0.001;
    plot={-1,-1};
    //warn_type=0;
#ifdef OPEN_GL
    vehicle=NULL;
#endif
}
#ifdef OPEN_GL
Group* Vehicle::get_vehicle(){
    return vehicle;
}
#endif

unit Vehicle::get_plot() {
    return plot;
}
/// manipulation for each car

int Vehicle::get_status() {
    return status;
}
void Vehicle::set_status(int st) {
    status=st;
}

void Vehicle::move_straight(int dir) {
    switch(dir)
    {
        case 1:{
#ifdef OPEN_GL
            vehicle->move(Vec(.0,speed));
#endif
#ifndef OPEN_GL
            anchor=anchor+Vec(.0,speed);
#endif

            break;
        }
        case 2:{
#ifdef OPEN_GL
            vehicle->move(Vec(.0,-speed));
#endif
#ifndef OPEN_GL
            anchor=anchor+Vec(.0,-speed);
#endif
            break;
        }
        case 3:{
#ifdef OPEN_GL
            vehicle->move(Vec(-speed,.0));
#endif
#ifndef OPEN_GL
            anchor=anchor+Vec(-speed,.0);
#endif
            break;
        }
        case 4:{
#ifdef OPEN_GL
            vehicle->move(Vec(speed,.0));
#endif
#ifndef OPEN_GL
            anchor=anchor+Vec(speed,.0);
#endif
            break;
        }
    }
}

Vec Vehicle::get_anchor() {
#ifndef OPEN_GL
    return anchor;
#endif
#ifdef OPEN_GL
    return vehicle->getAnchor();
#endif
}
void Vehicle::move_curly(Vec spin, int dir) {

    Vec dis=get_anchor()-spin;
    if(dir==1)//clockwise
        dis>>(speed/dis.get_dis());
    else
        dis<<(speed/dis.get_dis());
#ifndef OPEN_GL
        anchor=dis+spin;
#endif
#ifdef OPEN_GL

        vehicle->move(dis+spin-get_anchor());
        if(dir)
            vehicle->rotate(-speed/dis.get_dis());
        else
            vehicle->rotate(speed/dis.get_dis());
        //std::cout<<((dis+spin-get_anchor()).getX())<<" "<<((dis+spin-get_anchor()).getY())<<std::endl;
        //std::cout<<get_anchor().getX()<<" "<<get_anchor().getY()<<std::endl;
        vehicle->setAnchor(dis+spin);
        //vehicle->rotate(-speed/dis.get_dis());
#endif

}

void Vehicle::create_vehicle(Vec anch,int t,int et, int intv) {
    enter_time=et;
    interval=intv;
    type=t;
#ifndef OPEN_GL
    this->anchor=anch;
#endif
#ifdef OPEN_GL
    switch (t) {
        case 1:{
            //init_car
            vehicle=new Car(anch);

            break;
        }
        case 2:{
            vehicle=new UFO(anch);

            break;
        }
        case 3:{
            vehicle=new Spacecraft(anch);

            break;
        }
        case 4:{
            vehicle=new Teleported(anch);

            break;
        }

    }
#endif
}
#ifdef OPEN_GL
void Vehicle::delete_vehicle() {
    delete vehicle;
}
#endif


void Vehicle::send_signal(Vehicle *v) {
    v->receive_signal();
}

void Vehicle::receive_signal() {
    stop=true;
}
void Vehicle::self_detect() {

}
int Vehicle::get_enter_time() {
    return enter_time;
}
int Vehicle::get_interval() {
    return interval;
}

void Vehicle::set_plot(unit p) {
    plot=p;
}

float Vehicle::get_speed() {
    return speed;
}

void Vehicle::set_speed(float sp) {
    speed=sp;
}

int Vehicle::get_final_enter_time() {
    return final_enter_time;
}
void Vehicle::set_final_enter_time(int mtime) {
    final_enter_time=mtime;
}

bool Vehicle::get_stop() {
    return stop;
}

void Vehicle::set_exit(bool flag) {
    exit=flag;
}

bool Vehicle::get_exit() {
    return exit;
}