#ifndef P3_VEC_H
#define P3_VEC_H
#include <cmath>
#define PI  3.1415926535

typedef struct _Unit{
    int row;
    int col;
}unit;

class Vec {
private:
    float x,y;
public:
    Vec(float _x, float _y) {
        x = _x; y = _y;
    }
    Vec(){}
    float getX() {return x;}
    float getY() {return y;}

    // Example Overloads + operator
    // returns the sum of  Vec
    float get_dis()
    {
        return sqrt(x*x+y*y);
    }
    Vec operator+ (Vec v) {
        return Vec(x + v.getX(), y + v.getY());
    }
    bool operator== (Vec v){
        return (v.getX()==x && v.getY()==y);
    }

    // Overload - on  Vectors
    // return thier difference Vector
    Vec operator- (Vec v) {
        return Vec(x - v.getX(), y - v.getY());
    }

    // Overload * operator on a float k
    // return current Vector scaled by k
    Vec operator* (float k) {
        return Vec(x *k, y *k);
    }
    // Overload * on  Vectors
    // return thier inner product (scaler product)
    float operator* (Vec v) {
        return (x * v.getX() + y * v.getY());
    }
    // Overload << on an angle
    // return current vector rotated counter clockwise
    // by this angle
    Vec operator<< (float angle)
    {
        float dist= sqrt(x*x+y*y);
        float cur = atan(y/x)+angle;
        if(x<0) cur+=PI;
        x=dist* cosf(cur);
        y=dist* sinf(cur);
        return Vec(x,y);
    }
    // Overload >> on an angle
    // return current vector rotated clockwise
    // by this angle
    Vec operator>> (float angle)
    {
        float dist= sqrt(x*x+y*y);
        float cur = atan(y/x)-angle;
        if(x<0) cur+=PI;
        x=dist* cosf(cur);
        y=dist* sinf(cur);
        return Vec(x,y);
    }
};

#endif //P3_VEC_H
