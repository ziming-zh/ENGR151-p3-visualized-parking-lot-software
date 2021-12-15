//
// Created by Ziming on 2021/12/1.
//

#ifndef PGROUP_16_FLOOR_H
#define PGROUP_16_FLOOR_H

#include "Slot.h"
#include "Route.h"
#include "Vehicle.h"
#include <vector>
class Floor {
public:
    Floor(int row=3,int col=10,float width=1.6,float length=1.2,float owidth=0.15)
    {

        w=width;
        l=length;
        o=owidth;
        this->row=row;
        this->col=col;
        slot=NULL;
        m_time=1.0;
        anchor=Vec(-w/2,o-l/2);

    }
    ~Floor(){
        delete_slot();
    }
    //void create_plain_slot();
    void init_slot(); //allocat memory to the 2d-Slot* array slot
    void create_slot(); //put slot into the floor
    void delete_slot(); // delete slot from the floor
    void draw_slot();   // draw out the slot
    Slot*** get_slot(); // get the pointer slot(_)
    unit find_slot(bool type); // true for special type false for normal type
    Vec get_anchor();
    Vec get_exit();
    Vec get_main_turnpoint(int m_row,int pos);
    //get the point where the car should begin to turn from main road to side road when enter the slot (pos=1)
    //and finish the turning process from side to main when exit the slot(pos=0)
    ///pos 1-> begin 0 -> end

    Vec get_side_turnpoint(int m_row,int pos);
    // get the point where the car should finish the turning process form main road to side road(pos=1)
    // begin to turn from side road to main road when exit the slot (pos=0)
    Vec get_slot_anchor(unit slot);
    //get the anchor point of a specific slot
    Vec get_slot_center(unit slot);
    //get the center point of a specific slot (where the car fully enter the slot)
    Vec get_slot_bound(unit slot);
    // get the bound point of a specific slot
    Vec get_reversing_point(unit slot);
    // get the point where the car is going to stop and reverse to the plot
    float get_length();   //get the length of the whole floor
    float get_width();    //get the width of the whole floor
    float get_owidth();
    void set_time();    //make the timer move in pace of the timestep function (don't move it)
    int get_time();   //get the current time(int)
    float get_m_time(){return m_time;}

    void set_v(std::vector<Vehicle>* m_v);
    int get_row(){return row;}
    int get_col(){return col;}
    float get_slot_w(){return slot_w;}
    float get_slot_l(){return slot_l;}
private:
    float w,l,o;
    int row;
    int col;
    Slot ***slot;
    float m_time;
    Vec anchor;
    float slot_l;
    float slot_w;
    
    std::vector<Vehicle> *v;

    Corner **mainCorners;
    Corner **branchCorners;
    Corner get_main_corner(int pos, int r);
    Corner get_branch_corner(int r, int c);
    void init_corners();
    void create_corners();
    void delete_corners();

};

#endif //PGROUP_16_FLOOR_H
