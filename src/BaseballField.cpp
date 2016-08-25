#include <iostream>
#include <GL/glut.h>
#include "headers/Bresenham.h"
#include "headers/StraightLineAndCircle.h"

using namespace std;

bool isBresenhan = false;

//< Data of the external cicle >
int xCenter = 384;
int yCenter = 580;
int radius = 270;
//</ Data of the external cicle >

//< Data of the internal cicle >
int xIcenter = xCenter;
int yIcenter = (yCenter+radius)-200;
int iRadius = 160;
//</ Data of the internal cicle >

//<Coordinates to draw bleacher>
int bleacherX = 0;
int bleacherY = 0;
int bleacherCount = 0;
//</Coordinates to draw bleacher>

void drawExternalField() {

    GLint x0=400, y0=500;

    glColor3f(0.2,.67,0.2);
    glBegin(GL_POLYGON);
    if (isBresenhan) {
        bresenhamLine(x0,y0,600,300);
        bresenhamLine(x0,y0,200,300);
        bresenhamCicle(x0,y0,283);
    } else {
        drawStraightLine(xCenter,(yCenter+radius),(xCenter+radius),yCenter);
        drawStraightLine(xCenter,(yCenter+radius),(xCenter-radius),yCenter);
        drawSemiCircle(xCenter,yCenter,radius);
    }
    glEnd();
}

void drawInternalField() {

    glColor3f(.8,.6,.2);
    glBegin(GL_POLYGON);
    if (isBresenhan) {
        /*bresenhamLine((xIcenter+iRadius),yIcenter,xIcenter,(yIcenter+iRadius));
        bresenhamLine(xIcenter,(yIcenter+iRadius),(xIcenter-iRadius),yIcenter);
        bresenhamCicle(xIcenter,yIcenter,iRadius);*/
    } else {
        drawStraightLine((xIcenter+iRadius),yIcenter,xIcenter,(yIcenter+iRadius));
        drawStraightLine(xIcenter,(yIcenter+iRadius),(xIcenter-iRadius),yIcenter);
        drawSemiCircle(xIcenter,yIcenter,iRadius);
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

    if (isBresenhan) {

    } else {
        glColor3f(0.2,.67,0.2);
        glBegin(GL_POLYGON);
            drawStraightLine(ax,ay,bx,by);
            drawStraightLine(bx,by,cx,cy);
            drawStraightLine(cx,cy,dx,dy);
            drawStraightLine(dx,dy,ax,ay);
        glEnd();

        glColor3f(.8,.6,.2);
        glBegin(GL_POLYGON);
            drawCircle(xCenter,yCenter+(iRadius/1.7),20);
        glEnd();
    }


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

    if (isBresenhan) {

    } else {
        glColor3f(.8,.6,.2);
        glBegin(GL_POLYGON);
            drawCircle(ax,ay,30);
        glEnd();

        glColor3f(.8,.6,.2);
        glBegin(GL_POLYGON);
            drawCircle(bx,by,20);
        glEnd();

        glColor3f(.8,.6,.2);
        glBegin(GL_POLYGON);
            drawCircle(cx,cy,20);
        glEnd();

        glColor3f(.8,.6,.2);
        glBegin(GL_POLYGON);
            drawCircle(dx,dy,20);
        glEnd();

        glColor3f(1,1,1);
        glBegin(GL_POINTS);
            glVertex2i((GLint) ax, (GLint) ay);
            glVertex2i((GLint) bx, (GLint) by);
            glVertex2i((GLint) cx, (GLint) cy);
            glVertex2i((GLint) dx, (GLint) dy);
        glEnd();
    }
}

void mouseDrawBleacher(GLint button, GLint action, GLint xMouse, GLint yMouse) {

    int dx = xMouse;
    int dy = 900 - yMouse;

    if (button == GLUT_LEFT_BUTTON && action == GLUT_DOWN) {

        glColor3f(.2,.2,.2);

        if (bleacherX != 0 && bleacherY != 0) {

            glBegin(GL_POINTS);
            if (isBresenhan) {
                bresenhamLine(bleacherX,bleacherY,dx,dy);
            } else {
                drawStraightLine(bleacherX,bleacherY,dx,dy);
            }
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

    glClear(GL_COLOR_BUFFER_BIT);

    glPointSize(10);

    /*glColor3f(1,0,0);
    glBegin(GL_POINTS);
        //drawStraightLine(x0,y0,600,300);
        //drawStraightLine(x0,y0,200,300);
        //drawSemiCircle(x0,y0,283);
        bresenhamLine(x0,y0,600,300);
        bresenhamLine(x0,y0,200,300);
        bresenhamCicle(x0,y0,283);
    glEnd();*/

    drawExternalField();
    drawInternalField();
    drawPitcherGround();
    drawHomePlateAndBases();

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