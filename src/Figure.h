//
// Created by Ziming on 2021/12/4.
//

#ifndef P3_FIGURE_H
#define P3_FIGURE_H


class Figure {
protected:
    Vec anchor;
public:
    Figure() : anchor(, ) {}

    Vec getAnchor() {return anchor;}
    void setAnchor(Vec a) {anchor = a;}
    virtual void draw() = ;
    virtual void move(Vec dir) = ;
    virtual void rotate(float angle) = ;
    virtual void zoom(float k) = ;

    virtual ~Figure() {}
}

class ColoredFig:public Figure{

};


class Quadrilateral : public ColoredFig {

};

class Rectangle : public Quadrilateral{

};

class Teleporter : public Rectangle{

};
class Polygon : public ColoredFig {

};



class Group : public Figure {
private:
    // A Group of figure "has" other figures.
public:
    // We left out the constructor as well

    void draw(); // Draw out all its figures
    void move(Vec dir); // Move all its figures

    void rotate(float angle); // Rotate the group as a whole.
    void zoom(float k); // Zoom the group as a whole.
    ~Group() {}
}

class Car: public Group{

};
class UFO: public Group{

};
class Spacecraft: public Group{
    
};
*/


#endif //P3_FIGURE_H
