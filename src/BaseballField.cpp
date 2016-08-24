#include <iostream>
#include <GL/glut.h>
#include <math.h>
#include "Bresenham.h"
#define PI 3.14159265359

using namespace std;

//chose between simple and bresenhan algorithms

//

//< Data of the external cicle >
int xCenter = 384;
int yCenter = 580;
int r = 270;
int pointAmount = 1024;
double theta;
double cx;
double cy;
//</ Data of the external cicle >

//<Data of the external lines>
float dx = ((xCenter+r) - xCenter) / (float)pointAmount;
float dy = (yCenter - (yCenter+r)) / (float)pointAmount;
float jdx,jdy;
//</Data of the external lines>

//< Data of the internal cicle >
int xIcenter = xCenter;
int yIcenter = (yCenter+r)-200;
int iRadius = 160;
int iPointAmount = 1024;
double iTheta;
double icx = 0;
double icy = 0;
//</ Data of the internal cicle >

//<Data of the internal lines>
float idx = ((xIcenter+iRadius) - xIcenter) / (float)iPointAmount;
float idy = (yIcenter - (yIcenter+iRadius)) / (float)iPointAmount;
float ijdx,ijdy;
//</Data of the internal lines>

int bleacherX = 0;
int bleacherY = 0;
int bleacherCount = 0;

void simpleLine(GLfloat x0, GLfloat y0, GLfloat x1, GLfloat y1){

    GLint x,y,incY=1;
    GLfloat a;

    if(x0 > x1 ){
        float aux = x0;
        x0 = x1;
        x1 = aux;
        aux = y0;
        y0 = y1;
        y1 = aux;
    }
    x = (int)(x0+0.5);
    y = (int)(y0+0.5);
    a = (y1-y0)/(x1-x0);
    glVertex2i(x,y);
    if(a<0) incY=-1;

    while(x<x1||abs(y)<abs(y1)){
        if(abs(a)<1.0){
            x = x+1;
            y = (int)(a*(x - x0) + y0 + 0.5);
        }else{
            y = y+incY;
            x = (int)(x0 + (y-y0)/a + 0.5);
        }
        glVertex2i(x,y);
    }
}

void simpleCircle(int x0, int y0, int r) {
    
    int x, y, r2;

    r2 = r * r;
//    glVertex2i( x0, y0 + r);
//    glVertex2i( x0, y0 - r);
//    glVertex2i( x0 + r, y0);
//    glVertex2i( x0 - r, y0);

    y = r;
    x = 1;
    y = (int) (sqrt(r2 - 1) + 0.5);
    while (x < y) {
        //glVertex2i( x0 + x, y0 + y);
        glVertex2i( x0 + x, y0 - y);
        //glVertex2i( x0 - x, y0 + y);
        glVertex2i( x0 - x, y0 - y);
//        glVertex2i( x0 + y, y0 + x);
//        glVertex2i( x0 + y, y0 - x);
//        glVertex2i( x0 - y, y0 + x);
//        glVertex2i( x0 - y, y0 - x);
        x += 1;
        y = (int) (sqrt(r2 - x*x) + 0.5);
    }
    if (x == y) {
//        glVertex2i( x0 + x, y0 + y);
//        glVertex2i( x0 + x, y0 - y);
//        glVertex2i( x0 - x, y0 + y);
//        glVertex2i( x0 - x, y0 - y);
    }

}

void drawExternalField() {

    glColor3f(0.2,.67,0.2);
    glBegin(GL_POLYGON);
    //Draw the first line.
    for (int j = 0; j < pointAmount; ++j) {
        jdx = (j * dx) + xCenter;
        jdy = (j * dy) + (yCenter+r);
        glVertex2f(jdx, jdy);
    }

    //Draw the half-circle and connect with the first vertex.
    for (int i = 0; i < pointAmount; ++i) {
        theta = i * (2*PI)/pointAmount;
        cx = xCenter + (r * cos(theta));
        cy = yCenter + (r * sin(theta)) ;

        if (cy <= jdy) {
            glVertex2i((GLint)cx,(GLint)cy);
        }
    }
    glEnd();
}

void drawInternalField() {

    glColor3f(.8,.6,.2);
    glBegin(GL_POLYGON);
    //Draw the first line.
    for (int j = 0; j < iPointAmount; ++j) {
        ijdx = (j * idx) + xIcenter;
        ijdy = (j * idy) + (yIcenter+iRadius);
        glVertex2f(ijdx, ijdy);
    }

    //Draw the half-circle and connect with the first vertex.
    for (int i = 0; i < pointAmount; ++i) {
        iTheta = i * (2*PI)/iPointAmount;
        icx = xIcenter + (iRadius * cos(iTheta));
        icy = yIcenter + (iRadius * sin(iTheta)) ;

        if (icy <= ijdy) {
            glVertex2i((GLint)icx,(GLint)icy);
        }
    }
    glEnd();
}

void drawPitcherGround() {
    //<Points>
    int ax = xIcenter;
    int ay = yIcenter + 25 + iRadius/1.5;

    int bx = xIcenter + iRadius/1.5;
    int by = yIcenter + 25;

    int cx = xIcenter;
    int cy = yIcenter + 25 - iRadius/1.5;

    int dx = xIcenter - iRadius/1.5;
    int dy = yIcenter + 25 ;
    //</Points>

    int auxx = (bx - ax) / (float)iPointAmount;
    int auxy = (by - ay) / (float)iPointAmount;

    glColor3f(0.2,.67,0.2);
    glBegin(GL_POLYGON);
    for (int j = 0; j < iPointAmount; ++j) {
        glVertex2f((j * auxx) + ax, (j * auxy) + ay);
    }

    auxx = (cx - bx) / (float)iPointAmount;
    auxy = (cy - by) / (float)iPointAmount;

    for (int j = 0; j < iPointAmount; ++j) {
        glVertex2f((j * auxx) + bx, (j * auxy) + by);
    }

    auxx = (dx - cx) / (float)iPointAmount;
    auxy = (dy - cy) / (float)iPointAmount;

    for (int j = 0; j < iPointAmount; ++j) {
        glVertex2f((j * auxx) + cx, (j * auxy) + cy);
    }

    auxx = (ax - dx) / (float)iPointAmount;
    auxy = (ay - dy) / (float)iPointAmount;

    for (int j = 0; j < iPointAmount; ++j) {
        glVertex2f((j * auxx) + dx, (j * auxy) + dy);
    }
    glEnd();

    glColor3f(.8,.6,.2);
    glBegin(GL_POLYGON);
    for (int i = 0; i < iPointAmount; ++i) {
        theta = i * (2*PI)/iPointAmount;
        glVertex2f(xCenter + (20 * cos(theta)), yCenter+(iRadius/1.7) + (20 * sin(theta)));
    }
    glEnd();
}

void drawHomePlateAndBases() {
    //<Points>
    int ax = xIcenter;
    int ay = yIcenter + 25 + iRadius/1.5;

    int bx = xIcenter + iRadius/1.5;
    int by = yIcenter + 25;

    int cx = xIcenter;
    int cy = yIcenter + 25 - iRadius/1.5;

    int dx = xIcenter - iRadius/1.5;
    int dy = yIcenter + 25 ;
    //</Points>

    //<Home Plate>
    glColor3f(.8,.6,.2);
    glBegin(GL_POLYGON);
    for (int i = 0; i < iPointAmount; ++i) {
        theta = i * (2*PI)/iPointAmount;
        glVertex2f(ax + (30 * cos(theta)), ay + (30 * sin(theta)));
    }
    glEnd();

    //</Home Plate>

    //1º Base.
    glColor3f(.8,.6,.2);
    glBegin(GL_POLYGON);
    for (int i = 0; i < iPointAmount; ++i) {
        theta = i * (2*PI)/iPointAmount;
        glVertex2f(bx + (20 * cos(theta)), by + (20 * sin(theta)));
    }
    glEnd();

    //2º Base.
    glColor3f(.8,.6,.2);
    glBegin(GL_POLYGON);
    for (int i = 0; i < iPointAmount; ++i) {
        theta = i * (2*PI)/iPointAmount;
        glVertex2f(cx + (20 * cos(theta)), cy + (20 * sin(theta)));
    }
    glEnd();

    //3º base.
    glColor3f(.8,.6,.2);
    glBegin(GL_POLYGON);
    for (int i = 0; i < iPointAmount; ++i) {
        theta = i * (2*PI)/iPointAmount;
        glVertex2f(dx + (20 * cos(theta)), dy + (20 * sin(theta)));
    }
    glEnd();

    glColor3f(1,1,1);
    glPointSize(10);
    glBegin(GL_POINTS);
    glVertex2i((GLint) ax, (GLint) ay);
    glVertex2i((GLint) bx, (GLint) by);
    glVertex2i((GLint) cx, (GLint) cy);
    glVertex2i((GLint) dx, (GLint) dy);
    glEnd();
}

void mouseDrawBleacher(GLint button, GLint action, GLint xMouse, GLint yMouse) {

    int dx = xMouse;
    int dy = 900 - yMouse;

    cout << "("+std::to_string(xMouse)+", "+ to_string(yMouse)+")" << endl;

    if (button == GLUT_LEFT_BUTTON && action == GLUT_DOWN) {

        glPointSize(2);
        glColor3f(.2,.2,.2);

        if (bleacherX != 0 && bleacherY != 0) {

            glBegin(GL_POINTS);
                simpleLine(bleacherX,bleacherY,dx,dy);
            glEnd();

            ++bleacherCount;
        }

        glBegin(GL_POINTS);
        glVertex2i(dx, dy);
        glEnd();

        bleacherX = dx;
        bleacherY = dy;

        if (bleacherCount > 3) {
            bleacherX = 0;
            bleacherY = 0;
            bleacherCount = 0;
        }
    }

    glFlush();
}

void init(void) {

    glClearColor(1.0, 1.0, 1.0, 1.0);

    glMatrixMode(GL_PROJECTION);

    glOrtho(0.0, 768.0, 0.0, 900.0, -1.0, 1.0);

}

void display(void) {

    GLint x0=400, y0=500;

    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1,0,0);
    glBegin(GL_POINTS);
        simpleLine(x0,y0,600,300);
        simpleLine(x0,y0,200,300);
        simpleCircle(x0,y0,283);
//        bresenhamLine(x0,y0,600,300);
//        bresenhamLine(x0,y0,200,300);
//        bresenhamCicle(x0,y0,283);
    glEnd();

//    drawExternalField();
//    drawInternalField();
//    drawPitcherGround();
//    drawHomePlateAndBases();

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
    glutMouseFunc(mouseDrawBleacher);

    glutMainLoop();

    return 0;
}