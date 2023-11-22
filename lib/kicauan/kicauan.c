#include "kicauan.h"
#include <stdlib.h>
#include <stdio.h>

void createListKicau(ListKicau *l, int capacity){
    BUFFER(*l) =  (KICAU*) malloc(sizeof(KICAU) * capacity);
    NEFFLISTKICAU(*l) = 0;

    CAPACITY(*l) = capacity;
    
}

void createKicau(ListKicau *l, USER user, STRING text){
    KICAU kicau;
    IDKICAUAN(kicau) = getAvailableID(*l);
    printf("IDKICAUAN = %d\n",IDKICAUAN(kicau));
    AUTHOR(kicau) = user;
    TEXTKICAUAN(kicau) = text;
    LIKE(kicau) = 0;
    DATETIME(kicau) = getCurrentDATETIME();
    BALASANKICAUAN(kicau) = NULL;
    UTAS(kicau) = NULL;
    KICAU(*l, NEFFLISTKICAU(*l)) = kicau;
    NEFFLISTKICAU(*l)++;

}

void buatKicau(ListKicau *l,USER user){
    printf("Masukkan kicauan:\n");
    readKicauan();
    createKicau(l,user,string);
    printf("Selamat! kicauan telah diterbitkan!\n");
    printf("Detil kicauan:\n");
    displayKicau(KICAU(*l,NEFFLISTKICAU(*l)-1));
}

int getBanyakKicauan(ListKicau l){
    return NEFFLISTKICAU(l);
}

boolean isKicauanFull(ListKicau l){
    return NEFFLISTKICAU(l) == CAPACITY(l);
}

boolean isKicauanEmpty(ListKicau l){
    return NEFFLISTKICAU(l) == 0;
}

void sukaKicauan(ListKicau *l,int id,USER currUser ){
    int i = 0;
    while (i < NEFFLISTKICAU(*l) && IDKICAUAN(KICAU(*l,i)) != id){
        i++;
    }
    if(IDKICAUAN(KICAU(*l,i)) == id){
        if(isAuthorKicauPublicOrFriend(KICAU(*l,i),currUser)){
            LIKE(KICAU(*l,i))++;
            printf("Selamat! kicauan telah disukai! Detil kicauan:\n");
            displayKicau(KICAU(*l,i));
        }
        else{
            printf("Wah, kicauan tersebut dibuat oleh akun privat! Ikuti akun itu dulu ya\n");
        }
    }
    else{
        printf("Tidak ditemukan kicauan dengan ID %d\n",id);
    }
}

void ubahKicauan(ListKicau *l,USER currUser,int id){
    int i = 0;
    while (i < NEFFLISTKICAU(*l) && IDKICAUAN(KICAU(*l,i)) != id){
        i++;
    }
    if(IDKICAUAN(KICAU(*l,i)) == id){
        if(isUserEqual(currUser,AUTHOR(KICAU(*l,i)))){
            printf("Masukkan kicauan baru:\n");
            readKicauan();
            TEXTKICAUAN(KICAU(*l,i)) = string;
            printf("Selamat! kicauan telah diterbitkan!\n Detil kicauan:\n");
            displayKicau(KICAU(*l,i));
        }
        else{
            printf("Kicauan dengan ID = %d bukan milikmu\n",id);
        }
    }
    else{
        printf("Tidak ditemukan kicauan dengan ID = %d\n",id);
    }
}



int getAvailableID(ListKicau l){
    
    if (isKicauanEmpty(l)){
        return 1;
    } else {
        int max = 0;
        for (int i = 0; i < NEFFLISTKICAU(l); i++){
            if (IDKICAUAN(KICAU(l,i)) > max){
                max = IDKICAUAN(KICAU(l,i));
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
    KICAU(*l, NEFFLISTKICAU(*l)) = *kicau;
    NEFFLISTKICAU(*l)++;
}

void shrinkKicauan(ListKicau *l,int num){
    CAPACITY(*l) -= num;
    BUFFER(*l) = (KICAU*) realloc(BUFFER(*l),sizeof(KICAU) * CAPACITY(*l));
}

void displayKicau(KICAU kicau){

    printf("| ID = %d\n",IDKICAUAN(kicau));
    printf("| ");
    displayString(USERNAME(AUTHOR(kicau)));
    printf("| ");
    displayDATETIME(DATETIME(kicau));
    printf("| ");
    displayString(TEXTKICAUAN(kicau));
    printf("| Disukai: %d\n",LIKE(kicau));

}

void displayKicauan(ListKicau l,USER currUser){
    for (int i = 0; i < NEFFLISTKICAU(l); i++){
        if(isAuthorKicauPublicOrFriend(KICAU(l,i),currUser)){
            displayKicau(KICAU(l,i));
        }
    }
}

boolean isAuthorKicauPublicOrFriend(KICAU k,USER currUser){
    if (ACCOUNTTYPE(AUTHOR(k))){
        return true;
    } 
    else {
      if(isFriend(userID(currUser),userID(AUTHOR(k)))){
            return true;
      }
      else{
        return false;
      }
        
    }

}


// int main(){
    
//     KICAU k;
//     USER user;
//     ListUser l;
//     createListUser(&l);
//     daftarUSER(&l);
    
    
// }