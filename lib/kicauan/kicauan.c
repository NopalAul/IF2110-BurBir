#include "kicauan.h"
#include <stdlib.h>
#include <stdio.h>

void createListKicau(ListKicau *l, int capacity){
    BUFFER(*l) =  (KICAU*) malloc(sizeof(KICAU) * capacity);
    NEFFLISTKICAU(*l) = 0;

    CAPACITY(*l) = capacity;
    
}

void createKicau(ListKicau *l, USER user, STRING text){
    if (isKicauanFull(*l)){
        expandKicauan(l, CAPACITY(*l));
    }
    int idxNow = NEFFLISTKICAU(*l);
    IDKICAUAN(KICAU(*l, idxNow)) = idxNow+1;
    AUTHOR(KICAU(*l, idxNow)) = user;
    copyString(&TEXTKICAUAN(KICAU(*l, idxNow)), text);
    LIKE(KICAU(*l, idxNow)) = 0;
    DATETIME(KICAU(*l, idxNow)) = getCurrentDATETIME();
    CreateREPLY(&BALASAN(KICAU(*l, idxNow)));
    CreateListUtas(&UTAS(KICAU(*l, idxNow)));
    NEXTREPLYID(KICAU(*l, idxNow)) = 1;
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

/*

===============================================================
BALASAN
===============================================================
*/

void BALAS(ListKicau *lk, int currentID)
{
    if (!isStringNumeric(leftInfo) || !isStringNumeric(rightInfo)){
        printf("Command yang Anda masukkan tidak sesuai!\n\n");
        return;
    }
    int idKicau = stringToInteger(leftInfo);
    if (idKicau > (*lk).nEFF || idKicau <= 0){
        printf("Wah, tidak terdapat kicauan dengan id tersebut!\n\n");
        return;
    }
    int idReply = stringToInteger(rightInfo);
    STRING author;;
    createEmptyString(&author);
    if (idReply == -1) copyString(&author, USERNAME(AUTHOR(KICAU(*lk, idKicau-1))));
    else ReplyAuhtor(BALASAN(KICAU(*lk,idKicau-1)), idReply, &author);
    if (author.length == 0){
        printf("Wah, tidak terdapat balasan yang ingin Anda balas!\n\n");
        return;
    }
    if (!isFriend(currentID, searchUser(author))){
        printf("Wah, Anda tidak bisa membalas kicauan atau balasan dari akun privat yang bukan teman Anda!\n\n");
        return;
    }
    printf("\nMasukkan balasan:\n");
    readString();
    AddressReply p = newReply(NEXTREPLYID(KICAU(*lk,idKicau-1)), string, USERNAME(USER(UserList, currentID)), getCurrentDATETIME());
    if (p == NULL){
        printf("Error: Gagal membuat balasan.\n\n");
        return;
    }
    boolean succeed = false;
    addREPLY(&BALASAN(KICAU(*lk,idKicau-1)), idReply, p, &succeed);
    if (!succeed) {
        printf("Error: Gagal menerbitkan balasan.\n\n");
        free(p);
        return;
    } 
    NEXTREPLYID(KICAU(*lk,idKicau-1))++;
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
    if (idKicau <= 0 || idKicau > (*lk).nEFF){
        printf("Wah, tidak terdapat kicauan dengan id tersebut!\n\n");
        return;
    }
    if (isEmptyREPLY(BALASAN(KICAU(*lk, idKicau-1)))){
        printf("Belum terdapat balasan apapun pada kicauan tersebut. Yuk, balas kicauan tersebut!\n\n");
        return;
    }
    printf("\n");
    displayBalasanHandler(BALASAN(KICAU(*lk, idKicau-1)), currentID, 0);
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
    if (idKicau <= 0 || idKicau > (*lk).nEFF){
        printf("Walawe, tidak ada kicauan dengan id tersebut!\n\n");
        return;
    }
    int idReply = stringToInteger(rightInfo);
    STRING author;
    createEmptyString(&author);
    ReplyAuhtor(BALASAN(KICAU(*lk, idKicau-1)), idReply, &author);
    if (author.length == 0){
        printf("Walawe, tidak ada balasan dengan id tersebut.\n\n");
        return;
    }
    if (!isStringEqual(USERNAME(USER(UserList, currentID)), author)){
        printf("Ara-ara, ini balasan punya siapa? Jangan dihapus ya.\n\n");
    }
    boolean succeed = false;
    deleteREPLY(&BALASAN(KICAU(*lk, idKicau-1)), idReply, &succeed, NULL, NULL);
    if (!succeed) {
        printf("Error: Sepertinya ada masalah dalam proses penghapusan.\n\n");
        return;
    }
    printf("Balasan berhasil dihapus.\n\n");
}

/*

=============================================================
UTAS
=============================================================
*/


int getIDKicau(ListKicau l,int IDUtas) {
    int IDKicau;
    for (int i = 0; i < NEFFLISTKICAU(l); i++){
        if (IDUTAS(KICAU(l,i).utas) == IDUtas){
            IDKicau = i;
            break;
        }
    }

    return IDKicau;
}

boolean isIDUtasExist(ListKicau l, int IDUtas) {
    boolean exist = false;
    for (int i = 0; i < NEFFLISTKICAU(l); i++){
        if (IDUTAS(KICAU(l,i).utas) == IDUtas){
            exist = true;
            break;
        }
    }
    return exist;
}

void insertUtas(ListKicau *l, int IDUtas, int index) //PERLU PARAMETER USER?
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
    else if(index > lengthUtas(KICAU(*l,IDKicau).utas)) {
        // Kondisi index terlalu tinggi
        printf("Index terlalu tinggi!\n\n");
    }
    // else if(!isStringEqual(USERNAME(user), USERNAME(AUTHOR(KICAU(*l,IDKicau))))) {
    //     // Kondisi IDUtas bukan milik pengguna saat ini
    //     printf("Anda tidak bisa menyambung utas ini!\n\n");
    // }
    else
        {
            // Kondisi valid
            printf("Masukkan kicauan:\n");
            readKicauan(); copyString(&content, string);
            printf("\n");
            

            insertAt(&KICAU(*l,IDKicau).utas, IDUtas, index, AUTHORUTAS(p), content);
        }
}

void hapusUtas(ListKicau *l, int IDUtas, int index)
{
    /* Menghapus utas sesuai posisi index, tidak dapat menghapus index 0 (ID kicauan utama) 
    I.S :   IDUtas, mungkin bukan milik pengguna saat ini
    F.S :   Utas pada index terhapus, index Utas berkurang?*/

    int IDKicau = getIDKicau(*l,IDUtas);
    if(isIDUtasExist(*l,IDUtas) == false) {
        // Kondisi utas tidak ditemukan
        printf("Utas tidak ditemukan!\n\n");
    }
    // else if(true) {
    //     // Kondisi utas bukan milik pengguna saat ini
    //     printf("Anda tidak bisa menghapus kicauan dalam utas ini!\n\n");
    // }
    else
    {
        // Kondisi utas milik sendiri
        if(index > lengthUtas(KICAU(*l,IDKicau).utas)-1) {
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

void sambungUtas(ListKicau *l, int IDUtas, int index)
{
    insertUtas(l,IDUtas,index-1);
}

void tulisUtas(ListKicau *l, USER user, int IDKicau)
/* Membuat utas baru dari kicauan utama. Utas dapat dilanjutkan 
I.S :   IDKicau, mungkin bukan milik pengguna saat ini
F.S :   IDUtas terbentuk, index Utas terbentuk, terisi kicauan baru, length ListUtas bertambah */
{
    if(IDKicau > NEFFLISTKICAU(*l)) {
        printf("Kicauan tidak ditemukan\n\n");
    }
    else if(!isStringEqual(USERNAME(user), USERNAME(AUTHOR(KICAU(*l,IDKicau-1))))) {
        printf("Utas ini bukan milik anda!\n\n");
    }
    else if(IDUTAS(KICAU(*l,IDKicau-1).utas) != ID_UNDEF){
        printf("ID Kicau ini sudah mempunyai utas!\n\n");
    }
    else {
        // Address p;
        // p = FIRSTUTAS(KICAU(*l,IDKicau-1).utas);
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
        
        insertFirstUtas(&KICAU(*l,IDKicau-1-1).utas, IDUTAS(KICAU(*l,IDKicau-1-1).utas), user, content);
        printf("username:");displayString(USERNAME(user));printf("\n"); //delete

        do{
            printf("Apakah Anda ingin melanjutkan utas ini? (YA/TIDAK) ");
            readString(); printf("\n");
            if(!isWordEqual(string, "YA") && !isWordEqual(string, "TIDAK")) {
                printf("Input Anda tidak valid. Masukkan lagi yuk!\n\n");
            }
        } while(!isWordEqual(string, "YA") && !isWordEqual(string, "TIDAK"));

        // Pilihan YA, terus lanjutkan utas
        while(isWordEqual(string, "YA")) {
            index = lengthUtas(KICAU(*l,IDKicau-1).utas);
            printf("len: %d\n",lengthUtas(KICAU(*l,IDKicau-1).utas)); // delete
            insertUtas(l, IDUTAS(KICAU(*l,IDKicau-1).utas), index);
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
    int IDKicau = getIDKicau(l, IDUtas)+1;
    printf("idkicau: %d\n",IDKicau);
    Address p;
    p = FIRSTUTAS(KICAU(l,IDKicau).utas);

    if(isEmpty(KICAU(l,IDKicau).utas)) {
        printf("Maaf, belum ada utas untuk ditampilkan.");
    }
    else {
        // Cetak kicauan (utas utama)
        displayKicau(KICAU(l,IDKicau-1)); printf("\n");

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


