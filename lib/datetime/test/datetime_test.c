#include <stdio.h>
#include "../datetime.h"

int main(){
    int type;
    scanf("%d", &type);
    switch (type)
    {
        case 1:
            DATETIME dt;
            createDATETIME(&dt);
            if(DAY(dt) == 0 && MONTH(dt) == 0 && YEAR(dt) == 0 && HOUR(dt) == 0 && MINUTE(dt) == 0 && SECOND(dt) == 0) {
                printf("%d",1);
            }
            else {
                printf("%d",0);
            }
            break;
    }
}