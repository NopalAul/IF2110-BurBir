#include "kicauan.h"
#include <stdlib.h>
#include <stdio.h>

void createListKicau(ListKicau *l, int capacity){
    BUFFER(*l) =  (KICAU*) malloc(sizeof(KICAU) * capacity);
    NEFF(*l) = 0;
    (*l).NextUtasID = 1;
    CAPACITY(*l) = capacity;
}

void createKicau(ListKicau *l, USER user, STRING text){
    if (isKicauanFull(*l)){
        expandKicauan(l, CAPACITY(*l));
    }
    int idxNow = NEFF(*l);
    IDKICAUAN(KICAU(*l, idxNow)) = idxNow+1;
    AUTHOR(KICAU(*l, idxNow)) = user;
    copyString(&TEXTKICAUAN(KICAU(*l, idxNow)), text);
    LIKE(KICAU(*l, idxNow)) = 0;
    DATETIME(KICAU(*l, idxNow)) = getCurrentDATETIME();
    CreateREPLY(&BALASAN(KICAU(*l, idxNow)));
    CreateListUtas(&UTAS(KICAU(*l, idxNow)));
    NEXTREPLYID(KICAU(*l, idxNow)) = 1;
    NEFF(*l)++;
}

void buatKicau(ListKicau *l,USER user){
    do {
        printf("\nMasukkan kicauan:\n");
        readKicauan();
        if (!VALID){
            printf("\nWalawe, kicauan Anda tidak sesuai. Isi kicauan tidak boleh berisi karakter spasi atau newline saja.\n");
        }
    }while (!VALID);
    createKicau(l,user,string);
    printf("\nSelamat! kicauan telah diterbitkan!\n");
    printf("Detil kicauan:\n\n");
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

void addKicauan(ListKicau *l, KICAU *kicau){
    if (isKicauanFull(*l)){
        expandKicauan(l,CAPACITY(*l));
    }
    KICAU(*l, NEFF(*l)) = *kicau;
    NEFF(*l)++;
}

void sukaKicauan(ListKicau *l,int id,USER currUser ){
    int i = 0;
    while (i < NEFF(*l) && IDKICAUAN(KICAU(*l,i)) != id){
        i++;
    }
    if(IDKICAUAN(KICAU(*l,i)) == id){
        if(ACCOUNTTYPE(USER(UserList, searchUser(USERNAME(AUTHOR(KICAU(*l, i)))))) || isFriend(searchUser(USERNAME(currUser)), searchUser(USERNAME(AUTHOR(KICAU(*l, i)))))){
            LIKE(KICAU(*l,i))++;
            printf("\nSelamat! kicauan telah disukai! Detil kicauan:\n\n");
            displayKicau(KICAU(*l,i));
        }
        else{
            printf("\nWah, kicauan tersebut dibuat oleh akun privat! Ikuti akun itu dulu ya\n\n");
        }
    }
    else{
        printf("\nTidak ditemukan kicauan dengan ID %d\n\n",id);
    }
}

void ubahKicauan(ListKicau *l,USER currUser,int id){
    int i = 0;
    while (i < NEFF(*l) && IDKICAUAN(KICAU(*l,i)) != id){
        i++;
    }
    if(IDKICAUAN(KICAU(*l,i)) == id){
        if(isStringEqual(USERNAME(currUser), USERNAME(AUTHOR(KICAU(*l, i))))){
            do {
                printf("\nMasukkan kicauan baru:\n");
                readKicauan();
                if (!VALID) printf("\nWalawe, kicauan Anda tidak sesuai. Isi kicauan tidak boleh berisi karakter spasi atau newline saja.\n\n");
            } while (!VALID);
            copyString(&TEXTKICAUAN(KICAU(*l,i)), string);
            printf("\nSelamat! kicauan telah diterbitkan!\n Detil kicauan:\n");
            displayKicau(KICAU(*l,i));
        }
        else{
            printf("\nKicauan dengan ID = %d bukan milikmu\n",id);
        }
    }
    else{
        printf("\nTidak ditemukan kicauan dengan ID = %d\n",id);
    }
}

void expandKicauan (ListKicau *l,int num){
    CAPACITY(*l) += num;
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
    printf("| Disukai: %d\n\n",LIKE(kicau));

}

void displayKicauan(ListKicau l,USER currUser){
    printf("\n");
    for (int i = 0; i < NEFF(l); i++){
        if(ACCOUNTTYPE(USER(UserList, searchUser(USERNAME(AUTHOR(KICAU(l, i)))))) || isFriend(searchUser(USERNAME(currUser)), searchUser(USERNAME(AUTHOR(KICAU(l, i)))))){
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


void BALAS(ListKicau *lk, int currentID)
{
    if (!isStringNumeric(leftInfo) || !isStringNumeric(rightInfo)){
        printf("\nCommand yang Anda masukkan tidak sesuai!\n\n");
        return;
    }
    int idKicau = stringToInteger(leftInfo);
    if (idKicau > (*lk).nEFF || idKicau <= 0){
        printf("\nWah, tidak terdapat kicauan dengan id tersebut!\n\n");
        return;
    }
    int idReply = stringToInteger(rightInfo);
    STRING author;;
    createEmptyString(&author);
    if (idReply == -1) copyString(&author, USERNAME(AUTHOR(KICAU(*lk, idKicau-1))));
    else ReplyAuhtor(BALASAN(KICAU(*lk,idKicau-1)), idReply, &author);
    if (author.length == 0){
        printf("\nWah, tidak terdapat balasan yang ingin Anda balas!\n\n");
        return;
    }
    if (!isFriend(currentID, searchUser(author)) && !ACCOUNTTYPE(USER(UserList, searchUser(author)))){
        printf("\nWah, Anda tidak bisa membalas kicauan atau balasan dari akun privat yang bukan teman Anda!\n\n");
        return;
    }
    do {
        printf("\nMasukkan balasan:\n");
        readString();
        if (!isInputValid()){
            printf("\nWalawe, balasan tidak valid. Balasan tidak dapat mengandung newline.\n");
        }
    } while (!isInputValid());
    AddressReply p = newReply(NEXTREPLYID(KICAU(*lk,idKicau-1)), string, USERNAME(USER(UserList, currentID)), getCurrentDATETIME());
    if (p == NULL){
        printf("\nError: Gagal membuat balasan.\n\n");
        return;
    }
    boolean succeed = false;
    addREPLY(&BALASAN(KICAU(*lk,idKicau-1)), idReply, p, &succeed);
    if (!succeed) {
        printf("\nError: Gagal menerbitkan balasan.\n\n");
        free(p);
        return;
    } 
    NEXTREPLYID(KICAU(*lk,idKicau-1))++;
    printf("\nSelamat! Balasan telah diterbitkan!\nDetil balasan:\n");
    displaySpecificReply(p, 0, true);
}

void DISPLAYBALASAN(ListKicau *lk, int currentID)
{
    if (!isStringNumeric(leftInfo)){
        printf("\nCommand yang Anda masukkan tidak sesuai!\n\n");
        return;
    }
    int idKicau = stringToInteger(leftInfo);
    if (idKicau <= 0 || idKicau > (*lk).nEFF){
        printf("\nWah, tidak terdapat kicauan dengan id tersebut!\n\n");
        return;
    }
    if (isEmptyREPLY(BALASAN(KICAU(*lk, idKicau-1)))){
        printf("\nBelum terdapat balasan apapun pada kicauan tersebut. Yuk, balas kicauan tersebut!\n\n");
        return;
    }
    if (!ACCOUNTTYPE(USER(UserList,searchUser(USERNAME(AUTHOR(KICAU(*lk,idKicau-1)))))) && !isFriend(currentID, searchUser(USERNAME(AUTHOR(KICAU(*lk,idKicau-1)))))){
        printf("\nWalawe, Kicauan tersebut dibuat oleh akun privat\n\n");
        return;
    }
    printf("\n");
    displayBalasanHandler(BALASAN(KICAU(*lk, idKicau-1)), currentID, 0);
}

void displayBalasanHandler(REPLY r, int currentID, int depth)
{
    if(!isEmptyREPLY(r)){
        boolean noSensor = ACCOUNTTYPE(USER(UserList,searchUser(REPLYAUTHOR(r)))) || isFriend(currentID, searchUser(REPLYAUTHOR(r)));
        displaySpecificReply(r,depth, noSensor);
        displayBalasanHandler(CHILD(r), currentID, depth+1);
        displayBalasanHandler(SIBLING(r), currentID, depth);
    }
}

void HAPUSBALASAN(ListKicau *lk, int currentID)
{
    if (!isStringNumeric(leftInfo) || !isStringNumeric(rightInfo)){
        printf("\nCommand yang Anda masukkan tidak sesuai!\n\n");
        return;
    }
    int idKicau = stringToInteger(leftInfo);
    if (idKicau <= 0 || idKicau > (*lk).nEFF){
        printf("\nWalawe, tidak ada kicauan dengan id tersebut!\n\n");
        return;
    }
    int idReply = stringToInteger(rightInfo);
    STRING author;
    createEmptyString(&author);
    ReplyAuhtor(BALASAN(KICAU(*lk, idKicau-1)), idReply, &author);
    if (author.length == 0){
        printf("\nWalawe, tidak ada balasan dengan id tersebut.\n\n");
        return;
    }
    if (!isStringEqual(USERNAME(USER(UserList, currentID)), author)){
        printf("\nAra-ara, ini balasan punya siapa? Jangan dihapus ya.\n\n");
        return;
    }
    boolean succeed = false;
    deleteREPLY(&BALASAN(KICAU(*lk, idKicau-1)), idReply, &succeed, NULL, NULL);
    if (!succeed) {
        printf("\nError: Sepertinya ada masalah dalam proses penghapusan.\n\n");
        return;
    }
    printf("\nBalasan berhasil dihapus.\n\n");
}




int getIDKicau(ListKicau l,int IDUtas) {
    int IDKicau = NOT_FOUND;
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

void insertUtas(ListKicau *l, int IDUtas, int index,USER currentuser) //PERLU PARAMETER USER?
/* Melakukan sambung utas, menambah utas di posisi index yang dituju dari sebuah utas utama.
I.S :   IDUtas, mungkin bukan milik pengguna saat ini
F.S :   terisi kicauan baru, index Utas bertambah */
{   
    int IDKicau = getIDKicau(*l,IDUtas);
    if (IDKicau == NOT_FOUND){
        printf("\nWalawe, kicauan dengan ID utas tersebut tidak ada.\n\n");
        return;
    }
    if(!isStringEqual(USERNAME(currentuser), USERNAME(AUTHOR(KICAU(*l,IDKicau))))) {
        // Kondisi IDUtas bukan milik pengguna saat ini
        printf("\nAnda tidak bisa menyambung utas ini!\n\n");
        return;
    }
    Address p;
    p = FIRSTUTAS(KICAU(*l,IDKicau).utas);
    STRING content;

    if(isIDUtasExist(*l,IDUtas) == false) {
        // Kondisi tidak ditemukan IDUtas
        printf("\nUtas tidak ditemukan!\n\n");
    }
    else if(index > length(KICAU(*l,IDKicau).utas)) {
        // Kondisi index terlalu tinggi
        printf("\nIndex terlalu tinggi!\n\n");
    }
    else if(!isStringEqual(USERNAME(currentuser), USERNAME(AUTHOR(KICAU(*l,IDKicau))))) {
        // Kondisi IDUtas bukan milik pengguna saat ini
        printf("\nAnda tidak bisa menyambung utas ini!\n\n");
    }
    else
        {
            // Kondisi valid
            do{
                printf("\nMasukkan kicauan:\n");
                readKicauan();
                printf("\n");
                if(!isInputValid()){
                    printf("Input tidak valid. Masukkan lagi yuk!\n");
                }

            }while(!isInputValid());
            
            copyString(&content, string);
            

            insertAt(&KICAU(*l,IDKicau).utas, IDUtas, index, AUTHORUTAS(p), content);
        }
}

void hapusUtas(ListKicau *l, int IDUtas, int index, USER currentuser)
{
    /* Menghapus utas sesuai posisi index, tidak dapat menghapus index 0 (ID kicauan utama) 
    I.S :   IDUtas, mungkin bukan milik pengguna saat ini
    F.S :   Utas pada index terhapus, index Utas berkurang?*/

    int IDKicau = getIDKicau(*l,IDUtas);
    if(isIDUtasExist(*l,IDUtas) == false) {
        // Kondisi utas tidak ditemukan
        printf("\nUtas tidak ditemukan!\n\n");
    }
    else if(!isStringEqual(USERNAME(currentuser), USERNAME(AUTHOR(KICAU(*l,IDKicau))))) {
        // Kondisi IDUtas bukan milik pengguna saat ini
        printf("\nAnda tidak bisa menghapus kicauan dalam utas ini!\n\n");
    }
    else
    {
        // Kondisi utas milik sendiri
        if(index > length(KICAU(*l,IDKicau).utas)) {
            // Kondisi index utas tidak ditemukan
            printf("\nKicauan sambungan dengan index %d tidak ditemukan pada utas!\n\n",index);
        }
        else if(index == 0) {
            // Kondisi index = 0
            printf("\nAnda tidak bisa menghapus kicauan utama!\n\n");
        }
        else {
            // Kondisi valid
            deleteAt(&KICAU(*l,IDKicau).utas,index-1);
            printf("\nKicauan sambungan berhasil dihapus!\n\n");
        }
    }
}

void sambungUtas(ListKicau *l, int IDUtas, int index, USER currentuser)
{
    insertUtas(l,IDUtas,index-1,currentuser);
}

void tulisUtas(ListKicau *l, USER user, int IDKicau)
/* Membuat utas baru dari kicauan utama. Utas dapat dilanjutkan 
I.S :   IDKicau, mungkin bukan milik pengguna saat ini
F.S :   IDUtas terbentuk, index Utas terbentuk, terisi kicauan baru, length ListUtas bertambah */
{
    if(IDKicau > (*l).nEFF) {
        printf("\nKicauan tidak ditemukan\n\n");
    }
    else if(!isStringEqual(USERNAME(user), USERNAME(AUTHOR(KICAU(*l,IDKicau-1))))) {
        printf("\nUtas ini bukan milik anda!\n\n");
    }
    else if(IDUTAS(KICAU(*l,IDKicau-1).utas) != ID_UNDEF){
        printf("\nID Kicau ini sudah mempunyai utas!\n\n");
    }
    else {
        IDUTAS(KICAU(*l,IDKicau-1).utas) = (*l).NextUtasID;
        (*l).NextUtasID++;
        int index;
        STRING content;

        // Kondisi milik pengguna saat ini
        printf("\nUtas berhasil dibuat!\n\n");
        do{
                printf("Masukkan kicauan:\n");
                readKicauan();
                printf("\n");
                if(!isInputValid()){
                    printf("Input tidak valid. Masukkan lagi yuk!\n\n");
                }

            }while(!isInputValid());

        copyString(&content, string); 

        // insertFirst(&KICAU(*l,IDKicau-1-1).utas, IDUTAS(KICAU(*l,IDKicau-1-1).utas), user, content);
        insertFirst(&KICAU(*l,IDKicau-1).utas, IDUTAS(KICAU(*l,IDKicau-1).utas), user, content);

        do{
            printf("Apakah Anda ingin melanjutkan utas ini? (YA/TIDAK) ");
            readString();
            if(!isWordSimiliar(string, "YA") && !isWordSimiliar(string, "TIDAK")) {
                printf("\nInput Anda tidak valid. Masukkan lagi yuk!\n\n");
            }
        } while(!isWordSimiliar(string, "YA") && !isWordSimiliar(string, "TIDAK"));

        // Pilihan YA, terus lanjutkan utas
        while(isWordSimiliar(string, "YA")) {
            index = length(KICAU(*l,IDKicau-1).utas);
            insertUtas(l, IDUTAS(KICAU(*l,IDKicau-1).utas), index, user);
            do{
                printf("Apakah Anda ingin melanjutkan utas ini? (YA/TIDAK) ");
                readString();
                if(!isWordSimiliar(string, "YA") && !isWordSimiliar(string, "TIDAK")) {
                    printf("\nInput Anda tidak valid. Masukkan lagi yuk!\n\n");
                }
            } while(!isWordSimiliar(string, "YA") && !isWordSimiliar(string, "TIDAK"));
        }
        printf("\nUtas selesai!\n\n");
    }
}

void cetakUtas(ListKicau l, int IDUtas, USER user)
/* Mencetak seluruh kicauan dalam utas dengan id = IDUtas */
{
    printf("\n");
    int IDKicau = getIDKicau(l, IDUtas);
    if (IDKicau == NOT_FOUND){
        printf("\nWalawe, utas tidak ditemukan!\n\n");
        return;
    }
    Address p;
    p = FIRSTUTAS(KICAU(l,IDKicau).utas);

    boolean isSeen = ACCOUNTTYPE(USER(UserList,searchUser(USERNAME(AUTHORUTAS(p))))) || isFriend(userID(user),searchUser(USERNAME(AUTHORUTAS(p))));

    if (!isSeen) {
        printf("Akun yang membuat utas ini adalah akun privat! Ikuti dahulu akun ini untuk melihat utasnya!\n\n");
        return;
    }
    else {
        // Cetak kicauan (utas utama)
        displayKicau(KICAU(l,IDKicau));

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