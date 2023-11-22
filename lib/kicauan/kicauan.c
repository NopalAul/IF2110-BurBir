#include "kicauan.h"
#include <stdlib.h>
#include <stdio.h>

void createListKicau(ListKicau *l, int capacity){
    BUFFER(*l) =  (KICAU*) malloc(sizeof(KICAU) * capacity);
    NEFF(*l) = 0;

    CAPACITY(*l) = capacity;
    (*l).NextUtasID = 1;
}

void createKicau(ListKicau *l, USER user, STRING text){
    KICAU kicau;
    ID(kicau) = getAvailableID(*l);
    printf("ID = %d\n",ID(kicau));
    AUTHOR(kicau) = user;
    TEXT(kicau) = text;
    LIKE(kicau) = 0;
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

/* UTAS */

int getIDKicau(ListKicau l,int IDUtas) {
    int IDKicau;
    for (int i = 0; i < NEFF(l); i++){
        if (IDUTAS(KICAU(l,i).utas) == IDUtas){
            IDKicau = i;
            break;
        }
    }

    return IDKicau;
}

boolean isIDUtasExist(ListKicau l, int IDUtas) {
    boolean exist = false;
    for (int i = 0; i < NEFF(l); i++){
        if (IDUTAS(KICAU(l,i).utas) == IDUtas){
            exist = true;
            break;
        }
    }
    return exist;
}

void insertUtas(ListKicau *l, USER user, int IDUtas, int index) //PERLU PARAMETER USER?
/* Melakukan sambung utas, menambah utas di posisi index yang dituju dari sebuah utas utama.
I.S :   IDUtas, mungkin bukan milik pengguna saat ini
F.S :   terisi kicauan baru, index Utas bertambah */
{   
    int IDKicau = getIDKicau(*l,IDUtas);
    Address p;
    p = FIRSTUTAS(KICAU(*l,IDKicau).utas);
    STRING content;

    if(isIDUtasExist(*l,IDUtas) == false) {
        // Kondisi tidak ditemukan IDUtas
        printf("Utas tidak ditemukan!\n\n");
    }
    else if(index > length(KICAU(*l,IDKicau).utas)) {
        // Kondisi index terlalu tinggi
        printf("Index terlalu tinggi!\n\n");
    }
    else if(!isStringEqual(USERNAME(user), USERNAME(AUTHOR(KICAU(*l,IDKicau))))) {
        // Kondisi IDUtas bukan milik pengguna saat ini
        printf("Anda tidak bisa menyambung utas ini!\n\n");
    }
    else
        {
            // Kondisi valid
            printf("Masukkan kicauan:\n");
            readKicauan(); copyString(&content, string);
            printf("\n");
            

            insertAt(&KICAU(*l,IDKicau).utas, IDUtas, index, AUTHORUTAS(p), content);
        }
}

void hapusUtas(ListKicau *l, USER user, int IDUtas, int index)
{
    /* Menghapus utas sesuai posisi index, tidak dapat menghapus index 0 (ID kicauan utama) 
    I.S :   IDUtas, mungkin bukan milik pengguna saat ini
    F.S :   Utas pada index terhapus, index Utas berkurang?*/

    int IDKicau = getIDKicau(*l,IDUtas);
    if(isIDUtasExist(*l,IDUtas) == false) {
        // Kondisi utas tidak ditemukan
        printf("Utas tidak ditemukan!\n\n");
    }
    else if(!isStringEqual(USERNAME(user), USERNAME(AUTHOR(KICAU(*l,IDKicau))))) {
        // Kondisi IDUtas bukan milik pengguna saat ini
        printf("Anda tidak bisa menghapus kicauan dalam utas ini!\n\n");
    }
    else
    {
        // Kondisi utas milik sendiri
        if(index > length(KICAU(*l,IDKicau).utas)-1) {
            // Kondisi index utas tidak ditemukan
            printf("Kicauan sambungan dengan index %d tidak ditemukan pada utas!\n\n",index);
        }
        else if(index == 0) {
            // Kondisi index = 0
            printf("Anda tidak bisa menghapus kicauan utama!\n\n");
        }
        else {
            // Kondisi valid
            deleteAt(&KICAU(*l,IDKicau).utas,index-1);
            printf("Kicauan sambungan berhasil dihapus!\n\n");
        }
    }
}

void sambungUtas(ListKicau *l, USER user, int IDUtas, int index)
{
    insertUtas(l,user,IDUtas,index-1);
}

void tulisUtas(ListKicau *l, USER user, int IDKicau)
/* Membuat utas baru dari kicauan utama. Utas dapat dilanjutkan 
I.S :   IDKicau, mungkin bukan milik pengguna saat ini
F.S :   IDUtas terbentuk, index Utas terbentuk, terisi kicauan baru, length ListUtas bertambah */
{
    if(IDKicau > (*l).nEFF) {
        printf("Kicauan tidak ditemukan\n\n");
    }
    else if(!isStringEqual(USERNAME(user), USERNAME(AUTHOR(KICAU(*l,IDKicau-1))))) {
        printf("Utas ini bukan milik anda!\n\n");
    }
    else if(IDUTAS(KICAU(*l,IDKicau-1).utas) != ID_UNDEF){
        printf("ID Kicau ini sudah mempunyai utas!\n\n");
    }
    else {
        Address p;
        p = FIRSTUTAS(KICAU(*l,IDKicau-1).utas);
        IDUTAS(KICAU(*l,IDKicau-1).utas) = (*l).NextUtasID;
        printf("id utas: %d\n",IDUTAS(KICAU(*l,IDKicau-1).utas)); //delete
        (*l).NextUtasID++;
        int index;
        STRING content;

        // Kondisi milik pengguna saat ini
        printf("\nUtas berhasil dibuat!\n\n");
        printf("Masukkan kicauan:\n");
        readKicauan();
        copyString(&content, string); 
        printf("\n");
        
        insertFirst(&KICAU(*l,IDKicau-1).utas, IDUTAS(KICAU(*l,IDKicau-1).utas), user, content);

        do{
            printf("Apakah Anda ingin melanjutkan utas ini? (YA/TIDAK) ");
            readString(); printf("\n");
            if(!isWordEqual(string, "YA") && !isWordEqual(string, "TIDAK")) {
                printf("Input Anda tidak valid. Masukkan lagi yuk!\n\n");
            }
        } while(!isWordEqual(string, "YA") && !isWordEqual(string, "TIDAK"));

        // Pilihan YA, terus lanjutkan utas
        while(isWordEqual(string, "YA")) {
            index = length(KICAU(*l,IDKicau-1).utas);
            insertUtas(l,user,IDUTAS(KICAU(*l,IDKicau-1).utas), index);
            do{
                printf("Apakah Anda ingin melanjutkan utas ini? (YA/TIDAK) ");
                readString(); printf("\n");
                if(!isWordEqual(string, "YA") && !isWordEqual(string, "TIDAK")) {
                    printf("Input Anda tidak valid. Masukkan lagi yuk!\n\n");
                }
            } while(!isWordEqual(string, "YA") && !isWordEqual(string, "TIDAK"));
        }
        printf("Utas selesai!\n\n");
    }
}

void cetakUtas(ListKicau l, int IDUtas)
/* Mencetak seluruh kicauan dalam utas dengan id = IDUtas */
{
    int IDKicau = getIDKicau(l, IDUtas);
    printf("idkicau: %d\n",IDKicau);
    Address p;
    p = FIRSTUTAS(KICAU(l,IDKicau).utas);

    if(isEmpty(KICAU(l,IDKicau).utas)) {
        printf("Maaf, belum ada utas untuk ditampilkan.");
    }
    else {
        // Cetak kicauan (utas utama)
        displayKicau(KICAU(l,IDKicau)); printf("\n");

        // Cetak seluruh utas
        int index = 1;
        while((p) != NULL) {
            printf("   | INDEX = %d\n",index);
            printf("   | "); displayString(USERNAME(AUTHORUTAS(p)));
            printf("   | "); displayDATETIME(DATETIMEUTAS(p)); 
            printf("   | "); displayString(CONTENT(p));printf("\n");

            index++;
            p = NEXT(p);
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