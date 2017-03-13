#ifndef MATRIX_H
#define MATRIX_H

typedef struct 
{
	char **M;
	int xsize, ysize;
}Matrix;

void initMatrix(Matrix *M, int x, int y);
void resetMatrix(Matrix *M);
void printMatrix(Matrix M);
void fillMatrix(Matrix *M, int x, int y, int color);

#endif
