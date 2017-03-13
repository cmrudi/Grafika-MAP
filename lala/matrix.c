#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>

void initMatrix(Matrix *M, int x, int y) {
	M->xsize = x;
	M->ysize = y;
	M->M = (char**) malloc(y * sizeof(char*));
	for(int i = 0;i < y;i++) {
		M->M[i] = (char*) malloc(x * sizeof(char*));
	}
}

void resetMatrix(Matrix *M) {
	for(int i = 0;i < M->ysize;i++) {
		for(int j = 0;j < M->xsize;j++) {
			M->M[i][j] = 0;
		}
	}
}

void printMatrix(Matrix M) {
	for(int i = 0;i < M.ysize;i++) {
		for(int j = 0;j < M.xsize;j++) {
			printf("%c",M.M[i][j]);
		}
		printf("\n");
	}
}

void fillMatrix(Matrix *M,int x,int y, int color) {
	int tempX, tempY;
	if((x>5) && (x < 1195) && (y>5) && (y < 695)) {
		tempX = x; tempY = y+1;
    	if (M->M[tempY][tempX]==0) {
			M->M[tempY][tempX] = color;
			fillMatrix(M, tempX, tempY, color);
		}
		
		tempX = x; tempY = y-1;
    	if (M->M[tempY][tempX]==0) {
			M->M[tempY][tempX] = color;
			fillMatrix(M, tempX, tempY, color);
		}
		
    	tempX = x+1; tempY = y;
    	if (M->M[tempY][tempX]==0) {
			M->M[tempY][tempX] = color;
			fillMatrix(M, tempX, tempY, color);
		}
		
		tempX = x-1; tempY = y;
    	if (M->M[tempY][tempX]==0) {
			M->M[tempY][tempX] = color;
			fillMatrix(M, tempX, tempY, color);
		}
	}
}
