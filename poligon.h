#ifndef POLIGON_H
#define POLIGON_H

#include <iostream>
#include "line.h"

using namespace std;

class Poligon : public Shape
{
    public:
        Poligon() : arr_Line(), thickness(1), floodfill(Color::BLUE), LineColor(Color::BLACK){}

        Poligon(int Linethickness, Color floodfill, Color LineColor): arr_Line(){
            thickness = Linethickness;
            (*this).floodfill = floodfill;
            (*this).LineColor = LineColor;
        }

        void add(Line a){
            a.setColor(LineColor);
            a.setThickness(thickness);
            arr_Line.push_back(a);
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

        void draw(FramePanel& a){
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

        Color getFloodfill(){
            return floodfill;
        }

        int getThickness(){
            return thickness;
        }

        void setLineColor(Color c){
            LineColor = c;
        }

        void setFloodfill(Color c){
            floodfill = c;
        }

        void setThickness(int t){
            thickness = t;
        }

    private:
        std::vector<Line> arr_Line;
        int thickness;
        Color floodfill;
        Color LineColor;
};

#endif
