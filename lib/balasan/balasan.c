#include "balasan.h"
#include <stdlib.h>

void createListBalasan(ListBalasan *l, int capacity){
    BUFFER(*l) =  (BALASAN*) malloc(sizeof(BALASAN) * capacity);
    NEFF(*l) = 0;

    CAPACITY(*l) = capacity;

}

void createBalasan(ListBalasan *l, USER user, STRING text){
    BALASAN balasan;
    ID(balasan) = getAvailableID(*l);
    AUTHOR(balasan) = user;
    TEXT(balasan) = text;
    LIKE(balasan) = 0;
    DATETIME(balasan) = getCurrentDATETIME();
    BALASAN(balasan) = NOT_FOUND;
    BALASAN(*l, NEFF(*l)) = balasan;
    NEFF(*l)++;
    
}