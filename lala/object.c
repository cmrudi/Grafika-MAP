#include "object.h"
#include "lingkaran.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

void setXYObject(Object* O, int x, int y) {
	O->pointInit.x = x;
	O->pointInit.y = y;
}

void moveVertical(Object* O, int y) {
	O->pointInit.y = O->pointInit.y + y;
}

void moveHorizontal(Object* O, int x) {
	O->pointInit.x = O->pointInit.x + x;
}

void rotateClockwise(Object* O, int x) {
	float angle = x*PI/180;
	float s = sin(angle);
	float c = cos(angle);

	float px;
	float py;
	float pLx;
	float pLy;
	for (int i=0 ;i < O->size ;i++) {
		px = O->P[i].x;
		py = O->P[i].y;
		O->P[i].x = (px * c) - (py * s);
		O->P[i].y = (px * s) + (py * c);	
	}
}

void rotateWheelClockwise(Object* O, int x) {
	float angle = x*PI/180;
	float s = sin(angle);
	float c = cos(angle);

	float px;
	float py;
	float pLx;
	float pLy;
	for (int i=0 ;i < O->size ;i++) {
		px = O->P[i].x;
		py = O->P[i].y;
		pLx = O->L[i].x;
		pLy = O->L[i].y;
		O->P[i].x = (px * c) - (py * s);
		O->P[i].y = (px * s) + (py * c);	
		O->L[i].x = (pLx * c) - (pLy * s);
		O->L[i].y = (pLx * c) + (pLy * s);
	}
}

void rotateCounterClockwise(Object* O, int x) {
	float angle = x*PI/180;
	float s = -sin(angle);
	float c = cos(angle);

	float px;
	float py;
	for (int i=0 ;i<O->size ;i++) {
		px = O->P[i].x;
		py = O->P[i].y;
		O->P[i].x = (int) round((px * c) - (py * s));
		O->P[i].y = (int) round((px * s) + (py * c));		
	}
}

int isOut(Object* O,float rangex, float rangey) {
	if ((O->pointInit.x<=rangex)||(O->pointInit.y<=rangey)){
		return 1;
	}else{
		return 0;
	}
}

int isWheelOut(Object* O) {
	if (O->pointInit.y>=650) return 1;
	return 0;
}

void gambarObject(Object O, Matrix* M, char c) {
	Point start, finish;
	for(int i = 0;i < O.size-1 ;i++) {
		setXY(&start, (int)O.P[i].x + O.pointInit.x, (int)O.P[i].y + O.pointInit.y);
		setXY(&finish, (int)O.P[i+1].x + O.pointInit.x, (int)O.P[i+1].y + O.pointInit.y);
		gambarGaris(start, finish, M, c);
	}

	setXY(&start, (int)O.P[O.size - 1].x + O.pointInit.x, (int)O.P[O.size - 1].y + O.pointInit.y);
	setXY(&finish, (int)O.P[0].x + O.pointInit.x, (int)O.P[0].y + O.pointInit.y);
	gambarGaris(start, finish, M, c);

	for(int i = 0;i < O.nlingkaran ;i++) {
        Lingkaran L;
        L.x = O.L[i].x + O.pointInit.x;
        L.y = O.L[i].y + O.pointInit.y;
        L.r = O.L[i].r;
		gambarLingkaran(&L, M, c, O.lingkaranPenuh);
	}
}

int isObjectCollide(Object O, Matrix* M, char c) {
    int ret = 0;
	Point start, finish;
	for(int i = 0;i < O.size-1 && ret == 0;i++) {
		setXY(&start, O.P[i].x + O.pointInit.x, O.P[i].y + O.pointInit.y);
		setXY(&finish, O.P[i+1].x + O.pointInit.x, O.P[i+1].y + O.pointInit.y);
		ret = isGarisPutus(start, finish, M, c);
	}
    if (ret == 0) {
        setXY(&start, O.P[O.size - 1].x + O.pointInit.x, O.P[O.size - 1].y + O.pointInit.y);
        setXY(&finish, O.P[0].x + O.pointInit.x, O.P[0].y + O.pointInit.y);
        ret = isGarisPutus(start, finish, M, c);
    }
    if (ret == 0) {
        Lingkaran L;
        for(int i = 0;i < O.nlingkaran && ret == 0;i++) {
            L.x = O.L[i].x + O.pointInit.x;
            L.y = O.L[i].y + O.pointInit.y;
            L.r = O.L[i].r;
            ret = isLingkaranPutus(&L, M, c);
        }
    }
    return ret;
}

Object makePeluru(int xinit, int yinit) {
	int x[6] = {2, 6, 6, -6, -6, -2};
	int y[6] = {0, 8, 24, 24, 8, 0};
	Object O;
	for(int i = 0;i < 6;i++) {
		O.P[i].x = x[i];
		O.P[i].y = y[i];
	}

	O.pointInit.x = xinit;
	O.pointInit.y = yinit;
	O.size = 6;
	O.nlingkaran = 0;
	return O;
}

Object makePesawat(int xinit, int yinit) {
	int x[22] = {0, 16, 81, 125, 134, 110, 112, 154, 167, 176, 169, 169, 176, 167, 154, 112, 110, 134, 125,  81,  16, 0};
	int y[22] = {3, 11, 11, 57 , 57 , 21 , 11 , 9  , 28 , 28 , 11 , -11, -28, -28, -9 , -11, -21, -57, -57, -11, -11, -3};
	Object O;
	for(int i = 0;i < 22;i++) {
		O.P[i].x = x[i];
		O.P[i].y = y[i];
	}

	O.pointInit.x = xinit;
	O.pointInit.y = yinit;
	O.size = 22;
	O.nlingkaran = 0;
	return O;
}

Object makeLedakanPesawat1(int xinit, int yinit) {
	int x[6] = {-40, -24, 35,  41,  -24, -40};
	int y[6] = {0, 11, 11, -11, -11, -3};
	Object O;
	for(int i = 0;i < 6;i++) {
		O.P[i].x = x[i];
		O.P[i].y = y[i];
	}

	O.pointInit.x = xinit;
	O.pointInit.y = yinit;
	O.size = 6;
	O.nlingkaran = 0;
	return O;
}

Object makeLedakanPesawat2(int xinit, int yinit) {
	int x[6] = {-27, 17 , 27 , 2 , 4 , -22};
	int y[6] = {-10, 36 , 36 , 0 , -10  , -36};
	Object O;
	for(int i = 0;i < 6;i++) {
		O.P[i].x = x[i];
		O.P[i].y = y[i];
	}

	O.pointInit.x = xinit;
	O.pointInit.y = yinit;
	O.size = 6;
	O.nlingkaran = 0;
	return O;
}

Object makeLedakanPesawat3(int xinit, int yinit) {
	int x[12] = {-25, 20 , 39 , 48 ,  39, 48 , 39 , 26 , -10 , 12  , -3 ,-48};
	int y[12] = {12 , 12 , 36 , 36 ,  3 , -30, -30, -12, -12 , -36, -36, 2};
	Object O;
	for(int i = 0;i < 13;i++) {
		O.P[i].x = x[i];
		O.P[i].y = y[i];
	}

	O.pointInit.x = xinit;
	O.pointInit.y = yinit;
	O.size = 12;
	O.nlingkaran = 0;
	return O;
}

Object makeLedakan(int xinit, int yinit) {
	int x[20] = {0, 20, 46, 40, 84, 54, 86, 51, 72, 29, 28, 4, -34, -19, -60, -22, -67, -21, -47, -4};
	int y[20] = {0, 54, -2, 61, 39, 86, 96, 107, 145, 116, 148, 112, 117, 103, 107, 79, 64, 56, 8, 49};
	Object O;
	for(int i = 0;i < 20;i++) {
		O.P[i].x = x[i];
		O.P[i].y = y[i];
	}

	O.pointInit.x = xinit;
	O.pointInit.y = yinit;
	O.size = 20;
	O.nlingkaran = 0;
	return O;
}

Object makeBaling(int xinit, int yinit) {
	int x[12] = {-2, -7,  7,  2, 42, 42, 2,  7, -7,-2,-42,-42};
	int y[12] = {-2,-42,-42, -2, -7,  7, 2, 42, 42, 2,  7, -7};
	Object O;
	for(int i = 0;i < 12;i++) {
		O.P[i].x = x[i];
		O.P[i].y = y[i];
	}
	O.pointInit.x = xinit;
	O.pointInit.y = yinit;
	O.size = 12;
	O.nlingkaran = 0;
	return O;
}
	
Object makeMeriam(int xinitA, int yinitA) {
	int x[4] = {13, 13, -13, -13};
	int y[4] = {-117, -207, -207, -117};
	Object O;
	for(int i = 0;i < 4;i++) {
		O.P[i].x = x[i];
		O.P[i].y = y[i];
	}

	int xL[2] = {0, 0};
	int yL[2] = {0, 0};
	int rL[2] = {69, 117};
	for(int i = 0;i < 2;i++) {
		O.L[i].x = xL[i];
		O.L[i].y = yL[i];
		O.L[i].r = rL[i];
	}

	O.pointInit.x = xinitA;
	O.pointInit.y = yinitA;
	O.size = 4;
	O.nlingkaran = 2;
	O.lingkaranPenuh = 1;

	return O;
}

Object makeWheel(int xinit, int yinit) {
	int x[2] = {0,0};
	int y[2] = {30,10};
	Object o;
	for(int i = 0;i < 2;i++) {
		o.P[i].x = x[i];
		o.P[i].y = y[i];
		o.L[i].x = x[i];
		o.L[i].y = y[i];
		o.L[i].r = 20;
	}
	o.pointInit.x = xinit;
	o.pointInit.y = yinit;
	o.size = 2;
	o.nlingkaran = 1;
	o.lingkaranPenuh = 1;
	return o;
}

void wheelBounce(Object* O, int xtreamPoint, int *isXtream) {
	rotateWheelClockwise(O, 5);
	if (O->pointInit.y > xtreamPoint && !isXtream[0]) {
		moveHorizontal(O, 3);
		moveVertical(O, -5);
	}
	else  {
		moveHorizontal(O, 3);
		moveVertical(O, 5);
		isXtream[0]=1;
	}
}

Object makeLine(int xinit, int yinit) {
	int x[2] = {-65, 0};
	int y[2] = {  0, 0};
	Object O;
	for(int i = 0;i < 2;i++) {
		O.P[i].x = x[i];
		O.P[i].y = y[i];
	}
	O.pointInit.x = xinit;
	O.pointInit.y = yinit;
	O.size = 2;
	O.nlingkaran = 0;
	return O;
}

Object makeParasut(int xinit, int yinit) {
	int x[1] = {100};
	int y[1] = {80};
	Object O;
	O.L[0].x = x[0];
	O.L[0].y = y[0];
	O.L[0].r = 100;

	O.pointInit.x = xinit;
	O.pointInit.y = yinit;
	O.size = 1;
	O.nlingkaran = 1;
	O.lingkaranPenuh = 0;
	return O;
}

Object makePilot(int xinit, int yinit) {
	int x[15] = {0, 200, 100, 120, 100, 100, 120, 100, 80, 100, 100, 80, 100, 0, 100};
	int y[15] = {0, 0, 100, 100, 100, 130, 150, 130, 150, 130, 100, 100, 100, 0, 80};

	//badan pilot + setengan parasut
	int i;
	Object O;
	for (i=0; i<14;i++) {
		O.P[i].x = x[i];
		O.P[i].y = y[i];
	}

	//kepala pilot
	O.L[0].x = x[14];
	O.L[0].y = y[14];
	O.L[0].r = 10;

	O.pointInit.x = xinit;
	O.pointInit.y = yinit;
	O.size = i;
	O.nlingkaran = 1;
	O.lingkaranPenuh = 1;
	return O;
}

void pilotTerjun(Object *O) {
	moveVertical(O, 3);
}
