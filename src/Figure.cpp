//
// Created by Ziming on 2021/12/4.
//


#include <GL/freeglut.h>
#include "Figure.h"
void ColoredFig::Paint() {
    r = (float)rand() / (float)RAND_MAX;
    g = (float)rand() / (float)RAND_MAX;
    b = (float)rand() / (float)RAND_MAX;
}

void Circle::move(Vec s) {
    ori=ori+s;
}
void Circle::draw() {
    glColor3f(r, g, b);
    glBegin(GL_LINE_LOOP);
    int n = 1024;
    for(int i=0;i<n;i++){
        glVertex2f(ori.getX()+radius* cos(2*PI/n*i),ori.getY()+radius* sin(2*PI/n*i));
    }
    glEnd();
}
void Circle::zoom(float k) {
    radius*=k;
    ori=(ori-anchor)*k+anchor;
}

void Circle::rotate(float angle) {
    ori=((ori-anchor)<<angle)+anchor;
}
void SemiCircle::move(Vec s) {
    ori=ori+s;
}
void SemiCircle::draw() {
    glColor3f(r, g, b);
    glBegin(GL_POLYGON);
    int n = 1024;

    for (int i = 0; i < n; i++)
    {
        glVertex2d(((start-ori)<<(PI * i / n)).getX()+ ori.getX(),  ((start-ori)<<(PI * i / n)).getY() + ori.getY());
    }
    glVertex2d(((start-ori)<<(PI)).getX() + ori.getX(),  ((start-ori)<<(PI)).getY() + ori.getY());
    glEnd();
}
void SemiCircle::rotate(float angle) {
    start=((start-anchor)<<angle)+anchor;
    ori=((ori-anchor)<<angle)+anchor;

}
void SemiCircle::autorotate() {
    start=((start-ori)<<0.05)+ori;
}

void SemiCircle::zoom(float k) {
    start=((start-anchor)*k)+anchor;
}

void Triangle::move(Vec s) {
    p1=s+p1;
    p2=s+p2;
    p3=s+p3;
}
void Triangle::draw() {
    glColor3f(r, g, b);
    glBegin(GL_TRIANGLES);
    glVertex2d(p1.getX(),p1.getY());
    glVertex2d(p2.getX(), p2.getY());
    glVertex2d(p3.getX(), p3.getY());

    glEnd();
}
void Triangle::rotate(float angle) {
    p1=((p1-anchor)<<angle)+anchor;
    p2=((p2-anchor)<<angle)+anchor;
    p3=((p3-anchor)<<angle)+anchor;
}
void Triangle::zoom(float k) {
    p1=((p1-anchor)*k)+anchor;
    p2=((p2-anchor)*k)+anchor;
    p3=((p3-anchor)*k)+anchor;
}

void Quad::move(Vec s) {
    p1=s+p1;
    p2=s+p2;
    p3=s+p3;
    p4=s+p4;
}
void Quad::draw() {
    glColor3f(r, g, b);
    glBegin(GL_QUADS);
    glVertex2d(p1.getX(),p1.getY());
    glVertex2d(p2.getX(), p2.getY());
    glVertex2d(p3.getX(), p3.getY());
    glVertex2d(p4.getX(), p4.getY());

    glEnd();
}
void Quad::rotate(float angle) {
    p1=((p1-anchor)<<angle)+anchor;
    p2=((p2-anchor)<<angle)+anchor;
    p3=((p3-anchor)<<angle)+anchor;
    p4=((p4-anchor)<<angle)+anchor;
}
void Quad::zoom(float k) {
    p1=((p1-anchor)*k)+anchor;
    p2=((p2-anchor)*k)+anchor;
    p3=((p3-anchor)*k)+anchor;
    p4=((p4-anchor)*k)+anchor;
}
Polygon::Polygon(int num, Vec *p) {
    this->num=num;
    this->p=p;

}
void Polygon::move(Vec s) {
    for(int i = 0;i<num;i++){
        p[i]=s+p[i];
    }
}

void Polygon::draw() {
    glColor3f(r, g, b);
    glBegin(GL_POLYGON);
    for(int i = 0;i<num;i++){
        glVertex2d(p[i].getX(),p[i].getY());
    }
    glVertex2d(p[0].getX(),p[0].getY());
    glEnd();
}
void Polygon::rotate(float angle) {
    for(int i  = 0;i<num;i++)
    {
        p[i]=((p[i]-anchor)<<angle)+anchor;
    }
}
void Polygon::zoom(float k) {
    for(int i  = 0;i<num;i++)
    {
        p[i]=((p[i]-anchor)*k)+anchor;
    }
}

///Group
void Group::draw()
{
    for (int i = 0; i < sh_num; i++)
    {
        sh[i]->draw();
    }
}

void Group::rotate(float angle) {
    for (int i = 0; i < sh_num; i++)
    {
        sh[i]->rotate(angle);
    }
}
void Group::zoom(float k) {
    for (int i = 0; i < sh_num; i++)
    {
        sh[i]->zoom(k);
    }
}
void Group::move(Vec dir) {
    for (int i = 0; i < sh_num; i++)
    {
        sh[i]->move(dir);
    }
}

/// Vehicle
Car::Car(Vec anchor, float width, float height, float owidth) {

    // init
    this->anchor = anchor;
    w = width;
    h = height;
    o = owidth;
    sh = new ColoredFig*[4];
    sh_num=4;
    // body
    Vec p1 = Vec(anchor.getX() - w / 2, anchor.getY() - h / 2 + o);
    Vec p2 = Vec(anchor.getX() + w / 2, anchor.getY() + o / 2);
    sh[2]=new class Rectangle();
    sh[2]->setAnchor(anchor);
    ((class Rectangle*)sh[2])->set_p1(p1);
    ((class Rectangle*)sh[2])->set_p2(p2);


    sh[2]->Paint();
    // left tape
    p1 = Vec(anchor.getX() - w / 4, anchor.getY() - h / 2 + o);

    sh[0] = new Circle(o);
    sh[0]->setAnchor(anchor);
    ((Circle*)sh[0])->set_ori(p1);
    sh[0]->Paint();
    // right tape
    p1 = Vec(anchor.getX() + w / 4, anchor.getY() - h / 2 + o);

    sh[1] = new Circle(o);
    sh[1]->setAnchor(anchor);
    ((Circle*)sh[1])->set_ori(p1);
    sh[1]->Paint();
    // top
    p1 = {anchor.getX() - 3 * w / 8, anchor.getY() + o / 2};
    p2 = {anchor.getX() +  3 * w / 8, anchor.getY() + o / 2};
    Vec p3 = {anchor.getX() + w / 4, anchor.getY() + h / 2};
    Vec p4 = {anchor.getX() -   w / 4, anchor.getY() + h / 2};

    sh[3] = new Quad();
    sh[3]->setAnchor(anchor);
    ((Quad*)sh[3])->set_p1(p1);
    ((Quad*)sh[3])->set_p2(p2);
    ((Quad*)sh[3])->set_p3(p3);
    ((Quad*)sh[3])->set_p4(p4);
    sh[3]->Paint();
}
Group::~Group()
{
    for (int i = 0; i < sh_num; i++)
    {
        delete sh[i];
    }
}

UFO::UFO(Vec anchor, float radius, float height, float width) {
    // init
    this->anchor = anchor;
    w = width;
    h = height;
    this->radius = radius;
    sh = new ColoredFig*[5];
    sh_num=5;
    // foot
    Vec p1 = Vec(anchor.getX() - 3*h , anchor.getY() - 2 * h );
    Vec p2 = Vec(anchor.getX() - h , anchor.getY() - h );
    sh[1]=new class Rectangle();
    sh[1]->setAnchor(anchor);
    ((class Rectangle*)sh[1])->set_p1(p1);
    ((class Rectangle*)sh[1])->set_p2(p2);

    p1 = Vec(anchor.getX() + h , anchor.getY() - 2 * h);
    p2 = Vec(anchor.getX() + 3 * h, anchor.getY() - h );
    sh[2]=new class Rectangle();
    sh[2]->setAnchor(anchor);
    ((class Rectangle*)sh[2])->set_p1(p1);
    ((class Rectangle*)sh[2])->set_p2(p2);

    sh[1]->Paint();
    sh[2]->Paint();

    // body
    
    p1=Vec(anchor.getX(),anchor.getY()-h);
    sh[0] = new SemiCircle;
    sh[0]->setAnchor(anchor);
    ((SemiCircle*)sh[0])->set_ori(p1);
    ((SemiCircle*)sh[0])->set_start(p1+Vec(radius,.0));

    sh[0]->Paint();

    // head1
    p1 = Vec(radius*cosf(PI/3) + anchor.getX(), radius*sinf(PI/3) + anchor.getY() - h );
    p2 = p1 + Vec(0.1,-0.1);
    Vec p3 = Vec(1.5*radius*cosf(PI/3) + anchor.getX(), 1.5*radius*sinf(PI/3) + anchor.getY() - h );
    Vec p4 = p3 + Vec(0.1,-0.1);
    sh[3]=new Quad();
    sh[3]->setAnchor(anchor);
    ((class Quad*)sh[3])->set_p1(p1);
    ((class Quad*)sh[3])->set_p2(p2);
    ((class Quad*)sh[3])->set_p3(p4);
    ((class Quad*)sh[3])->set_p4(p3);

    //head2
    p1 = Vec(radius*cosf(2*PI/3) + anchor.getX(), radius*sinf(2*PI/3) + anchor.getY() - h );
    p2 = p1 + Vec(-0.1,-0.1);
    p3 = Vec(1.5*radius*cosf(2*PI/3) + anchor.getX(), 1.5*radius*sinf(2*PI/3) + anchor.getY() - h );
    p4 = p3 + Vec(-0.1,-0.1);
    sh[4]=new Quad();
    sh[4]->setAnchor(anchor);
    ((class Quad*)sh[4])->set_p1(p1);
    ((class Quad*)sh[4])->set_p2(p2);
    ((class Quad*)sh[4])->set_p3(p4);
    ((class Quad*)sh[4])->set_p4(p3);

    sh[3]->Paint();
    sh[4]->Paint();

}

Spacecraft::Spacecraft(Vec anchor, float width, float height, float owidth) {
    // init
    this->anchor = anchor;
    w = width;
    h = height;
    o=owidth;
    sh = new ColoredFig*[8];
    sh_num=8;
    // body
    Vec p1 = Vec(anchor.getX() - w/2 , anchor.getY() - h/2 );
    Vec p2 = Vec(anchor.getX() +w/2 , anchor.getY() + h /2);
    sh[1]=new class Rectangle();
    sh[1]->setAnchor(anchor);
    ((class Rectangle*)sh[1])->set_p1(p1);
    ((class Rectangle*)sh[1])->set_p2(p2);

    //mouth
    p1 = Vec(anchor.getX() - 2*o , anchor.getY() );
    p2 = Vec(anchor.getX() + 2*o, anchor.getY() +h/10 );
    sh[2]=new class Rectangle();
    sh[2]->setAnchor(anchor);
    ((class Rectangle*)sh[2])->set_p1(p1);
    ((class Rectangle*)sh[2])->set_p2(p2);
    
    sh[1]->Paint();
    sh[2]->Paint();
    
    // eyes
    p1 = Vec(anchor.getX() - 3*w/8 , anchor.getY() + h/4 );
    p2 = Vec(anchor.getX() - 3*w/8 +2.5*o , anchor.getY() + h /4 + h/20);
    sh[3]=new class Rectangle();
    sh[3]->setAnchor(anchor);
    ((class Rectangle*)sh[3])->set_p1(p1);
    ((class Rectangle*)sh[3])->set_p2(p2);
    
    p1 = Vec(anchor.getX() + 3*w/8-2.5*o , anchor.getY() +h/4 );
    p2 = Vec(anchor.getX() + 3*w/8, anchor.getY() +h/4+h/20 );
    sh[4]=new class Rectangle();
    sh[4]->setAnchor(anchor);
    ((class Rectangle*)sh[4])->set_p1(p1);
    ((class Rectangle*)sh[4])->set_p2(p2);
    
    sh[3]->Paint();
    sh[4]->Paint();

    // head
    p1= Vec(anchor.getX() - w/2 , anchor.getY() + h/2);
    p2= Vec(anchor.getX() + w/2 , anchor.getY() + h/2);
    Vec p3=Vec(anchor.getX()  , anchor.getY() + h/2+w/2);
    sh[0]=new Triangle();
    sh[0]->setAnchor(anchor);
    ((class Triangle*)sh[0])->set_p1(p1);
    ((class Triangle*)sh[0])->set_p2(p2);
    ((class Triangle*)sh[0])->set_p3(p3);
    sh[0]->Paint();

    // left wing
    p1= Vec(anchor.getX() - w/2 , anchor.getY() );
    p2=Vec(anchor.getX()-w/2, anchor.getY() - h/2);
    p3=Vec(anchor.getX()-w, anchor.getY() - h/2);
    sh[5]=new Triangle();
    sh[5]->setAnchor(anchor);
    ((class Triangle*)sh[5])->set_p1(p1);
    ((class Triangle*)sh[5])->set_p2(p2);
    ((class Triangle*)sh[5])->set_p3(p3);
    sh[5]->Paint();

    // right wings
    p1= Vec(anchor.getX() + w/2 , anchor.getY() );
    p2=Vec(anchor.getX()+w/2, anchor.getY() - h/2);
    p3=Vec(anchor.getX()+w, anchor.getY() - h/2);
    sh[6]=new Triangle();
    sh[6]->setAnchor(anchor);
    ((Triangle*)sh[6])->set_p1(p1);
    ((Triangle*)sh[6])->set_p2(p2);
    ((Triangle*)sh[6])->set_p3(p3);
    sh[6]->Paint();

    //tails
    p1=Vec(anchor.getX()-w/2, anchor.getY() - h/2);
    p3=Vec(anchor.getX()+w/2+w/4, anchor.getY() - h/2-w/2);
    Vec p4=Vec(anchor.getX()-w/2-w/4, anchor.getY() - h/2-w/2);
    sh[7]=new Quad();
    sh[7]->setAnchor(anchor);
    ((Quad*)sh[7])->set_p1(p1);
    ((Quad*)sh[7])->set_p2(p2);
    ((Quad*)sh[7])->set_p3(p3);
    ((Quad*)sh[7])->set_p4(p4);
    sh[7]->Paint();

}

