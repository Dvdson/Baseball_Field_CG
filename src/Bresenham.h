//
// Created by dvdson on 8/22/16.
//

#ifndef BASEBALL_FIELD_CG_BRESENHAM_H
#define BASEBALL_FIELD_CG_BRESENHAM_H

#include <iostream>
#include <GL/gl.h>
#include <stdlib.h>

#define PI 3.14159265359

void bresenhamLine(GLint x0, GLint y0, GLint x1, GLint y1){

    int dx = abs (x1 - x0);
    int dy = abs (y1 - y0);
    int x, y;
    if (dx >= dy) {
        int d = 2*dy-dx;
        int ds = 2*dy;
        int dt = 2*(dy-dx);
        if (x0 < x1) {
            x = x0;
            y = y0;
        }
        else
        {
            x = x1;
            y = y1;
            x1 = x0;
            y1 = y0;
        }
        glVertex2i (x, y);
        while (x < x1)
        {
            if (d < 0)
                d += ds;
            else {
                if (y < y1) {
                    y++;
                    d += dt;
                }
                else {
                    y--;
                    d += dt;
                }
            }
            x++;
            glVertex2i (x, y);
        }
    }
    else {
        int d = 2*dx-dy;
        int ds = 2*dx;
        int dt = 2*(dx-dy);
        if (y0 < y1) {
            x = x0;
            y = y0;
        }
        else {
            x = x1;
            y = y1;
            y1 = y0;
            x1 = x0;
        }
        glVertex2i (x, y);
        while (y < y1)
        {
            if (d < 0)
                d += ds;
            else {
                if (x > x1){
                    x--;
                    d += dt;
                } else {
                    x++;
                    d += dt;
                }
            }
            y++;
            glVertex2f (x, y);
        }
    }



}

void bresenhamCicle(int Xo, int Yo, int r) {


    int x=0,y=r,p=1-r;
    while(x<=y){
        //Here Transform each x,y coordinates by r pixels
//        glVertex2i(Xo+y, Yo+x);//0-45
//        glVertex2i(Xo+x, Yo+y);//45-90
//        glVertex2i(Xo-x, Yo+y);//90-135
//        glVertex2i(Xo-y, Yo+x);//135-180
//        glVertex2i(Xo-y, Yo-x);//180-225
        glVertex2i(Xo-x, Yo-y);//225-270
        glVertex2i(Xo+x, Yo-y);//270-315
//        glVertex2i(Xo+y, Yo-x);//315-360
        if(p<0)
            p=p+2*x+3;
        else{
            p=p+2*(x-y)+5;
            y--;
        }
        x++;
    }
}


#endif //BASEBALL_FIELD_CG_BRESENHAM_H
