#ifndef MATRIX_H
#define MATRIX_H

#include "../boolean/boolean.h"

#define ROW_CAP 5
#define COL_CAP 5

typedef struct photoElemen {
    char info;
    char color;
} PhotoElemen;

#define InfoPhoto(p) (p).info
#define ColorPhoto(p) (p).color

typedef struct photo {
    PhotoElemen photo[ROW_CAP][COL_CAP];
    int length;
} Photo;  //MODIFIKASI MATRIKS dengan struktur statik

#define PhotoElmt(p,i,j) (p).photo[i][j]
#define Length(p) (p).length

void createPhoto(Photo *p);

void displayPhoto(Photo p);

#endif