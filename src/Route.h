#ifndef _ROUTE_H_
#define _ROUTE_H_
#include <cmath>
#include <vector>
#include "vec.h"
typedef struct _Corner{
    Vec p1, p2, p3;
} Corner;

// Return combinatorial number (n, m). n >= m
unsigned long getCombNum(unsigned long n, unsigned long m);

// Get Points in Bezier curve. t in [0, 1].
Vec getBezier(std::vector<Vec> points, float t);

Vec getCornerStep(Corner cor, int &tPos, float velocity);

float getNorm(Vec v);

#endif