#ifndef FRAMEPANEL_H
#define FRAMEPANEL_H

#include "frame.h"
#include "color.h"
#include "point.h"

class FramePanel : public Frame
{
public:
    FramePanel(){
        sizex = sizey = 0;
        xmin = ymin = 0;
        EmptyFrame();
    }

    FramePanel(int x, int y){
    	xmin = ymin = 0;
        setXSize(x);
        setYSize(y);
        EmptyFrame();
    }

    FramePanel(int x, int y, int xmin, int ymin){
    	(*this).xmin = xmin;
    	(*this).ymin = ymin;
    	setXSize(x);
    	setYSize(y);
    	EmptyFrame();
    }

    FramePanel(FramePanel& _f){
        sizex = _f.sizex;
        sizey = _f.sizey;
        xmin = ymin = 0;
        for(int i = 0; i<_f.sizex;i++){
            for(int j = 0; j<_f.sizey;j++){
                M[i][j] = _f.M[i][j];
            }
        }
    }


    FramePanel& operator= (FramePanel& _f){
        M.clear();
        sizex = _f.sizex;
        sizey = _f.sizey;
        for(int i = 0; i<_f.sizex;i++){
            for(int j = 0; j<_f.sizey;j++){
                M[i][j] = _f.M[i][j];
            }
        }
        return *this;
    }

    void set(Color c, Point& p){
        M[p.getX()][p.getY()] = c;
    }

     void set(Color c, int x, int y){
        M[x][y] = c;
    }

    void set(char r, char g, char b, Point& p){
        M[p.getX()][p.getY()] = Color(r,g,b);
    }

    void set(char r, char g, char b, int x, int y){
        M[x][y] = Color(r,g,b);
    }

    Color get(Point& p){
        return M[p.getX()][p.getY()];
    }

    Color get(int x, int y){
        return M[x][y];
    }

    int getXSize(){
        return sizex;
    }

    int getYSize(){
        return sizey;
    }

    void setXSize(int x){
        sizex = x;
        M.resize(sizex);
    }

    void setYSize(int y){
        sizey = y;
        for(unsigned int i = 0; i<M.size(); i++){
            M[i].resize(sizey);
        }
    }

    int getXMin(){
    	return xmin;
    }

    int getYMin(){
    	return ymin;
    }

    void setXMin(int x){
    	xmin = x;
    }

    void setYMin(int y){
    	ymin = y;
    }

	void EmptyFrame(){
		for(int i = 0; i < sizex; i++){
			for(int j = 0; j<sizey; j++){
				M[i][j] = Color::BLACK;
				if(i == 0 || i == sizex-1 || j == 0 || j == sizey-1){
					M[i][j] = Color::WHITE;
				}
			}
		}
	}

	std::vector<std::vector<Color> > M;

private:

    int sizex, sizey;
    int xmin, ymin;
};

#endif // FRAMEPANEL_H
