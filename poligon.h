#ifndef POLIGON_H
#define POLIGON_H

#include <iostream>
#include "line.h"
#include <stack>
using namespace std;

class Poligon : public Shape
{
    public:
        Poligon() : arr_Line(), thickness(1), fill_color(Color::BLUE), LineColor(Color::WHITE){}

        Poligon(int Linethickness, Color fill_color, Color LineColor): arr_Line(){
            thickness = Linethickness;
            (*this).fill_color = fill_color;
            (*this).LineColor = LineColor;
        }

        Poligon& operator=(const Poligon& pol){
            arr_Line.clear();
            thickness = pol.thickness;
            fill_color = pol.fill_color;
            LineColor = pol.LineColor;
            for (unsigned int i = 0; i < pol.arr_Line.size(); ++i)
            {
                arr_Line.push_back(pol.arr_Line[i]);
            }

            return (*this);
        }

        void erase_fill_color(int x, int y, FramePanel *panel) {
            stack<Point> queue;
            Point point_todo(x, y), current_point;
            queue.push(point_todo);

            while (!queue.empty()) {
                current_point = queue.top();
                // current_point.printPoint();
                // printf("\n");
                queue.pop();
                if ((panel->get(current_point) != Color::BLACK)) {
                    // printf("here\n");
                    panel->set(Color::BLACK, current_point);

                    point_todo = current_point;
                    point_todo.Move(1,0);
                    queue.push(point_todo);

                    point_todo = current_point;
                    point_todo.Move(0,1);
                    queue.push(point_todo);

                    point_todo = current_point;
                    point_todo.Move(-1,0);
                    queue.push(point_todo);

                    point_todo = current_point;
                    point_todo.Move(0,-1);
                    queue.push(point_todo);
                } else {
                    // printf("black\n");
                }
            }
        }

        void draw_fill_color(int x, int y, FramePanel *panel) {
            stack<Point> queue;
            Point point_todo(x, y), current_point;
            queue.push(point_todo);

            while (!queue.empty()) {
                current_point = queue.top();
                // current_point.printPoint();
                // printf("\n");
                queue.pop();
                if ((panel->get(current_point) == Color::BLACK)) {
                    // printf("here\n");
                    panel->set(fill_color, current_point);

                    point_todo = current_point;
                    point_todo.Move(1,0);
                    queue.push(point_todo);

                    point_todo = current_point;
                    point_todo.Move(0,1);
                    queue.push(point_todo);

                    point_todo = current_point;
                    point_todo.Move(-1,0);
                    queue.push(point_todo);

                    point_todo = current_point;
                    point_todo.Move(0,-1);
                    queue.push(point_todo);
                } else {
                    // printf("black\n");
                }
            }
        }

        void add(Line a){
            a.setColor(LineColor);
            a.setThickness(thickness);
            arr_Line.push_back(a);
        }
        
        void del() {
			arr_Line.pop_back();
		}

        Line* getP(unsigned int i){
            if(i < arr_Line.size()){
                return &arr_Line[i];
            }

            return NULL;
        }

        Line* popLast(){
            if(arr_Line.empty()){
                return NULL;
            }
            Line* temp = new Line(arr_Line[arr_Line.size()-1].getP1(), arr_Line[arr_Line.size()-1].getP2(), LineColor,thickness);
            arr_Line.pop_back();
            return temp;
        }

        void erase(FramePanel *a) {
            for(unsigned int i = 0;i<arr_Line.size();i++){
                Line ax;
                ax = arr_Line[i];
                ax.setColor(Color::BLACK);
                ax.setThickness(thickness);
                ax.draw(a);
            }
        }

        void draw(FramePanel* a){
            for(unsigned int i = 0;i<arr_Line.size();i++){
                Line ax;
                ax = arr_Line[i];
                ax.setColor(LineColor);
                ax.setThickness(thickness);
                ax.draw(a);
            }
        }

        Color getLineColor(){
            return LineColor;
        }

        Color getfill_color(){
            return fill_color;
        }

        int getThickness(){
            return thickness;
        }

        void setLineColor(Color c){
            LineColor = c;
        }

        void setfill_color(Color c){
            fill_color = c;
        }

        void setThickness(int t){
            thickness = t;
        }

        void scalePolygon(float sx, float sy, const  Point& center = Point()){
            for(unsigned int i = 0; i < arr_Line.size(); i++){
                arr_Line[i].scaleLine(sx, sy, center);
            }
        }

        void makeLineFromArrPoint(std::vector<Point>& P){
            for(unsigned int i = 0; i<P.size(); i++){
                Line l;
                if(i == P.size()-1){
                    l = Line(P[i], P[0]);
                }else{
                    l = Line(P[i], P[i+1]);
                }
                (*this).add(l);
            }
        }

         void drawTree(Point p) {
            Line a,b,c,d,e;

            a = Line(p, Point(p.getX(),p.getY()-5));
            b = Line(Point(p.getX()-4,p.getY()-5),Point(p.getX()+4,p.getY()-5));
            c = Line(Point(p.getX()-4,p.getY()-5),Point(p.getX()-4,p.getY()-9));
            d = Line(Point(p.getX()-4,p.getY()-9),Point(p.getX()+4,p.getY()-9));
            e = Line(Point(p.getX()+4,p.getY()-5),Point(p.getX()+4,p.getY()-9));
            arr_Line.push_back(a);
            arr_Line.push_back(b);
            arr_Line.push_back(c);
            arr_Line.push_back(d);
            arr_Line.push_back(e);
            (*this).setLineColor(Color::GREEN);
            (*this).setThickness(1);

            setAllLineColor();
        }

        void setAllLineColor(){
            for(unsigned int i = 0; i<arr_Line.size(); i++){
                arr_Line[i].setColor(LineColor);
            }
        }

        void movePolygon(int x, int y){
            for(int i = 0; i<  arr_Line.size(); i++){
                arr_Line[i].moveLine(x, y);
            }
        }

        void printPolygon(){
            for (unsigned int i = 0; i < arr_Line.size(); ++i)
            {
                arr_Line[i].printLine();
            }
        }

        void drawInside(FramePanel* panelNormal, FramePanel* panelZoom){
            for(unsigned int i = 0; i < arr_Line.size(); i++){
                Line line;
                float sx = ((float)((*panelZoom).getXSize())/(float)((*panelNormal).getXSize()));
                float sy = ((float)((*panelZoom).getYSize())/(float)((*panelNormal).getYSize()));
                bool a = arr_Line[i].checkInsideFrame(*panelNormal, &line);
                if(a){
                    //cout << "sebel";line.printLine();
                    line.moveLine(((*panelNormal).getXMin()*(-1)), (-1)*((*panelNormal).getYMin()));
                    line.draw(panelNormal);
                    //cout << "sesud"; line.printLine();
                    line.scaleLine(sx, sy);
                    line.draw(panelZoom);
                    //cout << "sesud2"; line.printLine();
                }
            }
        }

        void rotate(int degree, Point &center_point) {
            for (unsigned int i = 0; i < arr_Line.size(); i++) {
                // printf("before "); arr_Line[i].printLine();
                arr_Line[i].rotateLine(degree, center_point);

                // printf("after ");arr_Line[i].printLine();
            }
        }

    private:
        std::vector<Line> arr_Line;
        int thickness;
        Color fill_color;
        Color LineColor;
};

#endif
