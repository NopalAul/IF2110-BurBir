#include "../charmachine.h"
#include <stdio.h>

int main(){
    int type;
    scanf("%d", &type);
    switch (type){
        case 1:
            //
            START();
            char temp[100];
            int i = 0;
            while (!EOP){
                temp[i] = currentChar;
                ADV();
                i++;
            }
            temp[i] = '\0';
            printf("%s\n", temp);
            stopRead();
            break;
    }
}