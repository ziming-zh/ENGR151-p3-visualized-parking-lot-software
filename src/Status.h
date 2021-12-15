#ifndef P3_STATUS_H
#define P3_STATUS_H
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include "Floor.h"
#include "Vehicle.h"
using namespace std;
bool detect_safe(Floor *f,vector <Vehicle>::iterator &v,int vec_n,int allv);
void self_dect(Floor *f,vector <Vehicle>::iterator &v,int vec_n,int allv);
void change_status(Floor *f,vector <Vehicle>::iterator &v,int vec_n,int allv);
void Read_Log(vector <Vehicle> &v,Floor *f);
#endif //P3_STATUS_H
