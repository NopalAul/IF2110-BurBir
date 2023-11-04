#include "../matrix.h"
#include <stdio.h>

int main(){
    int type;
    scanf("%d", &type);
    switch (type){
        case 1:
            //Test untuk PhotoElemen
            PhotoElemen p;
            InfoPhoto(p) = '@';
            ColorPhoto(p) = 'B';
            printf("%c %c\n", InfoPhoto(p), ColorPhoto(p));
            break;
        case 2:
            //test untuk createPhoto
            Photo foto;
            createPhoto(&foto);
            printf("%d\n", Length(foto));
            break;
        case 3:
            Photo photo;
            createPhoto(&photo);
            PhotoElemen el = {'*', 'R'};
            for (int i = 0; i < 5; i++){
                for (int j = 0; j < 5; j++){
                    PhotoElmt(photo,i,j) = el;
                }
            }
            Length(photo) = 5;
            displayPhoto(photo);
            break;
    }
}