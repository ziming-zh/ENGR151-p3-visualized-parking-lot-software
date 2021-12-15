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
    for(int i = 0; i < row; i++){
        delete[] (slot[i]);
    }
    delete[] slot;
}

void Floor::create_slot() {
    slot_l = (l) / (row) - o;
    slot_w = (w - 2 * o) / col;

    srand((unsigned)time(NULL));
    for(int i = 0; i < row; i++)
    {
        for(int j = 0; j < col; j++)
        {
            if(rand()%5 == 1) ///Special Slot
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



void Floor::set_v(std::vector<Vehicle> *m_v) {
    v=m_v;
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

void Floor::init_corners(){
    // init main corners
    mainCorners = new Corner *[2];
    for (int i = 0; i < 2; ++i){
        mainCorners[i] = new Corner[row];
    }
    
    // init branch corners
    branchCorners = new Corner *[row];
    for (int i = 0; i < row; ++i){
        branchCorners[i] = new Corner[col];
    }
}

void Floor::create_corners(){
    // create main corners
    for (int i = 0; i < 2; ++i){
        for (int j = 0; j < row; ++j){
            mainCorners[i][j] = get_main_corner(1-i, j);
        }
    }

    // create branch corners
    for (int i = 0; i < row; ++i){
        for (int j = 0; j < col; ++j){
            branchCorners[i][j] = get_branch_corner(i, j);
        }
    }
}

void Floor::delete_corners(){
    // delete main corners
    for (int i = 0; i < 2; ++i){
        delete[] (mainCorners[i]);
    }
    delete[] mainCorners;

    // delete branch corners
    for (int i = 0; i < row; ++i){
        delete[] (branchCorners[i]);
    }
    delete[] branchCorners;
}

Corner Floor::get_main_corner(int pos, int r){
    Corner ret;
    if(pos == 1){
        // enter
        ret.p1 = get_main_turnpoint(r, pos);
        ret.p3 = get_side_turnpoint(r, pos);
        ret.p2 = Vec(ret.p1.getX(), ret.p3.getY());
    }
    else{
        // exit
        ret.p1 = get_side_turnpoint(r, pos);
        ret.p3 = get_main_turnpoint(r, pos);
        ret.p2 = Vec(ret.p3.getX(), ret.p1.getY());
    }
    return ret;
}

Corner Floor::get_branch_corner(int r, int c){
    Corner ret;
    unit u;
    u.row = r; u.col = c;
    ret.p3 = get_slot_center(u);
    Vec bound = get_slot_bound(u);
    ret.p2 = Vec(bound.getX(), bound.getY() - o / 2.0);
    ret.p1 = get_reversing_point(u);
    return ret;
}