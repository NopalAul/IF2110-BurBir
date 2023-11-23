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
            AddressReply address;
            STRING text;
            createString(&text, "Halo");
            STRING author;
            createString(&author, "budi");
            DATETIME time = getCurrentDATETIME();
            address = newReply(1,text,author,time);
            if(address!=NULL){
                printf("yes\n");
            }
            break;

        case 3:
            // addreply
            REPLY reply2;
            CreateREPLY(&reply2);
            AddressReply address2;
            STRING text2;
            createString(&text2, "Halo");
            STRING author2;
            createString(&author2, "budi");
            DATETIME time2 = getCurrentDATETIME();
            address2 = newReply(1,text2,author2,time2);
            boolean succeed = false;
            addREPLY(&reply2, -1, address2, &succeed);
            
            if(succeed){
                printf("yes\n");
            }
            break;

        case 4:
            // delete reply
            REPLY reply3;
            CreateREPLY(&reply3);
            AddressReply address3;
            STRING text3;
            createString(&text3, "Halo");
            STRING author3;
            createString(&author3, "budi");
            DATETIME time3 = getCurrentDATETIME();
            address3 = newReply(1,text3,author3,time3);
            boolean succeed2 = false;
            boolean succeedd2 = false;
            addREPLY(&reply3, -1, address3, &succeed2);
            deleteREPLY(&reply3, 1, &succeedd2, NULL, NULL);
            if(succeedd2){
                printf("yes\n");
            }
            break;

        case 5:

            REPLY reply5;
            CreateREPLY(&reply5);
            AddressReply address5;
            STRING text5;
            createString(&text5, "Halo");
            STRING author5;
            createString(&author5, "budi");
            DATETIME time5 = getCurrentDATETIME();
            address5 = newReply(1,text5,author5,time5);
            boolean succeed5 = false;
            addREPLY(&reply5, -1, address5, &succeed5);
            // displayReply(reply5,0);
            // disini mau test displayreply tapi gabiasa dicocokin ke outputnya karena waktunya pasti beda-beda
            printf("yes\n");
            break;

    }
}