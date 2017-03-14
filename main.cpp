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
#define DELTA_GERAK 5

#define WIDTH 521
#define HEIGHT 241

static struct termios oldt;
std::vector<Point> PTree;
std::vector<Point> PTree2;
std::vector<Point> Enemy1;
FramePanel panelMain(700, 700, 0, 0);
FramePanel panelSmall(100, 100, 0, 300);
FramePanel panelBig(500, 500, 750, 0);
FramePanel panelWin(521,241,340,200);
Framebuffer a;
Parser parse;
Parser parse2;
Parser enemy1;
Poligon p, enemyPoligon;
pthread_t t_control;
int x1 = 200;
Player player(30,350,0,255,0,&panelMain,&a);
int redPixelMatrix[WIDTH][HEIGHT][2];
int greenPixelMatrix[WIDTH][HEIGHT][2];
int bluePixelMatrix[WIDTH][HEIGHT][2];
int isWin = 0;

void initializePriorMatrix () {
    for (int i = 0; i < WIDTH; i++) {
        for (int j = 0; j < HEIGHT; j++) {
            for (int k = 0; i < 2; k++) {
                redPixelMatrix[i][j][k] = 0;
                greenPixelMatrix[i][j][k] = 0;
                bluePixelMatrix[i][j][k] = 0;
            }
        }
    }
}

char getch() {
    char buf = 0;
    struct termios old = {0};
    if (tcgetattr(0, &old) < 0)
            perror("tcsetattr()");
    old.c_lflag &= ~ICANON;
    old.c_lflag &= ~ECHO;
    old.c_cc[VMIN] = 1;
    old.c_cc[VTIME] = 0;
    if (tcsetattr(0, TCSANOW, &old) < 0)
            perror("tcsetattr ICANON");
    if (read(0, &buf, 1) < 0)
            perror ("read()");
    old.c_lflag |= ICANON;
    old.c_lflag |= ECHO;
    if (tcsetattr(0, TCSADRAIN, &old) < 0)
            perror ("tcsetattr ~ICANON");
    printf("\033[%d;%dH", 100, 0);
    return (buf);
}

void drawWhitePointPrior(int x1, int y1, int prior) {
    if (x1 < 0 || x1 >= WIDTH || y1 < 0 || y1 >= HEIGHT) return;
    redPixelMatrix[x1][y1][prior] = 255;
    greenPixelMatrix[x1][y1][prior] = 255;
    bluePixelMatrix[x1][y1][prior] = 255;
}

bool drawWhiteLine(int x1, int y1, int x2, int y2, int prior) {
    bool ret = false;

    int deltaX = x2 - x1;
    int deltaY = y2 - y1;
    int ix = deltaX > 0 ? 1 : -1;
    int iy = deltaY > 0 ? 1 : -1;
    deltaX = abs(deltaX);
    deltaY = abs(deltaY);

    int x = x1;
    int y = y1;

    drawWhitePointPrior(x,y, prior);

    if (deltaX >= deltaY) {
        int error = 2 * deltaY - deltaX;

        while (x != x2) {
            if ((error >= 0) && (error || (ix > 0)))
            {
                error -= deltaX;
                y += iy;
            }

            error += deltaY;
            x += ix;


            if (redPixelMatrix[x][y][prior] == 255 && greenPixelMatrix[x][y][prior] == 255 && bluePixelMatrix[x][y][prior] == 255) {
                ret = true;
            }
            drawWhitePointPrior(x, y, prior);
        }
    } else {
        int error = 2 * deltaX - deltaY;

        while (y != y2)
        {
            if ((error >= 0) && (error || (iy > 0)))
            {
                error -= deltaY;
                x += ix;
            }

            error += deltaX;
            y += iy;


            if (redPixelMatrix[x][y][prior] == 255 && greenPixelMatrix[x][y][prior] == 255 && bluePixelMatrix[x][y][prior] == 255) {
                ret = true;
            }
            drawWhitePointPrior(x, y, prior);
        }
    }
    return ret;
}

void floodFill(int x,int y,int redBatas,int greenBatas,int blueBatas,int redColor,int greenColor,int blueColor, int prior){
    if((x>=0 && x<WIDTH) && (y>=0 && y<HEIGHT)){
        if(!((redPixelMatrix[x][y][prior] ==redBatas && greenPixelMatrix[x][y][prior] ==greenBatas && bluePixelMatrix[x][y][prior] ==blueBatas) ||
            (redPixelMatrix[x][y][prior]==redColor && greenPixelMatrix[x][y][prior]==greenColor && bluePixelMatrix[x][y][prior]==blueColor))){
            redPixelMatrix[x][y][prior] = redColor;
            greenPixelMatrix[x][y][prior] = greenColor;
            bluePixelMatrix[x][y][prior] = blueColor;
            floodFill(x,y+1,redBatas,greenBatas,blueBatas,redColor,greenColor,blueColor,prior);
            floodFill(x+1,y,redBatas,greenBatas,blueBatas,redColor,greenColor,blueColor,prior);
            floodFill(x,y-1,redBatas,greenBatas,blueBatas,redColor,greenColor,blueColor,prior);
            floodFill(x-1,y,redBatas,greenBatas,blueBatas,redColor,greenColor,blueColor,prior);
        }
    }
}

void drawWin() {
    //priority 0
    drawWhiteLine(1,1,520,1,0);
    drawWhiteLine(1,1,1,240,0);
    drawWhiteLine(520,1,520,240,0);
    drawWhiteLine(1,240,520,240,0);

    //priority 1

    //W
    drawWhiteLine(40,40,80,40,1);
    drawWhiteLine(80,40,100,120,1);
    drawWhiteLine(100,120,120,80,1);
    drawWhiteLine(120,80,140,120,1);
    drawWhiteLine(140,120,160,40,1);
    drawWhiteLine(160,40,200,40,1);
    drawWhiteLine(200,40,140,200,1);
    drawWhiteLine(140,200,120,160,1);
    drawWhiteLine(120,160,80,200,1);
    drawWhiteLine(80,200,40,40,1);
    //floodFill(60,60,255,255,255,0,255,0,1);

    //I
    drawWhiteLine(240,40,280,40,1);
    drawWhiteLine(280,40,280,200,1);
    drawWhiteLine(280,200,240,200,1);
    drawWhiteLine(240,200,240,40,1);
    //floodFill(260,120,255,255,255,0,255,0,1);

    //N
    drawWhiteLine(320,40,360,40,1);
    drawWhiteLine(360,40,440,160,1);
    drawWhiteLine(440,160,440,40,1);
    drawWhiteLine(440,40,480,40,1);
    drawWhiteLine(480,40,480,200,1);
    drawWhiteLine(480,200,440,200,1);
    drawWhiteLine(440,200,360,120,1);
    drawWhiteLine(360,120,360,200,1);
    drawWhiteLine(360,200,320,200,1);
    drawWhiteLine(320,200,320,40,1);
    //floodFill(340,60,255,255,255,0,255,0,1);
}

void drawPanelWin() {
    for (int i = 0; i < WIDTH; i++) {
        for (int j = 0; j < HEIGHT; j++) {
            if ((redPixelMatrix[i][j][1] != 0) || (greenPixelMatrix[i][j][1] != 0) || (bluePixelMatrix[i][j][1] != 0))
                panelWin.set(redPixelMatrix[i][j][1], greenPixelMatrix[i][j][1], bluePixelMatrix[i][j][1],i,j);
            else
                panelWin.set(redPixelMatrix[i][j][0], greenPixelMatrix[i][j][0], bluePixelMatrix[i][j][0],i,j);
        }
    }
}

void *controller(void *args){

    char c;
    while(1){
        c = getch();

        if(c == 'a'){
            if(panelSmall.getXMin() > 10){
				if (player.is_move_valid(-DELTA_GERAK, 0))
					panelSmall.setXMin(panelSmall.getXMin() - DELTA_GERAK);
                player.update_player(-DELTA_GERAK, 0, 3);
            }
            // printf("x: %d\n", panelSmall.getXMin());
        }else if(c == 's'){
            if(panelSmall.getYMin() < panelMain.getXSize() - panelSmall.getYMin()){
				if (player.is_move_valid(0, DELTA_GERAK))
					panelSmall.setYMin(panelSmall.getYMin() + DELTA_GERAK);
                player.update_player(0, DELTA_GERAK, 2);
            }
            // printf("y: %d\n", panelSmall.getYMin());
        }else if (c == 'd'){
            if(panelSmall.getXMin() < panelMain.getXSize() - panelSmall.getXMin()-10){
				if (player.is_move_valid(DELTA_GERAK, 0))
					panelSmall.setXMin(panelSmall.getXMin() + DELTA_GERAK);
                player.update_player(DELTA_GERAK, 0, 1);
            }
            // printf("x: %d\n", panelSmall.getXMin());
        }else if(c == 'w'){
            	if (player.is_move_valid(0, -DELTA_GERAK))
					panelSmall.setYMin(panelSmall.getYMin() - DELTA_GERAK);
                player.update_player(0, -DELTA_GERAK, 0);
            // printf("y: %d\n", panelSmall.getYMin());
        }else if(c == 'b'){
            panelSmall.setXSize(panelSmall.getXSize()+10);
            panelSmall.setYSize(panelSmall.getYSize()+10);
        }else if(c == 'n'){
            panelSmall.setXSize(panelSmall.getXSize()-10);
            panelSmall.setYSize(panelSmall.getYSize()-10);
        }
        else if (c == 'c') {
            panelSmall.setYMin(150);
            panelSmall.setXMin(550);
            player.player_cheat();
        }
        else if (c == 'p') {
			/*
			if (isWin == 1) {
				isWin = 0;
			}
			else {
				isWin = 1;
			}
			* */
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
    a.Draw();
    // usleep(100000000);
    drawWin();
    drawPanelWin();

	// draw enemy
    enemy1.parseEnemy("object/enemy1.txt", x1, 35);
    Enemy1 = enemy1.getTrees();
    for(int i = 1; i < Enemy1.size(); i++){
        enemyPoligon.add(Line(Enemy1[i-1],Enemy1[i]));
    }
    enemyPoligon.add(Line(Enemy1[0],Enemy1[Enemy1.size()-1]));
	/////////////////////////////////
    pthread_create(&t_control, NULL, controller, NULL);

	int x = 0;
    while(1) {
		//disable_waiting_for_enter();

		// Read Enemy File
	
		if (x1 > 150) {
			x1--;
		}
		else if (x1 < 200) {
			x1++;
		}
         //ZoomSelector
        enemyPoligon.drawInside(&panelSmall, &panelBig);
        if (x) {
			enemyPoligon.erase(&panelMain);
			x = 0;
			enemyPoligon.movePolygon(-1, 0);
		} else {
			x = 1;
		}
        p.drawInside(&panelSmall, &panelBig);
        player.player_shape.drawInside(&panelSmall, &panelBig);

		enemyPoligon.draw(&panelMain);
        p.draw(&panelMain);
        // p.draw_fill_color(0,0, &panelMain);
        player.player_shape.draw(&panelMain);
        a.drawFrame(panelMain);
        a.drawFrame(panelBig);
        a.drawFrame(panelSmall);
        if (player.player_center_point.getX() == 645 && player.player_center_point.getY() == 110) {
            isWin = 1;
        }

        if (isWin == 1) {
            a.drawFrame(panelWin);
        }

        a.Draw();

        // panelMain.EmptyFrame();
        panelSmall.EmptyFrame();
        panelBig.EmptyFrame();
    }


    pthread_join(t_control, NULL);

    return 0;
}
