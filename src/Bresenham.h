//
// Created by dvdson on 8/22/16.
//

#ifndef BASEBALL_FIELD_CG_BRESENHAM_H
#define BASEBALL_FIELD_CG_BRESENHAM_H

#include <GL/gl.h>

void bresenhamLine(int x1, int y1, int x2, int y2){

    int dx,dy,x,y,d,incNE,incE;

    //initial variables
    dx = x2 - x1;
    dy = y2 - y1;
    d = 2 * dy - dx;
    incE = 2*dy;
    incNE = 2*(dy - dx);
    x = x1;
    y = y1;

    //first point and the sequentials
    glVertex2i(x,y);
    while(x < x2) {
        if(d<=0) {
            d = d + incE;
            ++x;
        } else {
            d = d + incNE;
            ++x;
            ++y;
        }
        glVertex2i(x,y);
    }

}

void bresenhamCicle(int Xo,int Yo, int r) {

    int x,y;
    float d;

    //initial variables
    x = 0;
    y = r;
    d = 5/4 - r;

    glVertex2i(x+Xo,y+Yo);
    while(y > x) {
        if( d < 0) {
            d = d+ 2 * x + 3;
            ++x;
        } else {
            d = d + 2 * (x - y) + 5;
            ++x;
            ++y;
        }
        glVertex2i(x+Xo,y+Yo);
    }

}


#endif //BASEBALL_FIELD_CG_BRESENHAM_H
