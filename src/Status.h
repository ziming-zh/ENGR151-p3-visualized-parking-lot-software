//
// Created by Ziming on 2021/12/13.
//

#ifndef P3_STATUS_H
#define P3_STATUS_H
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include "Floor.h"
#include "Vehicle.h"
void change_status(Floor *f,std::vector <Vehicle>::iterator &v,int vec_n);
void Read_Log(std::vector <Vehicle> &v,Floor *f);
#endif //P3_STATUS_H
