#ifndef LINGKARAN_H
#define LINGKARAN_H
#include "matrix.h"

typedef struct
{
	int x, y, r;
} Lingkaran;

//Menggambar lingkaran pada matriks
void gambarLingkaran(Lingkaran* L, Matrix* M, char c, int penuh);

//Memeriksa apakah semua bagian lingkaran pada L pada matriks M berisi karakter c
//Mengembalikan 0 jika semuanya berisi karakter c
//Mengembalikan 1 jika ada bagian yang tertimpa karakter lain
int isLingkaranPutus(Lingkaran* L, Matrix* M, char c);

#endif
