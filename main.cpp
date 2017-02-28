#include "framebuffer.h"
#include <iostream>
#include "line.h"
#include "poligon.h"

int main(int argc, char** argv){
    FramePanel b(500, 500);
    Framebuffer a;
    Color c;
    c= Color::WHITE;
    Point ax(1,2);
    a.setColor(c, ax);
    for(int i = 0; i<a.getXSize(); i++){
        for(int j = 0; j<a.getYSize(); j++){
            a.setColor(c, i,j);
        }
    }

    Line l(Point(100,200), Point(300,300), Color::BLACK, 10);
    l.draw(a);



    Poligon p;
    p.add(Line(Point(100,100), Point(150,100)));
    p.add(Line(Point(150,100), Point(150,300)));
    p.add(Line(Point(150,300), Point(100,300)));
    p.add(Line(Point(100,300), Point(100,100)));

    p.draw(b);

    a.drawFrame(b);
    a.Draw();
    sleep(10);
    p.setLineColor(Color::BLUE);
    p.scalePolygon(1.5, 1.5);
    
    p.draw(a);
    a.Draw();

    return 0;
}
