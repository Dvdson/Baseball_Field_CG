//
// Created by wmarques on 25/08/16.
//

#ifndef BASEBALL_FIELD_CG_STRAIGHTLINEANDCIRCLE_H
#define BASEBALL_FIELD_CG_STRAIGHTLINEANDCIRCLE_H

#include <iostream>
#include <GL/gl.h>
#include <stdlib.h>
#include <math.h>
#define PI 3.14159265359

void drawStraightLine(int ax, int ay, int bx, int by) {
    int pointAmount = 1024;

    float x = (bx - ax) / (float)pointAmount;
    float y = (by - ay) / (float)pointAmount;

    for (int j = 0; j < pointAmount; ++j) {
        glVertex2f((j * x) + ax, (j * y) + ay);
    }
}

void drawCircle(int xCenter, int yCenter, int radius) {
    double theta;
    int pointAmount = 1024;
    double x,y;

    for (int i = 0; i < pointAmount; ++i) {
        theta = i * (2*PI)/pointAmount;
        x = xCenter + (radius * cos(theta));
        y = yCenter + (radius * sin(theta)) ;

        glVertex2i((GLint)x,(GLint)y);
    }
}

void drawSemiCircle(int xCenter, int yCenter, int radius) {
    double theta;
    int pointAmount = 1024;
    double x,y;

    for (int i = 0; i < pointAmount; ++i) {
        theta = i * (2*PI)/pointAmount;
        x = xCenter + (radius * cos(theta));
        y = yCenter + (radius * sin(theta)) ;

        if (y <= yCenter) {
            glVertex2i((GLint)x,(GLint)y);
        }
    }
}

#endif //BASEBALL_FIELD_CG_STRAIGHTLINEANDCIRCLE_H
