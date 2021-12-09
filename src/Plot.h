//
// Created by Ziming on 2021/12/4.
//

#ifndef PGROUP_16_PLOT_H
#define PGROUP_16_PLOT_H

#include "vec.h"


class Plot {
private:
    bool type;///0 for normal and 1 for special
    Rgb color_setting;

    ///vec
    Vec size;
    Vec anchor; ///point to down left side of the plot
public:
    bool get_type();
    Vec get_size();
    Vec get_anchor();

};
class Special_Plot:public Plot{
public:
    void change_color();
};



#endif //PGROUP_16_PLOT_H
