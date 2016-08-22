#include <iostream>
#include <GL/glut.h>
#include <math.h>
#define PI 3.14159265359

using namespace std;

//< Data of the cicle >
int xCenter = 384;
int yCenter = 580;
int radius = 270;
int pointAmount = 128;
float theta;
float cx;
float cy;
//</ Data of the cicle >

//<Data of the lines>
float dx = ((xCenter+radius) - xCenter) / (float)pointAmount;
float dy = (yCenter - (yCenter+radius)) / (float)pointAmount;
float  jdx,jdy;
//</Data of the lines>

void init(void) {

    glClearColor(0.0, 0.0, 0.0, 0.0);

    glMatrixMode(GL_PROJECTION);

    glOrtho(0.0, 768.0, 0.0, 900.0, -1.0, 1.0);

}

void display(void) {

    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(0,1,0);

    glBegin(GL_POLYGON);

    //Draw the first line.
    for (int j = 0; j < pointAmount; ++j) {
        jdx = (j * dx) + xCenter;
        jdy = (j * dy) + (yCenter+radius);
        glVertex2f(jdx, jdy);
    }

    //Draw the half-circle and connect with the first vertex.
    for (int i = 0; i < pointAmount; ++i) {
        theta = i * (2*PI)/pointAmount;
        cx = xCenter + (radius * cos(theta));
        cy = yCenter + (radius * sin(theta)) ;

        if (cy <= jdy) {
            glVertex2f(cx,cy);
        }
    }

    glEnd();

    glColor3f(1,0,0);
    glBegin(GL_LINES);
    glVertex2i(xCenter,yCenter);
    glVertex2i(xCenter,yCenter+radius);
    glEnd();

    glBegin(GL_LINES);
    glVertex2i(xCenter,yCenter);
    glVertex2i(xCenter+radius,yCenter);
    glEnd();

    glutSwapBuffers();
}

int main(int argc, char** argv) {

    glutInit(&argc,argv);

    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(768, 900);
    glutInitWindowPosition(50, 50);
    glutCreateWindow("Baseball Field");

    init();

    glutDisplayFunc(display);

    glutMainLoop();

    return 0;
}