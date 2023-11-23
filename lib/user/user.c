#include "user.h"
#include <stdio.h>
#include <stdlib.h>

STRING listWeton[5];
boolean notWasCreated = true;
STRING Accept;
STRING Reject;
boolean acceptNotInitialized = true;
ListUser UserList;

void createUSER(USER *user)
/*Melakukan inisialisasi awal user
I.S :   user sembarang
F.S :   user.username didefinisikan kosong 
        user.password didefinisikan kosong 
        user.bio didefinisikan kosong 
        user.noHP didefinisikan kosong 
        user.weton didefinisikan kosong 
        user.photo didefinisikan kosong */
{   PhotoElemen p = {'*', 'R'};
    createEmptyString(&USERNAME(*user));
    createEmptyString(&PASSWORD(*user));
    createEmptyString(&BIO(*user));
    createEmptyString(&NOHP(*user));
    createEmptyString(&WETON(*user));
    PHOTO(*user).length = 5;
    for (int i = 0; i < 5; i++){
        for (int j = 0; j < 5; j++){
            PhotoElmt(PHOTO(*user),i,j) = p;
        }
    }
    createListRequest(&REQUESTLIST(*user));
    ACCOUNTTYPE(*user) = true;
}

void createListUser()
/*Melakukan inisialisasi ListUser l
I.S :   l sembarang
F.S :   dibuat sebuah ListUser kosong l, l.length = 0
        semua elemen l dilakukan createUser*/
{   
    for (int i = 0; i < 20; i++){
        createUSER(&USER(UserList,i));
    }
    LENGTH(UserList) = 0;
}

void daftarUSER()
/*Melakukan prosedur DAFTAR untuk pengguna baru
I.S :   user sembarang
F.S :   melakukan procedure DAFTAR seperti spek 
        hanya meminta input untuk username dan password
        panjang maks password dan username sama, yaitu 20
        mengecek apakah username sudah terdaftar sebelumnya atau tidak
        jika sudah terdaftar akan dilakukan input ulang*/
{   
    if (LENGTH(UserList) < 20){
        do {
            printf("\nMasukkan nama:\n");
            readUsername();
            printf("\n");
            if (!VALID){
                printf("Wah, username masukan tidak sesuai! Masukkan username lain yang sesuai.\n");
            } else if (searchUser(string) != NOT_FOUND){
                printf("Wah, sayang sekali nama tersebut telah diambil.\n");
            }
        } while (!VALID || searchUser(string) != NOT_FOUND);
        copyString(&USERNAME(USER(UserList,LENGTH(UserList))), string);
        do {
            printf("Masukkan kata sandi:\n");
            readPassword();
            printf("\n");
            if (!VALID){
                printf("Wah, password tidak sesuai.\n");
            }
        } while (!VALID);
        copyString(&PASSWORD(USER(UserList, LENGTH(UserList))), string);
        printf("Pengguna telah berhasil terdaftar. Masuk untuk menikmati fitur-fitur BurBir.\n\n");
        LENGTH(UserList)++;
        RelationLength(RelMatrix)++;
    } else {
        printf("\nWaduh, Gan, jumlah User sudah maksimal.\n\n");
    }

}

int searchUser(STRING username)
/*Mengembalikan indeks ditemukannya user di dalam l, jika
user tidak ditemukan maka mengembalikan NOT_FOUND*/
{
    for (int i = 0; i < LENGTH(UserList); i++){
        if (isStringEqual(USERNAME(USER(UserList,i)),username)){
            return i;
        }
    }
    return NOT_FOUND;
}

void printPhoto(USER user)
/*Menampilkan foto profil dari user
I.S :   user terdefinisi
F.S :   foto profil user ditampilkan ke layar*/
{   
    for (int i = 0; i < Length(PHOTO(user)); i++){
        for (int j = 0; j < Length(PHOTO(user)); j++){
            if (ColorPhoto(PhotoElmt(PHOTO(user),i,j)) == 'R'){
                print_red(InfoPhoto(PhotoElmt(PHOTO(user),i,j)));
            } else if (ColorPhoto(PhotoElmt(PHOTO(user),i,j)) == 'G') {
                print_green(InfoPhoto(PhotoElmt(PHOTO(user),i,j)));
            } else {
                print_blue(InfoPhoto(PhotoElmt(PHOTO(user),i,j)));
            }
        }
        printf("\n");
    }
    printf("\n");
}

void displayUser(USER user)
/*Menampilkan profil user ke dalam
I.S :   user terdefinisi
F.S :   data umum user ditampilkan ke layar*/
{
    //printf("\n");
    printf("\n| Nama: ");
    displayString(USERNAME(user));
    printf("| Bio Akun: ");
    displayString(BIO(user));
    printf("| No HP: ");
    displayString(NOHP(user));
    printf("| Weton: ");
    displayString(WETON(user));
    printf("\n");
}

void displayDataUser(USER user)
/*Menampilkan profil user ke dalam
I.S :   user terdefinisi
F.S :   seluruh data user, kecuali password dan jenis akun ditampilkan ke layar*/
{
    displayUser(user);
    printf("Foto profil: \n");
    printPhoto(user);
}

void gantiProfil(USER *user)
/*Melakukan prosedur ganti profil sesuai spesifikasi
I.S :   User terdefinisi
F.S :   profil user diganti dengan yang baru
        jika tidak diganti user hanya menginput ; (MARK)*/
{
    if (notWasCreated || listWeton[0].length == 0){
        notWasCreated = false;
        createString(&listWeton[0], "Pahing");
        createString(&listWeton[1], "Kliwon");
        createString(&listWeton[2], "Wage");
        createString(&listWeton[3], "Pon");
        createString(&listWeton[4], "Legi");
    }
    displayUser(*user);
    printf("Masukkan Bio Akun:\n");
    readBio();
    if (string.length != 0){
        copyString(&user->bio, string);
    }
    printf("\n");
    do{
        printf("Masukkan No HP:\n");
        readString();
        printf("\n");
        if (!isNoHPValid(string)){
            printf("No HP tidak valid. Masukkan lagi yuk!\n\n");
        }
    } while (!isNoHPValid(string));
    if (string.length != 0){
        copyString(&user->noHP, string);
    }
    boolean wetonValid = false;
    int i;
    do{
        printf("Masukkan Weton:\n");
        readString();
        printf("\n");
        i = 0;
        while (! wetonValid && i < 5){
            if (isStringSimiliar(listWeton[i], string) || string.length==0){
                wetonValid = true;
            }
            i++;
        }
        if (!wetonValid){
            printf("Weton Anda tidak valid.\n\n");
        }
    } while (!wetonValid && string.length != 0);
    if (string.length != 0){
        copyString(&user->weton, listWeton[i-1]);
    }
    printf("Profil Anda sudah berhasil diperbarui!\n\n");
}

void aturJenisAkun(USER *user)
/*Melakukan procedure perngubahan jenis akun
I.S :   user terdefinisi
F.S :   jenis akun user diubah sesuai dengan pilihan user*/
{
    if (acceptNotInitialized){
        acceptNotInitialized = false;
        createString(&Accept, "YA");
        createString(&Reject, "TIDAK");
    }
    printf("\nSaat ini, akun Anda adalah akun %s. Ingin mengubah ke akun %s?\n", ACCOUNTTYPE(*user) ? "Publik" : "Privat", ACCOUNTTYPE(*user) ? "Privat" : "Publik");
    do {
        printf("(YA/TIDAK) ");
        readString();
        printf("\n");
        if (!isStringSimiliar(Accept,string) && !isStringSimiliar(Reject,string)){
            printf("\nInput Anda tidak valid. Masukkan lagi yuk!\n");
        }
    } while (!isStringSimiliar(Accept,string) && !isStringSimiliar(Reject,string));
    if (isStringSimiliar(Accept, string)){
        ACCOUNTTYPE(*user) = !ACCOUNTTYPE(*user);
        printf("Akun Anda sudah diubah menjadi akun %s.\n\n", ACCOUNTTYPE(*user) ? "Publik" : "Privat");
    } else {
        printf("Perubahan jenis akun Anda dibatalkan.\n\n");
    }
}

void ubahFotoProfil(USER *user)
/*Melakukan procedure pengubahan foto profil
I.S :   user terdefinisi
F.S :   foto profil user digantikan dengan foto profil baru*/
{
    printf("\nFoto profil Anda saat ini adalah:\n");
    printPhoto(*user);
    do {
        printf("Masukkan foto profil yang baru:\n");
        readPhoto();
        printf("\n");
        if (!VALID){
            printf("\nWah, foto profil yang Anda input tidak valid. Masukkan yang valid ya!\n");
        }
    } while (!VALID);
    char currInfo;
    char currColor;
    int count = 0;
    for (int i = 0; i < string.length; i++){
        if (i%4 == 0){
            currColor = string.buffer[i];
        } else if ((i-2)%4 == 0) {
            currInfo = string.buffer[i];
            PhotoElemen p = {currInfo,currColor};
            PhotoElmt(PHOTO(*user),count/5,count%5) = p;
            count++;
        }
    }
    printf("Foto profil Anda sudah berhasil diganti!\n\n");
}

int userID(USER user){
    for (int i = 0 ; i < LENGTH(UserList); i++){
        if (isStringEqual(USERNAME(USER(UserList,i)), USERNAME(user))){
            return i;
        }
    }
    return NOT_FOUND;
}

void daftarTeman(int currentID)
{
    int count = 0;
    STRING listFriend[20];
    for (int i = 0; i < LENGTH(UserList); i++){
        if (i != currentID && isFriend(currentID,i)){
            copyString(&listFriend[count], USERNAME(USER(UserList,i)));
            count++;
        }
    }
    if (!count) {
        printf("\n");
        displayStringNoNewline(USERNAME(USER(UserList,currentID)));
        printf(" belum memiliki teman.\n\n");
    } else {
        printf("\n");
        displayStringNoNewline(USERNAME(USER(UserList,currentID)));
        printf(" memiliki %d teman\nDaftar teman ", count);
        displayStringNoNewline(USERNAME(USER(UserList,currentID)));
        printf("\n\n");
        for (int i = 0; i < count; i++){
            printf("| ");
            displayString(listFriend[i]);
        }
        printf("\n");
    }
}
void hapusTeman(int currentID)
{
    if (acceptNotInitialized){
        acceptNotInitialized = false;
        createString(&Accept, "YA");
        createString(&Reject, "TIDAK");
    }
    printf("\nMasukkan nama pengguna:\n");
    readUsername();
    printf("\n");
    int idFound = searchUser(string);
    if (idFound == NOT_FOUND){
        printf("\nPengguna dengan nama ");
        displayStringNoNewline(string);
        printf(" tidak ditemukan.\n\n");
    } else if (idFound == currentID) {
        printf("\nWah, Anda sangat lucu, nama ini adalah nama Anda sendiri.\n\n");
    }else {
        if(!isFriend(currentID, idFound)){
            printf("\n");
            displayStringNoNewline(string);
            printf(" bukan teman Anda.\n\n");
        } else {
            printf("\nApakah Anda yakin ingin menghapus ");
            displayStringNoNewline(string);
            printf(" dari daftar teman Anda?\n");
            STRING targetName;
            copyString(&targetName, string);
            do {
                printf("(YA/TIDAK) ");
                readString();
                printf("\n");
                if (!isStringSimiliar(Accept,string) && !isStringSimiliar(Reject,string)){
                    printf("\nInput Anda tidak valid. Masukkan lagi yuk!\n");
                }
            } while (!isStringSimiliar(Accept,string) && !isStringSimiliar(Reject,string));
            if (isStringSimiliar(Accept,string)){
                RelationVal(RelMatrix,idFound,currentID) = 0;
                RelationVal(RelMatrix,currentID,idFound) = 0;
                printf("\n");
                displayStringNoNewline(targetName);
                printf(" berhasil dihapus dari daftar teman Anda.\n\n");
            } else {
                printf("Penghapusan teman dibatalkan.\n\n");
            }
        }
    }
}
void tambahTeman(int currentID)
{
    if (!isEmptyListRequest(REQUESTLIST(USER(UserList,currentID)))){
        printf("\nTerdapat permintaan pertemanan yang belum Anda setujui. Silahkan kosongkan daftar permintaan pertemanan untuk Anda terlebih dahulu.\n\n");
    } else {
        printf("\nMasukkan nama pengguna:\n");
        readUsername();
        printf("\n");
        int idFound = searchUser(string);
        if (idFound == NOT_FOUND){
            printf("\nPengguna dengan nama ");
            displayStringNoNewline(string);
            printf(" tidak ditemukan.\n\n");
        } else if (idFound == currentID) {
            printf("\nWah, Anda sangat lucu, nama ini adalah nama Anda sendiri.\n\n");
        }else {
            if (isFriend(currentID, idFound)){
                printf("\nAnda sudah berteman dengan ");
                displayStringNoNewline(string);
                printf(".\n\n");
            } else if (isRequestedFriend(currentID, idFound)){
                printf("Wah, Anda sudah mengirim permintaan pertemanan ke ");
                displayStringNoNewline(string);
                printf(" sebelumnya. Silahkan tunggu hingga permintaan Anda disetujui.\n\n");
            } else {
                int jumlahTeman = countFriend(currentID);
                UserPopularity val = {currentID, jumlahTeman};
                enqueueListRequest(&REQUESTLIST(USER(UserList,idFound)), val);
                RelationVal(RelMatrix, currentID, idFound) = true;
                printf("Anda sudah mengirimkan permintaan pertemanan kepada ");
                displayStringNoNewline(string);
                printf(". Silakan tunggu hingga permintaan Anda disetujui.\n\n");
            }
        }
    }
}
void batalTambahTeman(int currentID)
{
    printf("\nMasukkan nama pengguna:\n");
    readUsername();
    printf("\n");
    int idFound = searchUser(string);
    if (idFound == NOT_FOUND){
        printf("\nPengguna dengan nama ");
        displayStringNoNewline(string);
        printf(" tidak ditemukan.\n\n");
    } else if (idFound == currentID) {
        printf("\nWah, Anda sangat lucu, nama ini adalah nama Anda sendiri.\n\n");
    } else {
        if (!isRequestedFriend(currentID, idFound)){
            printf("\nAnda belum mengirimkan permintaan pertemanan ke ");
            displayStringNoNewline(string);
            printf(".\n\n");
        } else {
            UserPopularity listReq[20];
            int count = 0;
            while (IDHead(REQUESTLIST(USER(UserList,idFound)))!=currentID && !isEmptyListRequest(REQUESTLIST(USER(UserList,idFound)))){
                dequeueListRequest(&REQUESTLIST(USER(UserList,idFound)), &listReq[count]);
                count ++;
            }
            dequeueListRequest(&REQUESTLIST(USER(UserList,idFound)), &listReq[count]);
            for (int i = 0; i < count ; i++){
                enqueueListRequest(&REQUESTLIST(USER(UserList,idFound)), listReq[i]);
            }
            RelationVal(RelMatrix, currentID, idFound) = false;
            printf("\nPermintaan pertemanan kepada ");
            displayStringNoNewline(string);
            printf(" telah dibatalkan.\n\n");
        }
    }
}
void daftarPermintaanTeman(int currentID)
{
    if (!CountLRF(REQUESTLIST(USER(UserList,currentID)))){
        printf("\nTidak ada permintaan pertemanan untuk Anda.\n\n");
    } else {
        int count = CountLRF(REQUESTLIST(USER(UserList,currentID))); 
        UserPopularity tempCont[count];
        printf("\nTerdapat %d permintaan pertemanan untuk Anda.\n\n", count);
        for (int i = 0; i < count; i++){
            UserPopularity temp;
            dequeueListRequest(&REQUESTLIST(USER(UserList,currentID)), &temp);
            tempCont[i] = temp;
            printf("| ");
            displayString(USERNAME(USER(UserList,temp.id)));
            printf("| Jumlah teman: %d\n\n", temp.friendCount);
        }
        for (int i = 0; i < count ; i ++){
            enqueueListRequest(&REQUESTLIST(USER(UserList, currentID)), tempCont[i]);
        }
    }
}
void acceptPertemanan(int currentID)
{
    if (acceptNotInitialized){
        acceptNotInitialized = false;
        createString(&Accept, "YA");
        createString(&Reject, "TIDAK");
    }
    if (isEmptyListRequest(REQUESTLIST(USER(UserList, currentID)))){
        printf("\nPermintaan pertemanan untuk Anda kosong.\n\n");
    } else {
        UserPopularity out;
        dequeueListRequest(&REQUESTLIST(USER(UserList, currentID)), &out);
        printf("\nPermintaan pertemanan teratas dari ");
        displayStringNoNewline(USERNAME(USER(UserList, out.id)));
        printf("\n\n");
        printf("| ");
        displayString(USERNAME(USER(UserList, out.id)));
        printf("| Jumlah teman: %d\n\n", out.friendCount);
        printf("Apakah Anda ingin menyetujui permintaan pertemanan ini?");
        STRING name;
        copyString(&name, USERNAME(USER(UserList, out.id)));
        do {
            printf("(YA/TIDAK) ");
            readString();
            printf("\n");
            if (!isStringSimiliar(Accept,string) && !isStringSimiliar(Reject,string)){
                printf("\nInput Anda tidak valid. Masukkan lagi yuk!\n");
            }
        } while (!isStringSimiliar(Accept,string) && !isStringSimiliar(Reject,string));
        if (isStringSimiliar(Accept,string)){
            RelationVal(RelMatrix, currentID, out.id) = true;
            printf("Permintaan pertemanan dari ");
            displayStringNoNewline(name);
            printf(" telah disetujui. Selamat! Anda telah berteman dengan ");
            displayStringNoNewline(name);
            printf(".\n\n");
        } else {
            printf("Permintaan pertemanan dari ");
            displayStringNoNewline(name);
            printf(" telah ditolak.\n\n");
            RelationVal(RelMatrix, out.id, currentID) = false;
        }
    }
}

void LIHAT_PROFIL(int currentID)
{
    int id2 = searchUser(leftInfo);
    if (id2 == NOT_FOUND){
        printf("\nWalawe, tidak ada pengguna dengan nama tersebut!\n\n");
        return;
    }
    boolean canLook = ACCOUNTTYPE(USER(UserList, id2)) || isFriend(currentID, id2);
    if (!canLook){
        printf("\nWah, akun ");
        displayStringNoNewline(leftInfo);
        printf(" diprivat nih. Ikuti dulu yuk untuk bisa melihat profil ");
        displayStringNoNewline(leftInfo);
        printf("!\n\n");
        return;
    }
    displayDataUser(USER(UserList, id2));
}