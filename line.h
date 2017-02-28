#ifndef Line_H
#define Line_H

#include "framebuffer.h"
#include "shape.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <math.h>
#include <pthread.h>

class Line : public Shape
{
    public:
        Line() : p1(), p2(), c(), thick(1){}

        Line(Point p1, Point p2){
            (*this).p1 = p1;
            (*this).p2 = p2;
            (*this).c = Color::WHITE;
            thick = 1;
        }

        Line(Point p1, Point p2, Color c){
            (*this).p1 = p1;
            (*this).p2 = p2;
            (*this).c = c;
            thick = 1;
        }

        Line(Point p1, Point p2, Color c, int thickness){
            (*this).p1 = p1;
            (*this).p2 = p2;
            (*this).c = c;
            thick = thickness;
        }


        Line(int x1, int y1, int x2, int y2, Color c){
            p1 = Point(x1,y1);
            p2 = Point(x2, y2);
            (*this).c = c;
            thick = 1;
        }

        Line(int x1, int y1, int x2, int y2, Color c, int thickness){
            p1 = Point(x1,y1);
            p2 = Point(x2, y2);
            (*this).c = c;
            thick = thickness;
        }

        Line& operator= (const Line& l){
            p1 = l.p1;
            p2 = l.p2;
            c = l.c;
            thick = l.thick;

            return (*this);
        }



        Point getP1(){
            return p1;
        }

        Point getP2(){
            return p2;
        }

        Color getColor(){
            return c;
        }

        int getThickness(){
            return thick;
        }

        void setP1(Point P1){
            p1 = P1;
        }

        void setP2(Point P2){
            p2 = P2;
        }

        void setP1(int x, int y){
            p1 = Point(x,y);
        }

        void setP2(int x, int y){
            p2 = Point(x,y);
        }

        void setColor(Color C){
            c = C;
        }

        void setColor(char r, char g, char b, char a){
            c = Color(r,g,b,a);
        }

        void setThickness(int t){
            thick = t;
        }

        void draw(FramePanel* a){
            int xn=p1.getX(), yn=p1.getY();
            int dx=abs(p2.getX()-p1.getX());
            int dy=abs(p2.getY()-p1.getY());
            int p = 2*dy-dx;
            int inp;
            if(dx!=0){
                if (dx>dy){
                    for (int i=0;i<abs((p2.getX()-p1.getX()));i++){
                        if((p2.getX() > p1.getX())){
                            xn=xn+1;
                        } else {
                            xn=xn-1;
                        }
                        p=p+2*dy;
                        if (p>=0){
                            if ((p2.getY()-p1.getY())>0)
                                yn++;
                            else
                                yn--;
                            p-=2*dx;
                        }
                        if(xn < 0){
                            xn = 0;
                        }
                        if(yn < 0){
                            yn = 0;
                        }
                        if(xn > (*a).getXSize()-1){
                            xn = (*a).getXSize()-1;
                        }
                        if(yn > (*a).getYSize()){
                            yn = (*a).getYSize();
                        }
                        for(int k = 0; k < thick; k++)
                            for(int j = 0; j < thick; j++)
                                (*a).set(c,xn+k,yn+j);
                    }
                } else {
                    for (int i=0;i<abs(p2.getY()-p1.getY());i++){
                        if(p2.getY() > p1.getY()){
                            yn=yn+1;
                        } else {
                            yn=yn-1;
                        }
                        p=p+2*dx;
                        if (p>=0){
                            if (p2.getX()-p1.getX()>0)
                                xn++;
                            else
                                xn--;
                            p-=2*dy;
                        }
                        if(xn < 0){
                            xn = 0;
                        }
                        if(yn < 0){
                            yn = 0;
                        }
                        if(xn > (*a).getXSize()-1){
                            xn = (*a).getXSize()-1;
                        }
                        if(yn > (*a).getYSize()){
                            yn = (*a).getYSize();
                        }
                        for(int k = 0; k < thick; k++)
                            for(int j = 0; j < thick; j++){
                                (*a).set(c,xn+k,yn+j);
                            }
                    }
                    //scanf("%d", &inp);
                }
            } else {
                for (int i=0; i <dy; i++){
                    for(int k = 0; k < thick; k++){
                            for(int j = 0; j < thick; j++){
                                if(xn < 0){
                                    xn = 0;
                                }
                                if(yn < 0){
                                    yn = 0;
                                }
                                if(xn > (*a).getXSize()-1){
                                    xn = (*a).getXSize()-1;
                                }
                                if(yn > (*a).getYSize()){
                                    yn = (*a).getYSize();
                                }
                                (*a).set(c,xn+k,yn+j);
                            }
                    }   
                    if(p2.getY() > p1.getY()){
                        yn++;
                    }else{
                        yn--;
                    }
                }
            }
        }

        void scaleLine(float sx, float sy, const Point& center = Point()){
            p1.Scale(sx, sy, center);
            p2.Scale(sx, sy, center);
        }

        static const int INSIDE; // 0000
        static const int LEFT;   // 0001
        static const int RIGHT;  // 0010
        static const int BOTTOM; // 0100
        static const int TOP;    // 1000

        int ComputeOutCode(double x, double y, FramePanel& fp)
        {
            int code;
            int xmin = fp.getXMin();
            int ymin = fp.getYMin();
            int sizex = fp.getXSize();
            int sizey = fp.getYSize();

            code = INSIDE;          // initialised as being inside of [[clip window]]
            int xmax = xmin+sizex-1;
            int ymax = ymin+sizey-1;

            if (x < xmin)           // to the left of clip window
                code |= LEFT;
            else if (x > xmax)      // to the right of clip window
                code |= RIGHT;
            if (y < ymin)           // below the clip window
                code |= BOTTOM;
            else if (y > ymax)      // above the clip window
                code |= TOP;

            return code;
        }

        bool checkInsideFrame(FramePanel& fp, Line * line){
                // compute outcodes for P0, P1, and whatever point lies outside the clip rectangle
                int x0 = p1.getX();
                int y0 = p1.getY();
                int x1 = p2.getX();
                int y1 = p2.getY();
                int xmax = fp.getXSize()+fp.getXMin()-1;
                int xmin = fp.getXMin();
                int ymax = fp.getYSize()+fp.getYMin()-1;
                int ymin = fp.getYMin();

                int outcode0 = ComputeOutCode(x0, y0, fp);
                int outcode1 = ComputeOutCode(x1, y1, fp);
                bool accept = false;

                while (true) {
                    if (!(outcode0 | outcode1)) { // Bitwise OR is 0. Trivially accept and get out of loop
                        accept = true;
                        break;
                    } else if (outcode0 & outcode1) { // Bitwise AND is not 0. (implies both end points are in the same region outside the window). Reject and get out of loop
                        break;
                    } else {
                        // failed both tests, so calculate the line segment to clip
                        // from an outside point to an intersection with clip edge
                        double x, y;

                        // At least one endpoint is outside the clip rectangle; pick it.
                        int outcodeOut = outcode0 ? outcode0 : outcode1;

                        // Now find the intersection point;
                        // use formulas y = y0 + slope * (x - x0), x = x0 + (1 / slope) * (y - y0)
                        if (outcodeOut & TOP) {           // point is above the clip rectangle
                            x = x0 + (x1 - x0) * (ymax - y0) / (y1 - y0);
                            y = ymax;
                        } else if (outcodeOut & BOTTOM) { // point is below the clip rectangle
                            x = x0 + (x1 - x0) * (ymin - y0) / (y1 - y0);
                            y = ymin;
                        } else if (outcodeOut & RIGHT) {  // point is to the right of clip rectangle
                            y = y0 + (y1 - y0) * (xmax - x0) / (x1 - x0);
                            x = xmax;
                        } else if (outcodeOut & LEFT) {   // point is to the left of clip rectangle
                            y = y0 + (y1 - y0) * (xmin - x0) / (x1 - x0);
                            x = xmin;
                        }

                        // Now we move outside point to intersection point to clip
                        // and get ready for next pass.
                        if (outcodeOut == outcode0) {
                            x0 = x;
                            y0 = y;
                            outcode0 = ComputeOutCode(x0, y0, fp);
                        } else {
                            x1 = x;
                            y1 = y;
                            outcode1 = ComputeOutCode(x1, y1, fp);
                        }
                    }
                }
                if (accept) {
                    Point p_1 = Point(x0, y0);
                    Point p_2 = Point(x1, y1);
                    (*line) = Line(p_1, p_2);
                    (*line).setColor(c);
                    return true;
                }else{
                    return false;
                }
        }

        void moveLine(int x, int y){
            p1.setX(p1.getX()+x);
            p1.setY(p1.getY()+y);
            p2.setX(p2.getX()+x);
            p2.setY(p2.getY()+y);
        }

        void timesLine(float sx, float sy){
            p1.setX(p1.getX()*sx);
            p1.setY(p1.getY()*sy);
            p2.setX(p2.getX()*sx);
            p2.setY(p2.getY()*sy);
        }

        void printLine(){
            p1.printPoint();
            p2.printPoint();
            printf("\n");
        }

    private:
        Point p1, p2;
        Color c;
        int thick;
};

const int Line::INSIDE = 0; 
const int Line::LEFT = 1;   
const int Line::RIGHT = 2;  
const int Line::BOTTOM = 4; 
const int Line::TOP = 8;    

#endif // Line_H
