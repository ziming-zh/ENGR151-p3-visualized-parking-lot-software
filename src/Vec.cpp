#include "Vec.h"

Vec::Vec(float _x, float _y) : x(_x), y(_y) {}

float Vec::getX() const {return x;}

float Vec::getY() const {return y;}

// Return their sum vector.
Vec Vec::operator + (const Vec &v) const {
    return Vec(x + v.getX(), y + v.getY());
}

// Return thier difference Vector.
Vec Vec::operator - (const Vec &v) const{
    return Vec(x - v.getX(), y - v.getY());
}

// Return current Vector scaled by k.
Vec Vec::operator * (float k) const {
    return Vec(x * k, y * k);
}

// Return thier inner product (scaler product).
float Vec::operator * (const Vec &v) const {
    return x * v.getX() + y * v.getY();
}

// Return current vector rotated counter clockwise by angle. angle should be in radian.
Vec Vec::operator << (double angle) const {
    float x2 = x * cos(angle) - y * sin(angle);
    float y2 = x * sin(angle) + y * cos(angle);
    return Vec(x2, y2);
}

// Return current vector rotated clockwise by angle. angle should be in radian.
Vec Vec::operator >> (double angle) const {
    return (*this) << (-angle);
}