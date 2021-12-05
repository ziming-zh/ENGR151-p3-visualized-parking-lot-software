//
// Created by Ziming on 2021/12/1.
//

#ifndef PGROUP_16_FLOOR_H
#define PGROUP_16_FLOOR_H

#include "Plot.h"

class Floor {
public:
    Floor(int row=2,int col=5,float width=100.0,float length=150.0)
    {
        this->width=width;
        this->length=length;
        this->row=row;
        this->col=col;
        plot = new Plot**[row];
        for(int i = 0;i<row;i++){
            plot[i]=new Plot*[col];
        }
    }
    ~Floor(){
        for(int i = 0;i<row;i++){
            delete[] plot[i];
        }
        delete[] plot;
    }
    bool create_plot(Plot *p,bool type,int size); /// create a row of plot
    bool delete_plot(); /// delete a row of plot

    unit find_plot(int type);
    int get_length();
    int get_width();
    bool add_row(); //para
private:
    float width;
    float length;
    int row;
    int col;
    Plot ***plot;
};

#endif //PGROUP_16_FLOOR_H
