#include <iostream>
#include <GL/glut.h>
#include <math.h>
#define PI 3.14159265359

using namespace std;

//< Data of the external cicle >
int xCenter = 384;
int yCenter = 580;
int radius = 270;
int pointAmount = 1024;
double theta;
double cx;
double cy;
//</ Data of the external cicle >

//<Data of the external lines>
float dx = ((xCenter+radius) - xCenter) / (float)pointAmount;
float dy = (yCenter - (yCenter+radius)) / (float)pointAmount;
float jdx,jdy;
//</Data of the external lines>

//< Data of the internal cicle >
int xIcenter = xCenter;
int yIcenter = (yCenter+radius)-200;
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

void drawExternalField() {

    glColor3f(0.2,.67,0.2);
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
    if (button == GLUT_LEFT_BUTTON && action == GLUT_DOWN) {

        glPointSize(2);
        glColor3f(.2,.2,.2);
        int dx = xMouse;
        int dy = 900 - yMouse;

        if (bleacherX != 0 && bleacherY != 0) {
            float auxx = (dx - bleacherX) / (float)iPointAmount;
            float auxy = (dy - bleacherY) / (float)iPointAmount;

            glBegin(GL_POINTS);
            for (int j = 0; j < iPointAmount; ++j) {
                glVertex2f((j * auxx) + bleacherX, (j * auxy) + bleacherY);
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