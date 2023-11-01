#include <stdio.h>

#define kata "STOP"

typedef struct 
{
    int length;
    char x;
} taimu;

typedef taimu TAI[20];

int main(){
    TAI memek;
    for (int i = 0; i < 20; i++){
        memek[i].length = i+1;
        memek[i].x = 'A'+i;
    }
    for (int i = 19; i >= 0; i--){
        printf("l : %d --- x : %c\n", memek[i].length, memek[i].x);
    }
    return 0;
}