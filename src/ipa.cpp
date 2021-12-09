#ifdef __MaxOSX__ 
#include <GLUT/glut.h>
#else
#include <GL/freeglut.h>
#endif

#include "Figure.h"
void display() {

	/* clear window */
	glClear(GL_COLOR_BUFFER_BIT);

	/* draw scene */
//    class Rectangle r;
//    r.setAnchor(Vec(.0,.0));
//    r.set_p1(Vec(-.5,-.5));
//    r.set_p2(Vec(.5,.5));
//    r.Paint();
//    r.rotate(0.5);
//    r.rotate(-.5);
//    r.draw();
//	Circle cr(.25);
//	cr.set_ori(Vec(0.5,0));
//	cr.setAnchor(Vec(.0,.0));
//	cr.Paint();
//	cr.draw();

//    Car c;
//    c.zoom(0.5);
//    c.rotate(0.5);
//    c.move(Vec(0.5,0));
//    c.draw();

//    UFO u;
//    u.draw();
    ImgFloor imgf;
    imgf.draw();
    ImgPlot imgp;
    imgp.draw();
//    Spacecraft spc;
//    spc.draw();
	/* flush drawing routines to the window */
	glFlush();

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

	/* tell GLUT to wait for events */
	glutMainLoop();

	return 0;

}
