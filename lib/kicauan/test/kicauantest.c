#include <stdio.h>
#include "../kicauan.h"

int main(){
    int type;
    // STRING temp;
    scanf("%d", &type);
    switch (type)
    {
        case 1:
            ListKicau l;
            createListKicau(&l, 10);
            printf("%d\n", isKicauanEmpty(l));
            break;
        
        case 2:

            ListKicau l2;
            createListKicau(&l2, 10);
            STRING temp;
            createEmptyString(&temp);
            USER user1;
            createKicau(&l2, user1, temp);
            createKicau(&l2, user1, temp);
            printf("%d\n" , getBanyakKicauan(l2));
            break;
        case 3:
            ListKicau l3;
            createListKicau(&l3, 10);
            STRING temp2;
            createEmptyString(&temp2);
            createString(&temp2, "Halo");
            USER user2;
            createKicau(&l3, user2, temp2);
            printf("%d\n" , isKicauanFull(l3));
            break;
    }   
}