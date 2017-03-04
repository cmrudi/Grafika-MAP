#include <ncurses.h>
#include <iostream>
#include "poligon.h"
#include "parser.h"
#include <pthread.h>

std::vector<Point> PTree;
std::vector<Point> PTree2;
FramePanel panelMain(700, 700, 0, 0);
Framebuffer a;
Parser parse;
Parser parse2;
Poligon p;





int main(int argc, char** argv){

    parse.parseTree("maze_point_2.txt");
    parse2.parseTree("maze_point.txt");
    PTree = parse.getTrees();
    PTree2 = parse2.getTrees();

    
    for(int i = 1; i < PTree.size(); i++){
        p.add(Line(PTree[i-1],PTree[i]));
    }
    p.add(Line(PTree[0],PTree[PTree.size()-1]));
    for(int i = 1; i < PTree.size(); i++){
        p.add(Line(PTree2[i-1],PTree2[i]));
    }
    p.add(Line(PTree2[0],PTree2[PTree2.size()-1]));
    p.scalePolygon(0.75,0.75);
    p.draw(&panelMain);
    a.drawFrame(panelMain);
    a.Draw();

    return 0;
}
