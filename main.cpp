#include <ncurses.h>
#include <iostream>
#include <stdio.h>
#include "poligon.h"
#include "parser.h"
#include "player.h"
#include <pthread.h>
#include <termios.h>
#include <thread>


static struct termios oldt;
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
Player player(100,100,0,255,0,&panelMain,&a);	

void *controller(void *args){
    while(1){
        char c;
        c = getchar();

        if(c == 'j'){
            if(panelSmall.getXMin() > 10){
                panelSmall.setXMin(panelSmall.getXMin() - 2);
                player.update_player(-10, 0, 3);
            }
        }else if(c == 'k'){
            if(panelSmall.getYMin() > 10){
                panelSmall.setYMin(panelSmall.getYMin() + 2);
                player.update_player(0, 10, 2);
            }
        }else if (c == 'l'){
            if(panelSmall.getXMin() < panelMain.getXSize() - panelSmall.getXMin()-10){
                panelSmall.setXMin(panelSmall.getXMin() + 2);
                player.update_player(10, 0, 1);
            }
        }else if(c == 'i'){
            if(panelSmall.getYMin() < panelMain.getXSize() - panelSmall.getYMin()){
                panelSmall.setYMin(panelSmall.getYMin() - 2);
                player.update_player(0, -10, 0);
            }
        }else if(c == 'b'){
            panelSmall.setXSize(panelSmall.getXSize()+10);
            panelSmall.setYSize(panelSmall.getYSize()+10);
        }else if(c == 'n'){
            panelSmall.setXSize(panelSmall.getXSize()-10);
            panelSmall.setYSize(panelSmall.getYSize()-10);
        }
    }
}

void restore_terminal_settings(void) {
	tcsetattr(0, TCSANOW, &oldt);  /* Apply saved settings */
}

void disable_waiting_for_enter(void) {
    struct termios newt;

    /* Make terminal read 1 char at a time */
    tcgetattr(0, &oldt);  /* Save terminal settings */
    newt = oldt;  /* Init new settings */
    newt.c_lflag &= ~(ICANON | ECHO);  /* Change settings */
    tcsetattr(0, TCSANOW, &newt);  /* Apply settings */
    atexit(restore_terminal_settings); /* Make sure settings will be restored when program ends  */
}

int main(int argc, char** argv){

    // Read Text File
    parse.parseTree("object/maze_point_2.txt");
    parse2.parseTree("object/maze_point.txt");
    PTree = parse.getTrees();
    PTree2 = parse2.getTrees();
    /////////////////////////////////////

    
    // Insert Coordinat To Array
    for(int i = 1; i < PTree.size(); i++){
        p.add(Line(PTree[i-1],PTree[i]));
    }
    p.add(Line(PTree[0],PTree[PTree.size()-1]));
    for(int i = 1; i < PTree2.size(); i++){
        p.add(Line(PTree2[i-1],PTree2[i]));
    }
    p.add(Line(PTree2[0],PTree2[PTree2.size()-1]));
    //////////////////////////////////////

    pthread_create(&t_control, NULL, controller, NULL);
    p.scalePolygon(0.75,0.75);

	a.EmptyScreen();
    while(1) {
		disable_waiting_for_enter();
         //ZoomSelector
        p.drawInside(&panelSmall, &panelBig);
        player.player_shape.drawInside(&panelSmall, &panelBig);

        p.draw(&panelMain);
        player.player_shape.draw(&panelMain);
        //a.drawFrame(panelMain);
        a.drawFrame(panelBig);
        a.drawFrame(panelSmall);
        
        //player.draw_player();
        a.Draw();

        panelMain.EmptyFrame();
        panelSmall.EmptyFrame();
        panelBig.EmptyFrame();
    }
    

    pthread_join(t_control, NULL);

    return 0;
}
