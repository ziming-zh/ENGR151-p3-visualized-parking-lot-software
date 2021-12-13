//
// Created by Ziming on 2021/12/1.
//

#include "Floor.h"
#include <ctime>
#define SPECIAL 0.1
float Floor::get_length() {
    return l;
}
float Floor::get_width() {
    return w;
}
float Floor::get_owidth() {
    return o;
}
Vec Floor::get_anchor() {
    return anchor;
}
Slot ***Floor::get_slot() {
    return slot;
}
int Floor::get_time() {
    return (int)m_time;
}
void Floor::init_slot() {
    slot = new Slot**[row];
    for(int i = 0;i<row;i++){
        slot[i]=new Slot*[col];
    }
}
void Floor::delete_slot() {
    for(int i = 0;i<row;i++){
        delete[] (slot[i]);
    }
    delete[] slot;
}

void Floor::create_slot() {
    slot_l=(l)/(row)-o;
    slot_w=(w-2*o)/col;

    srand((unsigned)time(NULL));
    for(int i=0;i<row;i++)
    {
        for(int j=0;j<col;j++)
        {

            if(rand()%5==1) ///Special Slot
            {
                Special_Slot* p=new Special_Slot(anchor+Vec(o+j*slot_w,i*(slot_l+o)),slot_l,slot_w);

                slot[i][j]=(Slot*)p;
                //p->get_widget()->move(anchor+Vec(j*slot_w,2*i*slot_l));
#ifdef OPEN_GL
                p->get_widget()->draw();
#endif
            }
            /// Normal Slot
            else{
                slot[i][j]=new Slot(anchor+Vec(o+j*slot_w,i*(slot_l+o)),slot_l,slot_w);
#ifdef OPEN_GL
                slot[i][j]->get_widget()->draw();
#endif
            }
        }
    }

}
#ifdef OPEN_GL
void Floor::draw_slot(){
    for(int i=0;i<row;i++)
    {
        for(int j=0;j<col;j++)
        {
            slot[i][j]->get_widget()->draw();
        }
    }
}
#endif
void Floor::set_time() {
    m_time=m_time+0.05;
}

unit Floor::find_slot(bool type) {
    for(int i=0;i<row;i++)
    {
        for(int j=0;j<col;j++)
        {
            if(slot[i][j]->get_type()==type && slot[i][j]->is_vacant())
            {
                slot[i][j]->occupy_slot();
                return unit{i,j};
            }
        }
    }
    return unit{-1,-1};
}

Vec Floor::get_main_turnpoint(int m_row, int pos) {
    if(pos)
        return anchor+Vec(o/2,m_row*(slot_l+o)-o);
    else
        return anchor+Vec(w-o/2,m_row*(slot_l+o)-o);
}
Vec Floor::get_side_turnpoint(int m_row, int pos) {
    if(pos)
        return anchor+Vec(o,m_row*(slot_l+o)-o/2);
    else
        return anchor+Vec(w-o,m_row*(slot_l+o)-o/2);
}
Vec Floor::get_reversing_point(unit m_slot) {
    return get_slot_anchor(m_slot)+Vec(slot_w/2+o/2,-o/2);
}
Vec Floor::get_slot_bound(unit m_slot){
    return get_slot_anchor(m_slot)+Vec(slot_w/2,0);
}

Vec Floor::get_slot_anchor(unit m_slot) {
    return slot[m_slot.row][m_slot.col]->get_anchor();
}
Vec Floor::get_slot_center(unit m_slot) {
    return get_slot_anchor(m_slot)+Vec(slot_w/2,slot_l/2);
}

Vec Floor::get_exit() {
    return anchor+Vec(w-o/2,-2*o);
}