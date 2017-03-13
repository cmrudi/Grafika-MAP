#include "framebuffer.h"
#include "poligon.h"
#include <termios.h>
#define DELTA_PLAYER_MOVE 3
class Player {
public:
    Player(int x, int y, char r, char g, char b, FramePanel *p, Framebuffer *fbuff) {
        player_center_point.setX(x);
        player_center_point.setY(y);
        this->panel = p;
        this->fb = fbuff;
        Color c(r,g,b);

        Point P1(x, y-10);
        Point P2(x+3, y+5);
        Point P3(x-3, y+5);

        player_points.push_back(P1);
        player_points.push_back(P2);
        player_points.push_back(P3);

        Line l;
        for (unsigned int i = 0; i < player_points.size(); i++) {
            l.setP1(player_points[i]);
            l.setP2(player_points[(i+1)%player_points.size()]);
            player_shape.add(l);
        }
        player_shape.setLineColor(c);
        player_shape.setfill_color(c);
        player_direction = 0;
    }

    void run_player() {
        draw_player();
        int XP = 0;
        int YP = 0;
        int move_x = 0, move_y = 0;
        int new_direction;
        while(1){
            char c;
            c = getchar();
            if (c == 'w'){
                // printf("WWWWWWWWWWWWWW\n");
                new_direction = 0;
                move_x = 0;
                move_y = -DELTA_PLAYER_MOVE;
            } else if (c == 'd'){
                // printf("DDDDDDDDDDDDDD\n");
                new_direction = 1;
                move_x = DELTA_PLAYER_MOVE;
                move_y = 0;
            } else if (c == 's'){
                // printf("SSSSSSSSSSSSS\n");
                new_direction = 2;
                move_x = 0;
                move_y = DELTA_PLAYER_MOVE;
            } else if (c == 'a'){
                // printf("AAAAAAAAAAAA\n");
                new_direction = 3;

                move_x = -DELTA_PLAYER_MOVE;
                move_y = 0;
            }
            printf("\033[%d;%dH", YP, XP);
            update_player(move_x, move_y, new_direction);
        }
    }

    /*char getch() {
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
        return (buf);
    }*/

    void update_player(int move_x, int move_y, int new_dir) {
        rotate_player(new_dir);

        if (is_move_valid(move_x, move_y))
            move_player(move_x, move_y);
    }

    void move_player(int move_x, int move_y) {

        erase_player();
        player_shape.movePolygon(move_x, move_y);
        for (unsigned int i = 0; i < player_points.size(); i++) {
            player_points[i].Move(move_x, move_y);
        }
        player_center_point.Move(move_x, move_y);
        draw_player();
        usleep(5);
        //usleep(500);
    }

    void draw_player() {
        player_shape.draw(panel);
        //player_shape.draw_fill_color(player_center_point.getX(), player_center_point.getY(), panel);
        fb->drawFrame(*panel);
        fb->Draw();
    }

    void erase_player() {
        player_shape.erase(panel);
        player_shape.erase_fill_color(player_center_point.getX(), player_center_point.getY(), panel);
    }

    void rotate_player(int new_dir) {
        int inc = 1;
        if (player_direction > new_dir)
            inc = -1;

        while (player_direction != new_dir) {
            for (int i = 0; i < 9; i++) {
                erase_player();
                player_shape.rotate(10 * inc, player_center_point);
                draw_player();
                usleep(5);
				//usleep(500);
            }
            player_direction += inc;
        }
    }

    bool is_move_valid(int delta_x, int delta_y) {
        int newx = player_shape.getP(0)->getP1().getX() + delta_x;
        int newy = player_shape.getP(0)->getP1().getY() + delta_y;

        return (panel->get(newx, newy) == Color::BLACK);
    }

    int player_direction; // 0 -> up, 1->right, 2->down, 3->left
    FramePanel *panel;
    Framebuffer *fb;
    Poligon player_shape;
    Point player_center_point;
    vector<Point> player_points;
};
