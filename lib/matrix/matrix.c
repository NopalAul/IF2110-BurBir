#include "matrix.h"
#include <stdio.h>

void createPhoto(Photo *p)
{
    Length(*p) = 0;
}

void displayPhoto(Photo p)
{
    for (int i = 0; i < p.length; i++){
        for (int j = 0; j < p.length; j++){
            printf("%c %c", InfoPhoto(PhotoElmt(p, i, j)), ColorPhoto(PhotoElmt(p, i, j)));
            if (j != Length(p)-1){
                printf(" ");
            }
        }
        printf("\n");
    }
}