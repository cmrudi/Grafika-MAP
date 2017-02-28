#include <ncurses.h>
#include <iostream>
#include "poligon.h"
#include "parser.h"
#include <pthread.h>

pthread_t t_bullet;
std::vector<Point> PTree;
std::vector<Poligon> vPoligon;
FramePanel panelMain(550, 500, 0, 0);
bool bTree = false;
bool bRoad = false;
bool bBuilding = false;
Parser parse2;
Framebuffer a;
std::vector< std::vector<Point> > v;
Parser parse;
std::vector< std::vector<Point> > PJalan;

FramePanel panelSmall(100, 100, 50, 50);
FramePanel panelBig(500, 500, 500, 0);
FramePanel panelMiniMap(100, 100, 250, 600);

void *controller(void *args){
    while(1){
        char c;
        c = getchar();
        if (c == 'q'){
            bTree = true;
        }
        if (c == 'w'){
            bTree = false;
        }
        if (c == 'a'){
            bRoad = true;
        }
        if (c == 's'){
            bRoad = false;
        }
        if (c == 'z'){
            bBuilding = true;
        }
        if (c == 'x'){
            bBuilding = false;
        }
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

void drawTree(){
    for(int i = 0; i < PTree.size(); i++){
        Poligon Shape = Poligon();
        Shape.drawTree(PTree[i]);
        Shape.draw(&panelMain);
    }
}

void drawBuilding(){
    for(int i = 0; i < v.size(); i++){
        Poligon Shape = Poligon();
        Shape.makeLineFromArrPoint(v[i]);
        Shape.draw(&panelMain);
    }   
}

void drawRoad(){
    for(int i = 0; i < PJalan.size(); i++){
        Poligon Shape = Poligon();
        Shape.makeLineFromArrPoint(PJalan[i]);
        Shape.setLineColor(Color::RED);
        Shape.setAllLineColor();
        Shape.draw(&panelMain);
    }
}

void poliRoad(){
    for(int i = 0; i < PJalan.size(); i++){
        Poligon Shape = Poligon();
        Shape.makeLineFromArrPoint(PJalan[i]);
        Shape.setLineColor(Color::RED);
        Shape.setAllLineColor();
        vPoligon.push_back(Shape);
    }
}

void poliBuild(){
    for(int i = 0; i < v.size(); i++){
        Poligon Shape = Poligon();
        Shape.makeLineFromArrPoint(v[i]);
        vPoligon.push_back(Shape);
    }   
}

void poliPlant(){
     for(int i = 0; i < PTree.size(); i++){
        Poligon Shape = Poligon();
        Shape.drawTree(PTree[i]);
        vPoligon.push_back(Shape);
    }
}

int main(int argc, char** argv){


   
    parse.parseAdi("bangunan.txt");
    parse.parseTree("tree.txt");
    v = parse.getPoints();
    PTree = parse.getTrees();
    parse2.parseAdi("jalan.txt");
    PJalan = parse2.getPoints();
    poliRoad();
    poliPlant();
    poliBuild();


    pthread_create(&t_bullet, NULL, controller, NULL);
    while(1){
        //Draw Bangunan
        if(bBuilding){   
            drawBuilding();
        }

        if(bTree){   
            //Draw Tree 
            drawTree();
        }

        if(bRoad){    
            drawRoad();
        }

        //Minimap
        for(int i = 0; i < vPoligon.size(); i++){
            Poligon Shape = Poligon();
            Shape = vPoligon[i];
            Shape.scalePolygon(0.5,0.5);
            Shape.draw(&panelMiniMap);
        }
        
        //ZoomSelector
        for(int i = 0; i<vPoligon.size();i++){
            vPoligon[i].drawInside(&panelSmall, &panelBig);
        }

        //draw semua
        a.drawFrame(panelMain);
        a.drawFrame(panelMiniMap);
        a.drawFrame(panelBig);
        a.drawFrame(panelSmall);
        a.Draw();

        panelMain.EmptyFrame();
        panelSmall.EmptyFrame();
        panelBig.EmptyFrame();
    }
    pthread_join(t_bullet, NULL);

    return 0;
}
