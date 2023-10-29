#include "user.h"
#include <stdio.h>
#include <stdlib.h>
#include "user.h"
void createUSER(USER *user)
/*Melakukan inisialisasi awal user
I.S :   user sembarang
F.S :   user.username didefinisikan kosong 
        user.password didefinisikan kosong 
        user.bio didefinisikan kosong 
        user.noHP didefinisikan kosong 
        user.weton didefinisikan kosong 
        user.photo didefinisikan kosong */
{   
    createEmptyString(&USERNAME(*user));
    createEmptyString(&PASSWORD(*user));
    createEmptyString(&BIO(*user));
    createEmptyString(&NOHP(*user));
    createEmptyString(&WETON(*user));
    createString(&PHOTO(*user),DEFAULT_PHOTO);
    ACCOUNTTYPE(*user) = true;
}

void createListUser(ListUser *l)
/*Melakukan inisialisasi ListUser l
I.S :   l sembarang
F.S :   dibuat sebuah ListUser kosong l, l.length = 0
        semua elemen l dilakukan createUser*/
{   
    for (int i = 0; i < 20; i++){
        createUSER(&USER(*l,i));
    }
    LENGTH(*l) = 0;
}

void daftarUSER(ListUser *l)
/*Melakukan prosedur DAFTAR untuk pengguna baru
I.S :   user sembarang
F.S :   melakukan procedure DAFTAR seperti spek 
        hanya meminta input untuk username dan password
        panjang maks password dan username sama, yaitu 20
        mengecek apakah username sudah terdaftar sebelumnya atau tidak
        jika sudah terdaftar akan dilakukan input ulang*/
{   
    if (LENGTH(*l) < 20){
        do {
            printf("Masukkan nama:\n");
            readUsername();
            printf("\n");
            if (!VALID){
                printf("Wah, username masukan tidak sesuai! Masukkan username lain yang sesuai.\n\n");
            } else if (searchUser(*l, string) != NOT_FOUND){
                printf("Wah, sayang sekali nama tersebut telah diambil.\n\n");
            }
        } while (!VALID || searchUser(*l, string) != NOT_FOUND);
        copyString(&USERNAME(USER(*l,LENGTH(*l))), string);
        do {
            printf("Masukkan kata sandi:\n");
            readPassword();
            printf("\n");
            if (!VALID){
                printf("Wah, password tidak sesuai.\n\n");
            }
        } while (!VALID);
        copyString(&PASSWORD(USER(*l, LENGTH(*l))), string);
        printf("\nPengguna telah berhasil terdaftar. Masuk untuk menikmati fitur-fitur BurBir.\n\n");
        LENGTH(*l)++;
    } else {
        printf("Waduh, Gan, jumlah User sudah maksimal.\n\n");
    }

}

int searchUser(ListUser l, STRING username)
/*Mengembalikan indeks ditemukannya user di dalam l, jika
user tidak ditemukan maka mengembalikan NOT_FOUND*/
{
    for (int i = 0; i < LENGTH(l); i++){
        if (isStringEqual(USERNAME(USER(l,i)),username)){
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
    for (int i = 0; i < PHOTO(user).length; i++){
        if ((i-2)%4 == 0 && (i+1)%20 != 0){
            if (PHOTO(user).buffer[i-2] == 'R'){
                print_red(PHOTO(user).buffer[i]);
            } else if (PHOTO(user).buffer[i-2] == 'G'){
                print_green(PHOTO(user).buffer[i]);
            } else{
                print_blue(PHOTO(user).buffer[i]);
            }
        } else if ((i+1)%20 == 0){
            printf("\n");
        }
    }
    printf("\n\n");
}

void displayUser(USER user)
/*Menampilkan profil user ke dalam
I.S :   user terdefinisi
F.S :   data umum user ditampilkan ke layar*/
{
    //printf("\n");
    printf("| Nama: ");
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