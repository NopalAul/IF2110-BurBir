#include "../reply.h"
#include <stdio.h>

int main(){
    int type;
    scanf("%d", &type);
    switch (type){
        case 1:
            REPLY reply;
            CreateREPLY(&reply);
            printf("%d\n", isEmptyREPLY(reply));
            break;

        case 2:
            
            break;
    }
}