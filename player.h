#include "framebuffer.h"
#include "poligon.h"
#include "framepanel.h"
#include "color.h"
#include "point.h"
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
                new_direction = 0;
                move_x = 0;
                move_y = -DELTA_PLAYER_MOVE;
            } else if (c == 'd'){
                new_direction = 1;
                move_x = DELTA_PLAYER_MOVE;
                move_y = 0;
            } else if (c == 's'){
                new_direction = 2;
                move_x = 0;
                move_y = DELTA_PLAYER_MOVE;
            } else if (c == 'a'){                
                new_direction = 3;

                move_x = -DELTA_PLAYER_MOVE;
                move_y = 0;
            }
            else if (c == 'c') {
                player_cheat();
            }
            printf("\033[%d;%dH", YP, XP);
            update_player(move_x, move_y, new_direction);
        }
    }

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
    }

    void draw_player() {
        player_shape.draw(panel);
        fb->Draw();
    }

    void erase_player() {
        player_shape.erase(panel);
    }

    void player_cheat() {
        erase_player();
        int x = 600;
        int y = 200;
        player_center_point.setX(x);
        player_center_point.setY(y);
        
        Point P1(x, y-10);
        Point P2(x+3, y+5);
        Point P3(x-3, y+5);

        player_points.clear();
        player_points.push_back(P1);
        player_points.push_back(P2);
        player_points.push_back(P3);
        player_shape.clearPolygon();
        Line l;
        for (unsigned int i = 0; i < player_points.size(); i++) {
            l.setP1(player_points[i]);
            l.setP2(player_points[(i+1)%player_points.size()]);
            player_shape.add(l);
        }
        draw_player();

    }

    void rotate_player(int new_dir) {
        int inc = 1;
        if (this->player_direction > new_dir)
            inc = -1;

        while (this->player_direction != new_dir) {
            for (int i = 0; i < 3; i++) {
                erase_player();
                player_shape.rotate(30 * inc, player_center_point);
                draw_player();
            }
            this->player_direction += inc;
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
