#include "lingkaran.h"
#include "matrix.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

void gambarLingkaran(Lingkaran* L, Matrix* M, char c, int penuh) {
    if (sizeof(L) != 0){
        if ((sizeof(M -> xsize)) != 0) {
            if (sizeof(M -> ysize != 0)) {
                    int x = L->x;
                    int y = L->y + L->r;
                    int err = 0;
                    while (x - L->x <= y - L->y) {
                        int dx = x - L->x;
                        int dy = y - L->y;

                        //setengan lingkaran
                        if (L->x + dx >= 0 && L->x + dx < M->xsize && L->y - dy >= 0 && L->y - dy < M->ysize) {
                            M -> M[L->y - dy][L->x + dx] = c;
                        }
                        if (L->x - dx >= 0 && L->x - dx < M->xsize && L->y - dy >= 0 && L->y - dy < M->ysize) {
                            M -> M[L->y - dy][L->x - dx] = c;
                        }

                        if (L->x + dy >= 0 && L->x + dy < M->xsize && L->y - dx >= 0 && L->y - dx < M->ysize) {
                            M -> M[L->y - dx][L->x + dy] = c;
                        }
                        if (L->x - dy >= 0 && L->x - dy < M->xsize && L->y - dx >= 0 && L->y - dx < M->ysize) {
                            M -> M[L->y - dx][L->x - dy] = c;
                        }

                        //lingkaran penuh
                        if (penuh) {
                            if (L->x + dx >= 0 && L->x + dx < M->xsize && L->y + dy >= 0 && L->y + dy < M->ysize) {
                                M -> M[L->y + dy][L->x + dx] = c;
                            }
                            if (L->x - dx >= 0 && L->x - dx < M->xsize && L->y + dy >= 0 && L->y + dy < M->ysize) {
                                M -> M[L->y + dy][L->x - dx] = c;
                            }
                            
                            if (L->x + dy >= 0 && L->x + dy < M->xsize && L->y + dx >= 0 && L->y + dx < M->ysize) {
                                M -> M[L->y + dx][L->x + dy] = c;
                            }
                            if (L->x - dy >= 0 && L->x - dy < M->xsize && L->y + dx >= 0 && L->y + dx < M->ysize) {
                                M -> M[L->y + dx][L->x - dy] = c;
                            }
                        }
                        

                        if (err <= 0)
                        {
                            dx += 1;
                            err += 2*dx + 1;
                        }
                        if (err > 0)
                        {
                            dy -= 1;
                            err -= 2*dy + 1;
                        }

                        x = L->x + dx;
                        y = L->y + dy;
                }
            }
        }
    }
}

int isLingkaranPutus(Lingkaran* L, Matrix* M, char c) {
    int ret = 0;
    if (sizeof(L) != 0){
        if ((sizeof(M -> xsize)) != 0) {
            if (sizeof(M -> ysize != 0)) {
                    int x = L->x;
                    int y = L->y + L->r;
                    int err = 0;
                    while (x - L->x <= y - L->y && ret == 0) {
                        int dx = x - L->x;
                        int dy = y - L->y;
                        if (L->x + dx >= 0 && L->x + dx < M->xsize && L->y + dy >= 0 && L->y + dy < M->ysize) {
                            if (M -> M[L->y + dy][L->x + dx] != c) {
                                ret = 1;
                            };
                        }
                        if (L->x - dx >= 0 && L->x - dx < M->xsize && L->y + dy >= 0 && L->y + dy < M->ysize) {
                            if (M -> M[L->y + dy][L->x - dx] != c) {
                                ret = 1;
                            };
                        }
                        if (L->x + dx >= 0 && L->x + dx < M->xsize && L->y - dy >= 0 && L->y - dy < M->ysize) {
                            if (M -> M[L->y - dy][L->x + dx] != c) {
                                ret = 1;
                            };
                        }
                        if (L->x - dx >= 0 && L->x - dx < M->xsize && L->y - dy >= 0 && L->y - dy < M->ysize) {
                            if (M -> M[L->y - dy][L->x - dx] != c) {
                                ret = 1;
                            };
                        }
                        if (L->x + dy >= 0 && L->x + dy < M->xsize && L->y + dx >= 0 && L->y + dx < M->ysize) {
                            if (M -> M[L->y + dx][L->x + dy] != c) {
                                ret = 1;
                            };
                        }
                        if (L->x - dy >= 0 && L->x - dy < M->xsize && L->y + dx >= 0 && L->y + dx < M->ysize) {
                            if (M -> M[L->y + dx][L->x - dy] != c) {
                                ret = 1;
                            };
                        }
                        if (L->x + dy >= 0 && L->x + dy < M->xsize && L->y - dx >= 0 && L->y - dx < M->ysize) {
                            if (M -> M[L->y - dx][L->x + dy] != c) {
                                ret = 1;
                            };
                        }
                        if (L->x - dy >= 0 && L->x - dy < M->xsize && L->y - dx >= 0 && L->y - dx < M->ysize) {
                            if (M -> M[L->y - dx][L->x - dy] != c) {
                                ret = 1;
                            };
                        }

                        if (err <= 0)
                        {
                            dx += 1;
                            err += 2*dx + 1;
                        }
                        if (err > 0)
                        {
                            dy -= 1;
                            err -= 2*dy + 1;
                        }

                        x = L->x + dx;
                        y = L->y + dy;
                }
            }
        }
    }
    return ret;
}
