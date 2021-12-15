#include "Route.h"

unsigned long getCombNum(unsigned long n, unsigned long m){
    if(m > n) {return -1;}
    if(m == n || m == 0) {return 1;}
    if(m == 1) {return n;}

    return getCombNum(n - 1, m - 1) + getCombNum(n - 1, m);
}

// Get Points in Bezier curve. t in [0, 1].
Vec getBezier(std::vector<Vec> points, float t){
    Vec sum{0, 0};
    unsigned long n = points.size();
    for (unsigned long i = 0; i <= n; ++i){
        sum = sum + points[i] * getCombNum(n, i) * pow(1 - t, n - i) * pow(t, i);
    }
    return sum;
}

float getNorm(Vec v){
    return sqrt(pow(v.getX(), 2) + pow(v.getY(), 2));
}

Vec getCornerStep(Corner cor, int &tPos, float velocity){
    static const int resolution = 1000;
    std::vector<Vec> points;
    points.push_back(cor.p1);
    points.push_back(cor.p2);
    points.push_back(cor.p3);

    float sum = 0;
    Vec anchor = getBezier(points, tPos / resolution);
    Vec cur = anchor;
    for (int i = tPos + 1; i <= resolution; ++i){
        Vec next = getBezier(points, i / resolution);
        Vec d = next - cur;
        sum += getNorm(d);
        if(sum >= velocity){
            tPos = i;
            return next - anchor;
        }
    }
    return getBezier(points, 1);
}