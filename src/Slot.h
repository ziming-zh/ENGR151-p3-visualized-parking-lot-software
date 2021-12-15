#ifndef PGROUP_16_PLOT_H
#define PGROUP_16_PLOT_H

#include "vec.h"
#include "Figure.h"

class Slot {
protected:
    bool vacant;
    bool type;///0 for normal and 1 for special
    float w,l;
#ifdef OPEN_GL
    ImgSlot* pl;
#endif
#ifndef OPEN_GL
    Vec anchor;
#endif
    ///vec

public:
    Slot(Vec anchor=Vec(0.0,0.0),float length=0.1,float width = 0.05);
    ~Slot();
    float get_w(); //get the width of the slot
    float get_l(); //get the length of the slot
    Vec get_anchor(); //get the anchor of the slot
    bool get_type();// get the type of the slot
    bool is_vacant(); //checkout whether the slot is vacant or not
    void occupy_slot(); // occupy the slot -> make it not vacant
    void exit_slot(); // make the slot vacant again
#ifdef OPEN_GL
    virtual ImgSlot* get_widget();
#endif
};
class Special_Slot:public Slot{
public:
    Special_Slot(Vec anchor=Vec(0.0,0.0),float length=0.1,float width = 0.05,float owidth=0.01);
    ~Special_Slot(){};
#ifdef OPEN_GL
    SpcSlot* get_widget(); //get the widget SpcSlot inside the Special_Slot
#endif
private:
    float o;

};


#endif //PGROUP_16_PLOT_H
