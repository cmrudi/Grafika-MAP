
#include <iostream>
#include "poligon.h"
#include "parser.h"



int main(int argc, char** argv){
    FramePanel panelSmall(100, 100, 50, 50);
    FramePanel panelMain(550, 500, 0, 0);
    FramePanel panelBig(500, 500, 500, 0);
    FramePanel panelMiniMap(100, 100, 250, 600);
    Framebuffer a;
    Parser parse;
    parse.parseAdi("bgn.octet-stream");
    parse.parseTree("tree.txt");
    std::vector<Poligon> vPoligon;
    std::vector<std::vector<Point>> v;
    v = parse.getPoints();
    
    //Draw Bangunan
    for(int i = 0; i < v.size(); i++){
        Poligon Shape = Poligon();
        Shape.makeLineFromArrPoint(v[i]);
        vPoligon.push_back(Shape);
        Shape.draw(&panelMain);
    }

    //Draw Tree
    std::vector<Point> PTree;
    PTree = parse.getTrees(); 
    for(int i = 0; i < PTree.size(); i++){
        Poligon Shape = Poligon();
        Shape.drawTree(PTree[i]);
        vPoligon.push_back(Shape);
        Shape.draw(&panelMain);
    }

    //Minimap
    cout << vPoligon.size() << endl;
    for(int i = 0; i < vPoligon.size(); i++){
        Poligon Shape = Poligon();
        Shape = vPoligon[i];
        Shape.scalePolygon(-0.8,-0.8);
        Shape.draw(&panelMiniMap);
    }

    //ZoomSelector
    for(int i = 0; i<vPoligon.size();i++){
        //vPoligon[i].drawInside(&panelSmall, &panelBig);
    }

    

    //draw semua
    a.drawFrame(panelMain);
    a.drawFrame(panelMiniMap);
    a.drawFrame(panelBig);
    a.drawFrame(panelSmall);
    a.Draw();

    return 0;
}
