#ifdef __MaxOSX__ 
#include <GLUT/glut.h>
#else
#include <GL/freeglut.h>
#endif
#include <iostream>
#include <vector>
#include "Floor.h"
#include "Figure.h"
#include "Vehicle.h"
#include "Status.h"

using namespace std;

void display() {

	/* clear window */
	glClear(GL_COLOR_BUFFER_BIT);

	/* draw scene */
	//// Static Part
	///draw floor( first set with 1th floor)

	ImgFloor imgf;
	imgf.draw();
    //Floor f;
    static Floor f;
    f.set_time();
    if(f.get_slot()==NULL)
    {
        f.init_slot();
        f.create_slot();
    }
    else{
        f.draw_slot();
    }
    //std::cout<<f.get_time()<<std::endl;

    ///Here read from files and establish each car




    ///first find out every car --> monitor their motions
    // Car should be "statically" established (and modified) here according to the instruction from the user!


    ///the modifying function should mainly focuses on two parts
    // 1. the animation

    // 2. the activation
    //

    static vector<Vehicle> v;
    if(v.empty()){
        Read_Log(v,&f);
        f.set_v(&v);
    }
    /// search each car find potential changes
    vector<Vehicle>::iterator it;
    int i =0;
    int allv=v.size();
    for(it=v.begin();it!=v.end();it++){
        i++;
        
        if(it->get_type()==3){
            it->get_vehicle()->auto_zoom();
        }
        if(it->get_type()==2){
            it->get_vehicle()->auto_rotate();
        }
        change_status(&f,it,i,allv);
#ifdef OPEN_GL
        if(it->get_status()!=0&&it->get_status()!=10)
            it->get_vehicle()->draw();
#endif
    }
    bool flag=true;
    for(it=v.begin();it!=v.end();it++){
        if(!it->get_exit())
            flag= false;
    }
    if(flag==true)
    {
        cout<<"ALL Vehicles exit successfully! The program will end automatically"<<endl;
        exit(0);
    }





//    Spacecraft spc;
//    spc.draw();
    glutSwapBuffers();

	/* flush drawing routines to the window */
	glFlush();

}

void TimeStep(int n)
{
    glutTimerFunc((unsigned int)n, TimeStep, n);
    glutPostRedisplay();
}
int main(int argc, char *argv[]) {

	/* initialize GLUT, using any commandline parameters passed to the program */
	glutInit(&argc, argv);

	/* setup the size, position, and display mode for new windows */
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);
	glutInitDisplayMode(GLUT_RGB);

	/* create and set up a window */
	glutCreateWindow("Interstellar parking animation");
	glutDisplayFunc(display);
	//glutIdleFunc(display);
	glutTimerFunc(50, TimeStep, 50);
	/* tell GLUT to wait for events */
	glutMainLoop();

	return 0;

}
