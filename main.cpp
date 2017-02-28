
#include <iostream>
#include "poligon.h"
#include "parser.h"

using namespace std;



int main(int argc, char** argv){
    FramePanel panelSmall(100, 100, 50, 50);
    FramePanel panelMain(500, 500, 10, 10);
    FramePanel panelBig(500, 500, 500, 0);
    Framebuffer a;
    Parser parse;
    parse.parseAdi("bgn.octet-stream");
    std::vector<Poligon> vPoligon;
    std::vector<std::vector<Point>> v;
    v = parse.getPoints();
    for(int i = 0; i < v.size(); i++){
        Poligon Shape = Poligon();
        Shape.makeLineFromArrPoint(v[i]);
        vPoligon.push_back(Shape);
        Shape.draw(&panelMain);
        //cout << "NEKONEKO" <<endl;
    }

    //draw semua
    a.drawFrame(panelMain);
    a.Draw();



    return 0;
}
