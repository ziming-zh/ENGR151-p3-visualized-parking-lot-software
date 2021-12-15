#ifndef P3_FIGURE_H
#define P3_FIGURE_H

#include "OPEN_GL_ENABLED.h"
#include "vec.h"

class Figure {
protected:
    Vec anchor;
public:
    Figure() : anchor(0, 0) {}

    Vec getAnchor() {return anchor;}
    void setAnchor(Vec a) {anchor = a;}
    virtual void draw() = 0;
    virtual void move(Vec dir) = 0;
    virtual void rotate(float angle) = 0;
    virtual void zoom(float k) = 0;

    virtual ~Figure() {}
};

class ColoredFig : public Figure{
protected:
    float r,g,b;
public:
    ColoredFig(float r=.0,float g=.0,float b=.0){
        this->r=r;
        this->g=g;
        this->b=b;
    };
    ~ColoredFig(){}
    void Paint();
    void ClearColor();

};

class Circle: public ColoredFig{
private:
    float radius;
    Vec ori;
public:
    Circle(float r): ori(anchor.getX(),anchor.getY()){
        radius=r;
    }
    ~Circle(){}
    void move(Vec s);
    void draw();
    void rotate(float angle);
    void zoom(float k);
    void set_ori(Vec v){
        ori=v;
    }
};

class SemiCircle:  public ColoredFig{
public:
    SemiCircle(): ori(anchor.getX(),anchor.getY()),start(anchor.getX()+.1,anchor.getY()){}
    ~SemiCircle() {}
    void move(Vec s);
    void draw();
    void rotate(float angle);
    void zoom(float k);
    void autorotate();
    void set_ori(Vec v){
        ori=v;
    }
    void set_start(Vec v){
        start=v;
    }

private:
    Vec ori;
    Vec start;
};

class Quad : public ColoredFig {
public:
    Quad(): p1(-.5,-.5), p2(.5,-.5),p3(.5,.5), p4(-.5,.5){};
    ~Quad(){}
    void move(Vec s);
    void draw();
    void rotate(float angle);
    void zoom(float k);
    void set_p1(Vec p){p1=p;}
    void set_p2(Vec p){p2=p;}
    void set_p3(Vec p){p3=p;}
    void set_p4(Vec p){p4=p;}
protected:
    Vec p1;
    Vec p2;
    Vec p3;
    Vec p4;
};

class Triangle : public ColoredFig {
public:
    Triangle(): p1(-.5,-.5), p2(.5,-.5),p3(.0,.5){};
    ~Triangle(){}
    void move(Vec s);
    void draw();
    void rotate(float angle);
    void zoom(float k);
    void set_p1(Vec p){p1=p;}
    void set_p2(Vec p){p2=p;}
    void set_p3(Vec p){p3=p;}
protected:
    Vec p1;
    Vec p2;
    Vec p3;
};

class Rectangle : public Quad{
public:
    Rectangle() : s1(-.5,-.5),s2(.5,.5){
        reset();
    };
    void set_p1(Vec p){s1=p;reset();}
    void set_p2(Vec p){s2=p;reset();}
    void reset(){
        p1=s1;
        p3=s2;
        Vec tmp=s2-s1;
        p2=p1+Vec(0,tmp.getY());
        p4=p1+Vec(tmp.getX(),0);
    }
    ~Rectangle(){}
private:
    Vec s1,s2;
};

class Polygon : public ColoredFig {
private:
    int num;
    Vec **p;
public:
    Polygon(int num,Vec **p);
    ~Polygon(){};
    void move(Vec s);
    void draw();
    void rotate(float angle);
    void zoom(float k);
};

class Group : public Figure {
protected:
    // A Group of figure "has" other figures.
    ColoredFig **sh;
    int sh_num;
    float gwidth,gheight;
    float max_w;
    float size;
    bool zoom_out;
public:
    // We left out the constructor as well
    float get_width();
    void draw(); // Draw out all its figures
    void move(Vec dir); // Move all its figures
    void move_to(Vec dir); // Move all its figures to a specific place
    void rotate(float angle); // Rotate the group as a whole.
    void zoom(float k); // Zoom the group as a whole.
    void auto_rotate();
    void auto_zoom();
    void initsize(){size=1;zoom_out=true;}
    ~Group();

};

class Car: public Group{
public:
    Car(Vec s=Vec(.0,.0),float width=1.0,float height=0.75, float owidth = .1);
    ~Car(){}

    float w,h,o;
};

class UFO: public Group{
public:
    UFO(Vec s=Vec(.0,.0),float radius=0.5,float height=0.1,float width=0.2);

    ~UFO(){}
private:
    float radius,h, w;

};

class Spacecraft: public Group{
public:
    Spacecraft(Vec s=Vec(.0,.0),float width=0.1,float height = 0.4,float owidth=0.005);


    ~Spacecraft(){}
private:
    float w,h,o;
};
class Teleported: public Group{
public:
    Teleported(Vec s=Vec(.0,.0),float width=0.2,float height = 0.8);
    ~Teleported(){}
protected:
    float w,h;
};

class ImgFloor : public Group{
public:
    ImgFloor(float length=1.2,float width=1.6,float owidth=0.15);
    ~ImgFloor(){}
private:
    float l,w,o;
};

class ImgSlot : public Group{
public:
    ImgSlot(Vec s=Vec(.0,.0),float length=0.1,float width = 0.05);
    ~ImgSlot(){}
protected:
    float l,w;
};

class SpcSlot : public ImgSlot{
public:
    SpcSlot(float owidth=0.01);
    ~SpcSlot(){}
    void set_w(float w);
    void set_l(float l);
private:
    float o;
};

#endif //P3_FIGURE_H
