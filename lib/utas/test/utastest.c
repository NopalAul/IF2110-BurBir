#include <stdio.h>
#include "../utas.h"

int main(){
    USER user;
    STRING uname;
    STRING content;
    int type;
    scanf("%d", &type);
    switch (type)
    {
        case 1:
            // create utas
            UtasList l1;
            CreateListUtas(&l1);
            if(isEmpty(l1))
                printf("%d",1);
            else
                printf("%d",0);
            break;
        case 2:
            // length
            UtasList l2;
            CreateListUtas(&l2);
            createString(&content, "tes");
            createString(&uname, "ucup");
            copyString(&USERNAME(user), uname);
            insertFirst(&l2, 1, user, content);
            printf("%d",length(l2));
            break;
        case 3:
            // insert first
            UtasList l3;
            CreateListUtas(&l3);
            createString(&content, "tes");
            createString(&uname, "ucup");
            copyString(&USERNAME(user), uname);
            insertFirst(&l3, 1, user, content);
            
            Address p = FIRSTUTAS(l3);
            displayString(USERNAME(AUTHORUTAS(p)));
            displayString(CONTENT(p));
            printf("%d",length(l3)); 
            break;
        case 4:
            // insert last
            UtasList l4;
            CreateListUtas(&l4);
            createString(&content, "tes");
            createString(&uname, "ucup");
            copyString(&USERNAME(user), uname);
            insertFirst(&l4, 1, user, content);
            createString(&content, "tes2");
            insertLast(&l4, 1, user, content);
            
            Address p2 = FIRSTUTAS(l4);
            displayString(USERNAME(AUTHORUTAS(p2)));
            displayString(CONTENT(NEXT(p2)));
            printf("%d",length(l4));
            break;
        case 5:
            // insert at
            UtasList l5;
            CreateListUtas(&l5);
            createString(&content, "tes");
            createString(&uname, "ucup");
            copyString(&USERNAME(user), uname);
            insertFirst(&l5, 1, user, content);
            createString(&content, "tes2");
            insertAt(&l5, 1, 1, user, content);
            
            Address p3 = FIRSTUTAS(l5);
            displayString(USERNAME(AUTHORUTAS(p3)));
            displayString(CONTENT(NEXT(p3)));
            printf("%d",length(l5)); 
            break;
        case 6:
            // delete first
            UtasList l6;
            CreateListUtas(&l6);
            createString(&content, "tes");
            createString(&uname, "ucup");
            copyString(&USERNAME(user), uname);
            insertFirst(&l6, 1, user, content);
            createString(&content, "tes2");
            insertAt(&l6, 1, 1, user, content);
            deleteFirst(&l6);
            
            Address p4 = FIRSTUTAS(l6);
            displayString(USERNAME(AUTHORUTAS(p4)));
            displayString(CONTENT(p4));
            printf("%d",length(l6)); 
            break;
        case 7:
            // delete at
            UtasList l7;
            CreateListUtas(&l7);
            createString(&content, "tes");
            createString(&uname, "ucup");
            copyString(&USERNAME(user), uname);
            insertFirst(&l7, 1, user, content);
            createString(&content, "tes2");
            insertAt(&l7, 1, 1, user, content);
            deleteAt(&l7,0);
            
            Address p5 = FIRSTUTAS(l7);
            displayString(USERNAME(AUTHORUTAS(p5)));
            displayString(CONTENT(p5));
            printf("%d",length(l7)); 
            break;
    }   
}
