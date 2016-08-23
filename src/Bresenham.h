//
// Created by dvdson on 8/22/16.
//

#ifndef BASEBALL_FIELD_CG_BRESENHAM_H
#define BASEBALL_FIELD_CG_BRESENHAM_H

#include <GL/gl.h>
#include <stdlib.h>

void bresenhamLine(int x1, int y1, int x2, int y2){

    int dx,dy,x,y,d,incNE,incE, incX = 1 ,incY = 1;
    float angle;

    //troca caso o vetor seja direcionado para a esquerda
    if(x2 < x1){
        int aux = x1;
        x1 = x2;
        x2 = aux;
        aux = y1;
        y1 = y2;
        y2 = aux;
    }

    //initial variables
    dx = x2 - x1;
    dy = y2 - y1;

    if(dy < 0) incY = -1;

    if(dx >= abs(dy)) {
        d = 2 * dy - dx;
        incE = 2*dy;
        incNE = 2*(dy - dx);
    }else{
        d = 2 * dx - dy;
        incE = 2*dx;
        incNE = 2*(dx - dy);
    }


    x = x1;
    y = y1;

    //first point and the sequentials
    glVertex2i(x,y);
    while(x < x2 || y < y2) {
        if(d<=0) {
            d = d + incE;

            if(dx >= abs(dy)) x+=incX;
            else y+= incY;

        } else {
            d = d + incNE;
            x+=incX;
            y+=incY;
        }
        glVertex2f(x,y);
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
            d = d + 2 * x + 3;
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
