#ifndef POINT_H
#define POINT_H
#include "matrix.h"

#define PI 3.14159265

typedef struct
{
	float x, y;
} Point;

void gambarGaris(Point P1, Point P2, Matrix* M, char c);
int isGarisPutus(Point P1, Point P2, Matrix* M, char c);
void setXY(Point* P, int x, int y);
void plotXY(Matrix* M, int x, int y, char c);
void rotatePoint(Point* P, int initx, int inity, int x);

#endif
