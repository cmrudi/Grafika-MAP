
#include <iostream>
#include "poligon.h"
#include "parser.h"



int main(int argc, char** argv){
    FramePanel panelSmall(100, 100, 50, 50);
    FramePanel panelMain(550, 500, 0, 0);
    FramePanel panelBig(500, 500, 550, 0);
    FramePanel panelMiniMap(100, 100, 250, 600);
    Framebuffer fp;
    Parser parse;
    parse.parseAdi("bangunan.txt");
    parse.parseTree("tree.txt");
    std::vector<Poligon> vPoligon;
    std::vector<std::vector<Point>> v;
    v = parse.getPoints();
    Parser parse2;
    parse2.parseAdi("jalan.txt");
    std::vector<std::vector<Point>> PJalan;
    PJalan = parse2.getPoints();

    cout << vPoligon.size() << endl;
    

    bool tree, build, road;
    tree = build = road = false;
    
    while(1){
        char inp;
        cin >> inp;
        if(inp == 'a'){
            if(panelSmall.getXMin() > 10){
                panelSmall.setXMin(panelSmall.getXMin() - 10);
            }
        }else if(inp == 's'){
            if(panelSmall.getYMin() < panelMain.getYSize() - panelSmall.getYSize()){
                panelSmall.setYMin(panelSmall.getYMin() + 10);
            }
        }else if (inp == 'd'){
            if(panelSmall.getXMin() < panelMain.getXSize() - panelSmall.getXSize()){
                panelSmall.setXMin(panelSmall.getXMin() + 10);
            }
        }else if(inp == 'w'){
            if(panelSmall.getYMin() > 10){
                panelSmall.setYMin(panelSmall.getYMin() - 10);
            }
        }else if(inp == 'z'){
            panelSmall.setXSize(panelSmall.getXSize()-10);
            panelSmall.setYSize(panelSmall.getYSize()-10);
        }else if(inp == 'x'){
            panelSmall.setXSize(panelSmall.getXSize()+10);
            panelSmall.setYSize(panelSmall.getYSize()+10);
        }else if(inp == 'e'){
            break;
        }else if(inp == 'b'){
            if(build){
                build = false;
            }else{
                build = true;
            }
        }else if(inp == 't'){
            if(tree){
                tree = false;
            }else{
                tree = true;
            }
        }else if(inp == 'r'){
            if(road){
                road = false;
            }else{
                road = true;
            }
        }
        if(build){ 
            //Draw Bangunan
            for(int i = 0; i < v.size(); i++){
                Poligon Shape = Poligon();
                Shape.makeLineFromArrPoint(v[i]);
                vPoligon.push_back(Shape);
                Shape.draw(&panelMain);
            }
        }

        if(tree){
            //Draw Tree
            std::vector<Point> PTree;
            PTree = parse.getTrees(); 
            for(int i = 0; i < PTree.size(); i++){
                Poligon Shape = Poligon();
                Shape.drawTree(PTree[i]);
                vPoligon.push_back(Shape);
                Shape.draw(&panelMain);
            }
        }

        if(road){
            //draw Jalan
            for(int i = 0; i < PJalan.size(); i++){
                Poligon Shape = Poligon();
                Shape.makeLineFromArrPoint(PJalan[i]);
                Shape.setLineColor(Color::RED);
                Shape.setAllLineColor();
                vPoligon.push_back(Shape);
                Shape.draw(&panelMain);
            }
        }

        //Minimap
        for(int i = 0; i < vPoligon.size(); i++){
            Poligon Shape = Poligon();
            Shape = vPoligon[i];
            Shape.scalePolygon(0.25,0.25);
            Shape.draw(&panelMiniMap);
        }

        int size = vPoligon.size();
        for(int i = 0; i<size;i++){
            vPoligon[i].drawInside(&panelSmall, &panelBig);
        }
        fp.drawFrame(panelMain);
        fp.drawFrame(panelMiniMap);
        fp.drawFrame(panelBig);
        fp.drawFrame(panelSmall);
        fp.Draw();
        panelMain.EmptyFrame();
        panelSmall.EmptyFrame();
        panelBig.EmptyFrame();
        vPoligon.clear();
    }

    return 0;
}
