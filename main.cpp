#include <ncurses.h>
#include <iostream>
#include <stdio.h>
#include "poligon.h"
#include "parser.h"
#include <pthread.h>

std::vector<Point> PTree;
std::vector<Point> PTree2;
FramePanel panelMain(700, 700, 0, 0);
FramePanel panelSmall(100, 100, 50, 50);
FramePanel panelBig(500, 500, 750, 0);
Framebuffer a;
Parser parse;
Parser parse2;
Poligon p;
pthread_t t_control;


void *controller(void *args){
    while(1){
        char c;
        c = getchar();

        if(c == 'j'){
            if(panelSmall.getXMin() > 10){
                panelSmall.setXMin(panelSmall.getXMin() - 10);
            }
        }else if(c == 'k'){
            if(panelSmall.getYMin() > 10){
                panelSmall.setYMin(panelSmall.getYMin() + 10);
            }
        }else if (c == 'l'){
            if(panelSmall.getXMin() < panelMain.getXSize() - panelSmall.getXMin()-10){
                panelSmall.setXMin(panelSmall.getXMin() + 10);
            }
        }else if(c == 'i'){
            if(panelSmall.getYMin() < panelMain.getXSize() - panelSmall.getYMin()){
                panelSmall.setYMin(panelSmall.getYMin() - 10);
            }
        }else if(c == 'b'){
            panelSmall.setXSize(panelSmall.getXSize()+10);
            panelSmall.setYSize(panelSmall.getYSize()+10);
        }else if(c == 'n'){
            panelSmall.setXSize(panelSmall.getXSize()-10);
            panelSmall.setYSize(panelSmall.getYSize()-10);
        }else if(c == 'm'){
            break;
        }
    }
}




int main(int argc, char** argv){

    // Read Text File
    parse.parseTree("maze_point_2.txt");
    parse2.parseTree("maze_point.txt");
    PTree = parse.getTrees();
    PTree2 = parse2.getTrees();
    /////////////////////////////////////

    
    // Insert Coordinat To Array
    for(int i = 1; i < PTree.size(); i++){
        p.add(Line(PTree[i-1],PTree[i]));
    }
    p.add(Line(PTree[0],PTree[PTree.size()-1]));
    for(int i = 1; i < PTree.size(); i++){
        p.add(Line(PTree2[i-1],PTree2[i]));
    }
    p.add(Line(PTree2[0],PTree2[PTree2.size()-1]));
    //////////////////////////////////////

    pthread_create(&t_control, NULL, controller, NULL);
    p.scalePolygon(0.75,0.75);

    while(1) {
         //ZoomSelector
        p.drawInside(&panelSmall, &panelBig);



        p.draw(&panelMain);
        a.drawFrame(panelMain);
        a.drawFrame(panelBig);
        a.drawFrame(panelSmall);
        a.Draw();

        panelMain.EmptyFrame();
        panelSmall.EmptyFrame();
        panelBig.EmptyFrame();
    }
    

    pthread_join(t_control, NULL);

    return 0;
}
