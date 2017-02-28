#ifndef Line_H
#define Line_H

#include "../src/framebuffer.h"
#include "shape.h"

class Line : public Shape
{
    public:
        Line() : p1(), p2(), c(), thick(1){}

        Line(Point p1, Point p2){
            (*this).p1 = p1;
            (*this).p2 = p2;
            (*this).c = Color::BLACK;
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

        void draw(FramePanel& a){
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
                        for(int k = 0; k < thick; k++)
                            for(int j = 0; j < thick; j++)
                                a.set(c,xn+k,yn+j);
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
                        for(int k = 0; k < thick; k++)
                            for(int j = 0; j < thick; j++)
                                a.set(c,xn+k,yn+j);
                    }
                    //scanf("%d", &inp);
                }
            } else {
                for (int i=0; i <dy; i++){
                    for(int k = 0; k < thick; k++){
                            for(int j = 0; j < thick; j++){
                                a.set(c,xn+k,yn+j);
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


    private:
        Point p1, p2;
        Color c;
        int thick;
};

#endif // Line_H
