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
    printf("ID = %d\n",ID(kicau));
    AUTHOR(kicau) = user;
    TEXT(kicau) = text;
    LIKE(kicau) = 0;
    NEXTREPLYID(kicau) = 1;
    DATETIME(kicau) = getCurrentDATETIME();
    BALASAN(kicau) = NULL;
    CreateListUtas(&UTAS(kicau));
    KICAU(*l, NEFF(*l)) = kicau;
    NEFF(*l)++;

}

void buatKicau(ListKicau *l,USER user){
    printf("Masukkan kicauan:\n");
    readKicauan();
    createKicau(l,user,string);
    printf("Selamat! kicauan telah diterbitkan!\n");
    printf("Detil kicauan:\n");
    displayKicau(KICAU(*l,NEFF(*l)-1));
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

void sukaKicauan(ListKicau *l,int id,USER currUser ){
    int i = 0;
    while (i < NEFF(*l) && ID(KICAU(*l,i)) != id){
        i++;
    }
    if(ID(KICAU(*l,i)) == id){
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
    while (i < NEFF(*l) && ID(KICAU(*l,i)) != id){
        i++;
    }
    if(ID(KICAU(*l,i)) == id){
        if(isUserEqual(currUser,AUTHOR(KICAU(*l,i)))){
            printf("Masukkan kicauan baru:\n");
            readKicauan();
            TEXT(KICAU(*l,i)) = string;
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

void displayKicauan(ListKicau l,USER currUser){
    for (int i = 0; i < NEFF(l); i++){
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

void tulisUtas(UtasList *l, USER user, int IDKicau)
/* Membuat utas baru dari kicauan utama. Utas dapat dilanjutkan 
I.S :   IDKicau, mungkin bukan milik pengguna saat ini
F.S :   IDUtas terbentuk, index Utas terbentuk, terisi kicauan baru, length ListUtas bertambah */
{
    Address p;
    p = FIRST(*l);
    int IDUtas = -1; // assign apa?
    int index;
    STRING content;

    // if(true) {
    //     // Kondisi IDKicau tidak ditemukan
    //     printf("Kicauan tidak ditemukan\n\n");
    // } 
    // else if(true) {
    //     // Kondisi IDKicau bukan milik pengguna saat ini
    //     printf("Utas ini bukan milik anda!\n\n");
    // }
    // else
    {
        // Kondisi milik pengguna saat ini
        printf("\nUtas berhasil dibuat!\n\n");
        printf("Masukkan kicauan:\n");
        readKicauan();
        copyString(&content, string); 
        printf("\n");
        
        insertFirst(l, IDUtas, user, content);

        do{
            printf("Apakah Anda ingin melanjutkan utas ini? (YA/TIDAK) ");
            readString(); printf("\n");
            if(!isWordEqual(string, "YA") && !isWordEqual(string, "TIDAK")) {
                printf("Input Anda tidak valid. Masukkan lagi yuk!\n\n");
            }
        } while(!isWordEqual(string, "YA") && !isWordEqual(string, "TIDAK"));

        // Pilihan YA, terus lanjutkan utas
        while(isWordEqual(string, "YA")) {
            index = length(*l);
            printf("len: %d\n",length(*l)); // delete
            sambungUtas(l, IDUtas, index);
            printf("Apakah Anda ingin melanjutkan utas ini? (YA/TIDAK) ");
            readString(); printf("\n");
            if(!isWordEqual(string, "YA") && !isWordEqual(string, "TIDAK")) {
                printf("Input Anda tidak valid. Masukkan lagi yuk!\n\n");
            }
        }
        printf("Utas selesai!\n\n");
    }
}

void BALAS(ListKicau *lk, int currentID)
{
    if (!isStringNumeric(leftInfo) || !isStringNumeric(rightInfo)){
        printf('Command yang Anda masukkan tidak sesuai!\n\n');
        return;
    }
    int idKicau = stringToInteger(leftInfo);
    if (idKicau >= (*lk).nEFF || idKicau <= 0){
        printf("Wah, tidak terdapat kicauan dengan id tersebut!\n\n");
        return;
    }
    int idReply = stringToInteger(rightInfo);
    STRING author;;
    createEmptyString(&author);
    if (idReply == -1) copyString(&author, USERNAME(AUTHOR(KICAU(*lk, idKicau))));
    else ReplyAuhtor(BALASAN(KICAU(*lk,idKicau)), idReply, &author);
    if (author.length == 0){
        printf("Wah, tidak terdapat balasan yang ingin Anda balas!\n\n");
        return;
    }
    if (!isFriend(currentID, searchUser(author))){
        prnintf("Wah, Anda tidak bisa membalas kicauan atau balasan dari akun privat yang bukan teman Anda!\n\n");
        return;
    }
    printf("\nMasukkan balasan:\n");
    readString();
    AddressReply p = newReply(NEXTREPLYID(KICAU(*lk,idKicau)), string, USERNAME(USER(UserList, currentID)), getCurrentDATETIME());
    if (p == NULL){
        printf("Error: Gagal membuat balasan.\n\n");
        return;
    }
    boolean succeed = false;
    addREPLY(&BALASAN(KICAU(*lk,idKicau)), idReply, p, &succeed);
    if (!succeed) {
        printf("Error: Gagal menerbitkan balasan.\n\n");
        free(p);
        return;
    } 
    NEXTREPLYID(KICAU(*lk,idKicau))++;
    printf("Selamat! Balasan telah diterbitkan!\nDetil balasan:\n");
    displaySpecificReply(p, 0, true);
    printf("\n");
}

void DISPLAYBALASAN(ListKicau *lk, int currentID)
{
    if (!isStringNumeric(leftInfo)){
        printf("Command yang Anda masukkan tidak sesuai!\n\n");
        return;
    }
    int idKicau = stringToInteger(leftInfo);
    if (idKicau <= 0 || idKicau >= (*lk).nEFF){
        printf("Wah, tidak terdapat kicauan dengan id tersebut!\n\n");
        return;
    }
    if (isEmptyREPLY(BALASAN(KICAU(*lk, idKicau)))){
        printf("Belum terdapat balasan apapun pada kicauan tersebut. Yuk, balas kicauan tersebut!\n\n");
        return;
    }
    printf("\n");
    displayBalasanHandler(BALASAN(KICAU(*lk, idKicau)), currentID, 0);
    printf("\n");
}

void displayBalasanHandler(REPLY r, int currentID, int depth)
{
    if(!isEmptyREPLY(r)){
        boolean noSensor = ACCOUNTTYPE(USER(UserList,searchUser(REPLYAUTHOR(r)))) || isFriend(currentID, REPLYID(r));
        displaySpecificReply(r,depth, noSensor);
        displayBalasanHandler(CHILD(r), currentID, depth+1);
        displayBalasanHandler(SIBLING(r), currentID, depth);
    }
}

void HAPUSBALASAN(ListKicau *lk, int currentID)
{
    if (!isStringNumeric(leftInfo) || !isStringNumeric(rightInfo)){
        printf("Command yang Anda masukkan tidak sesuai!\n\n");
        return;
    }
    int idKicau = stringToInteger(leftInfo);
    if (idKicau <= 0 || idKicau >= (*lk).nEFF){
        printf("Walawe, tidak ada kicauan dengan id tersebut!\n\n");
        return;
    }
    int idReply = stringToInteger(rightInfo);
    STRING author;
    createEmptyString(&author);
    ReplyAuhtor(BALASAN(KICAU(*lk, idKicau)), idReply, &author);
    if (author.length == 0){
        printf("Walawe, tidak ada balasan dengan id tersebut.\n\n");
        return;
    }
    if (!isStringEqual(USERNAME(USER(UserList, currentID)), author)){
        printf("Ara-ara, ini balasan punya siapa? Jangan dihapus ya.\n\n");
    }
    boolean succeed = false;
    deleteREPLY(&BALASAN(KICAU(*lk, idKicau)), idReply, &succeed, NULL, NULL);
    if (!succeed) {
        printf("Error: Sepertinya ada masalah dalam proses penghapusan.\n\n");
        return;
    }
    printf("Balasan berhasil dihapus.\n\n");
}

// int main(){
    
//     KICAU k;
//     USER user;
//     ListUser l;
//     createListUser(&l);
//     daftarUSER(&l);
    
    
// }