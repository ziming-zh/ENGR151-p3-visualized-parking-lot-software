//
// Created by Ziming on 2021/12/4.
//

#include "Slot.h"

Slot::Slot(Vec anchor, float length, float width) {
    type=false;
    vacant=true;
    w=width;
    l=length;
#ifndef OPEN_GL
    this->anchor=anchor;
#endif
#ifdef OPEN_GL
    pl=new ImgSlot(anchor,length,width);
#endif

}
Slot::~Slot() {
#ifdef OPEN_GL
    delete pl;
#endif
}
float Slot::get_w(){
    return w;
}
float Slot::get_l() {
    return l;
}
bool Slot::get_type(){
    return type;
}
Vec Slot::get_anchor() {
#ifdef OPEN_GL
    return pl->getAnchor();
#endif
#ifndef OPEN_GL
    return anchor;
#endif
}

Special_Slot::Special_Slot(Vec anchor,float length, float width, float owidth)  {
    o=owidth;
    l=length;
    w=width;
    type=true;
    Slot(anchor,l,w);
#ifdef OPEN_GL

    delete pl;

    pl=new SpcSlot(o);
    ((SpcSlot*)pl)->set_w(w);
    ((SpcSlot*)pl)->set_l(l);
    pl->move(anchor);


#endif

}
#ifdef OPEN_GL
ImgSlot *Slot::get_widget() {
    return (ImgSlot*) pl;
}

SpcSlot *Special_Slot::get_widget() {
    return (SpcSlot*) pl;
}
#endif

bool Slot::is_vacant() {
    return vacant;
}
void Slot::occupy_slot() {
    vacant=false;
}

void Slot::exit_slot() {
    vacant=true;
}