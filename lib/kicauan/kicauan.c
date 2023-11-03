#include "kicauan.h"
#include <stdlib.h>
#include <stdio.h>

void createListKicau(ListKicau *l, int capacity){
    BUFFER(*l) =  (KICAU*) malloc(sizeof(KICAU) * capacity);
    NEFF(*l) = 0;

    CAPACITY(*l) = capacity;

    
}

void createKicau(ListKicau *l, USER user, STRING text){
    KICAU kicau;
    ID(kicau) = getAvailableID(*l);
    AUTHOR(kicau) = user;
    TEXT(kicau) = text;
    LIKE(kicau) = 0;
    DATETIME(kicau) = getCurrentDATETIME();
    BALASAN(kicau) = NOT_FOUND;
    KICAU(*l, NEFF(*l)) = kicau;
    NEFF(*l)++;
    
}

int getBanyakKicauan(ListKicau l){
    return NEFF(l);
}

boolean isKicauanFull(ListKicau l){
    return NEFF(l) == CAPACITY(l);
}

boolean isKicauanEmpty(ListKicau l){
    return NEFF(l) == 0;
}

void sukaKicauan(ListKicau *l,int id ){
    int i = 0;
    while (i < NEFF(*l) && ID(KICAU(*l,i)) != id){
        i++;
    }
    if(ID(KICAU(*l,i)) == id){
        LIKE(KICAU(*l,i))++;
    }
}

void ubahKicauan(KICAU *kicau,STRING text){
    TEXT(*kicau) = text;
    
}

void sortKicauan();

int getAvailableID(ListKicau l){
    
    if (isKicauanEmpty(l)){
        return 1;
    } else {
        int max = 0;
        for (int i = 0; i < NEFF(l); i++){
            if (ID(KICAU(l,i)) > max){
                max = ID(KICAU(l,i));
            }
        }
        return max+1;
    }
}

void expandKicauan (ListKicau *l,int num){
    CAPACITY(*l) += num;
    BUFFER(*l) = (KICAU*) realloc(BUFFER(*l),sizeof(KICAU) * CAPACITY(*l));
}

void addKicauan(ListKicau *l, KICAU *kicau){
    if (isKicauanFull(*l)){
        expandKicauan(l,1);
    }
    KICAU(*l, NEFF(*l)) = *kicau;
    NEFF(*l)++;
}

void shrinkKicauan(ListKicau *l,int num){
    CAPACITY(*l) -= num;
    BUFFER(*l) = (KICAU*) realloc(BUFFER(*l),sizeof(KICAU) * CAPACITY(*l));
}

void displayKicau(KICAU kicau){

    printf("| ID = %d\n",ID(kicau));
    printf("| ");
    displayString(USERNAME(AUTHOR(kicau)));
    printf("| ");
    displayDATETIME(DATETIME(kicau));
    printf("| ");
    displayString(TEXT(kicau));
    printf("| Disukai: %d\n",LIKE(kicau));

}

void displayKicauan(ListKicau l){
    for (int i = 0; i < NEFF(l); i++){
        displayKicau(KICAU(l,i));
    }
}

// int main(){
    
//     KICAU k;
//     USER user;
//     ListUser l;
//     createListUser(&l);
//     daftarUSER(&l);
    
    
// }