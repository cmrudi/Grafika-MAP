// #include <ncurses.h>
#include <iostream>
#include <stdio.h>
#include "poligon.h"
#include "parser.h"
#include "player.h"
#include <pthread.h>
#include <termios.h>
#include <thread>
#include <stdlib.h>
#define DELTA_GERAK 2


static struct termios oldt;
std::vector<Point> PTree;
std::vector<Point> PTree2;
FramePanel panelMain(700, 700, 0, 0);
FramePanel panelSmall(100, 100, 0, 300);
FramePanel panelBig(500, 500, 750, 0);
Framebuffer a;
Parser parse;
Parser parse2;
Poligon p;
pthread_t t_control;
Player player(30,350,0,255,0,&panelMain,&a);

void *controller(void *args){
    while(1){
        char c;
        c = getchar();

        if(c == 'j'){
            if(panelSmall.getXMin() > 10){
				if (player.is_move_valid(-DELTA_GERAK, 0))
					panelSmall.setXMin(panelSmall.getXMin() - DELTA_GERAK);
                player.update_player(-DELTA_GERAK, 0, 3);
            }
        }else if(c == 'k'){
            if(panelSmall.getYMin() > 10){
				if (player.is_move_valid(0, DELTA_GERAK))
					panelSmall.setYMin(panelSmall.getYMin() + DELTA_GERAK);
                player.update_player(0, DELTA_GERAK, 2);
            }
        }else if (c == 'l'){
            if(panelSmall.getXMin() < panelMain.getXSize() - panelSmall.getXMin()-10){
				if (player.is_move_valid(DELTA_GERAK, 0))
					panelSmall.setXMin(panelSmall.getXMin() + DELTA_GERAK);
                player.update_player(DELTA_GERAK, 0, 1);
            }
        }else if(c == 'i'){
            if(panelSmall.getYMin() < panelMain.getXSize() - panelSmall.getYMin()){
				if (player.is_move_valid(0, -DELTA_GERAK))
					panelSmall.setYMin(panelSmall.getYMin() - DELTA_GERAK);
                player.update_player(0, -DELTA_GERAK, 0);
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
    // a.EmptyScreen();
    p.scalePolygon(0.75,0.75);
    p.setfill_color(Color::BLUE);

    p.draw(&panelMain);
    p.draw_fill_color(28,28, &panelMain);
    p.draw_fill_color(617,600, &panelMain);

    p.draw(&panelMain);
    a.drawFrame(panelMain);
    // a.set(Color::GREEN, 617,600);
    a.Draw();
    // usleep(100000000);


    pthread_create(&t_control, NULL, controller, NULL);

    while(1) {
		disable_waiting_for_enter();
         //ZoomSelector
        p.drawInside(&panelSmall, &panelBig);
        player.player_shape.drawInside(&panelSmall, &panelBig);

        p.draw(&panelMain);
        //p.draw_fill_color(0,0, &panelMain);
        player.player_shape.draw(&panelMain);
        a.drawFrame(panelMain);
        a.drawFrame(panelBig);
        a.drawFrame(panelSmall);

        //player.draw_player();
        a.Draw();

        // panelMain.EmptyFrame();
        panelSmall.EmptyFrame();
        panelBig.EmptyFrame();
    }


    pthread_join(t_control, NULL);

    return 0;
}
