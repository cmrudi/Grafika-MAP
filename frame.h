#ifndef FRAME_H
#define FRAME_H

#include "color.h"
#include "point.h"

class Frame
{
public:
	virtual void set(Color c, Point& p) = 0;
	virtual void set(char r, char g, char b, Point& p) = 0;
	virtual void set(char r, char g, char b, int x, int y) = 0;
	virtual Color get(Point& p) = 0;
	virtual Color get(int x, int y) = 0;
    virtual int getXSize() = 0;
	virtual int getYSize() = 0;

};

#endif // FRAME_H
