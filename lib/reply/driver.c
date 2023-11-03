#include <stdio.h>
#include "reply.h"


int main() {
    REPLY r;
    CreateREPLY(&r);
    STRING text, author;
    createString(&text, "Ini textnya Bang");
    createString(&author, "Bang Berto");
    DATETIME now = getCurrentDATETIME();
    AddressReply temp1 = newReply(1, text, author, now);
    AddressReply temp2 = newReply(2, text, author, now);
    AddressReply temp3 = newReply(3, text, author, now);
    AddressReply temp4 = newReply(4, text, author, now);
    AddressReply temp5 = newReply(5, text, author, now);
    AddressReply temp6 = newReply(6, text, author, now);
    AddressReply temp7 = newReply(7, text, author, now);
    AddressReply temp8 = newReply(8, text, author, now);
    AddressReply temp9 = newReply(9, text, author, now);
    AddressReply temp10 = newReply(10, text, author, now);
    boolean succeded = false;
    addREPLY(&r, -1, temp1,&succeded);
    succeded = false;
    addREPLY(&r, -1, temp2,&succeded);
    succeded = false;
    addREPLY(&r, -1, temp3,&succeded);
    succeded = false;
    addREPLY(&r, 1, temp4,&succeded);
    succeded = false;
    addREPLY(&r, 4, temp5,&succeded);
    succeded = false;
    addREPLY(&r, 5, temp6,&succeded);
    succeded = false;
    addREPLY(&r, 6, temp7,&succeded);
    succeded = false;
    addREPLY(&r, 5, temp8,&succeded);
    succeded = false;
    addREPLY(&r, 5, temp9,&succeded);
    succeded = false;
    addREPLY(&r, 1, temp10,&succeded);
    displayReply(r, 0);
    succeded = false;
    printf("\n\n ------------------------------ \n\n\n");
    deleteREPLY(&r, 5, &succeded, NULL, NULL);
    displayReply(r,0);
}
