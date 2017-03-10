#include <iostream>
#include "poligon.h"
#include "parser.h"
#include "player.h"
#include <thread>
#include <termios.h>

using namespace std;

char orientation;
Framebuffer fb;
FramePanel panelMain(550, 500, 10, 10);

void draw_maze(int x, int y) {
    panelMain.EmptyFrame();
    Poligon maze;
    maze.setfill_color(Color::BLUE);

    Line l(x,y,x,y+100,Color::WHITE, 1);
    maze.add(l);

    l.setP1(x + 10,y+ 100);
    // l.setP2(220,300);
    maze.add(l);

    // l.setP1(220,300);
    l.setP2(x+ 10,y+10);
    maze.add(l);

    l.setP1(x,y);
    // l.setP2(210,210);
    maze.add(l);
    maze.draw(&panelMain);
    maze.draw_fill_color(x+5, y+20, &panelMain);
    fb.drawFrame(panelMain);
    fb.Draw();
}


int main() {
    draw_maze(100,10);
    Player player(50,50,0,255,0,&panelMain,&fb);
    player.run_player();
	// thread t_player(player.run_player);

    // draw_player(200,200,0);
    // fb.Draw();

    // t_listener.join();
	return 0;
}
