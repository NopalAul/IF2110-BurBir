#ifndef user_h
#define user_h

#include "../wordmachine/wordmachine.h"
#include "../pcolor/pcolor.h"
#include "../boolean/boolean.h"
#include "../matrix/matrix.h"
#include "../listRequest/listRequest.h"

#define MAX_USER 20
#define NOT_FOUND -1

typedef struct{
    STRING username;    //menyimpan username atau nama user
    STRING password;    //menyimpan password user
    STRING bio;         //menyimpan bio akun user
    STRING noHP;        //menyimpan Nomor HP user
    STRING weton;       //menyimpan jenis weton user
    Photo photo;       //menyimpan photo user
    ListFriendRequest request; //menyimpan permintaan pertemanan ke user
    boolean accountType;//akun public bernilai TRUE, akun privat FALSE  
} USER;

/*Selektor*/
#define USERNAME(U) (U).username
#define PASSWORD(U) (U).password
#define BIO(U) (U).bio
#define NOHP(U) (U).noHP
#define WETON(U) (U).weton
#define PHOTO(U) (U).photo
#define REQUESTLIST(U) (U).request
#define ACCOUNTTYPE(U) (U).accountType

typedef struct{
    USER Tab[MAX_USER]; //menyimpan info USER (modifikasi List dengan array statik)
    int length;         //meyimpan banyak user
} ListUser;

extern ListUser UserList;

#define LENGTH(l) (l).length
#define USER(l,i)  (l).Tab[i]

void createUSER(USER *user);
/*Melakukan inisialisasi awal user
I.S :   user sembarang
F.S :   user.username didefinisikan kosong 
        user.password didefinisikan kosong 
        user.bio didefinisikan kosong  
        user.noHP didefinisikan kosong 
        user.weton didefinisikan kosong 
        user.photo didefinisikan kosong */

void createListUser();
/*Melakukan inisialisasi ListUser l
I.S :   l sembarang
F.S :   dibuat sebuah ListUser kosong l, l.length = 0
        semua elemen l dilakukan createUser*/

void daftarUSER();
/*Melakukan prosedur DAFTAR untuk pengguna baru
I.S :   user sembarang
F.S :   melakukan procedure DAFTAR seperti spek 
        hanya meminta input untuk username dan password
        panjang maks password dan username sama, yaitu 20
        mengecek apakah username sudah terdaftar sebelumnya atau tidak
        jika sudah terdaftar akan dilakukan input ulang*/

int searchUser(STRING username);
/*Mengembalikan indeks ditemukannya user di dalam l, jika
user tidak ditemukan maka mengembalikan NOT_FOUND*/

void printPhoto(USER user);
/*Menampilkan foto profil dari user
I.S :   user terdefinisi
F.S :   foto profil user ditampilkan ke layar*/

void displayUser(USER user);
/*Menampilkan profil user ke dalam
I.S :   user terdefinisi
F.S :   data umum user ditampilkan ke layar*/

void displayDataUser(USER user);
/*Menampilkan profil user ke dalam
I.S :   user terdefinisi
F.S :   seluruh data user, kecuali password dan jenis akun ditampilkan ke layar*/

void gantiProfil(USER *user);
/*Melakukan prosedur ganti profil sesuai spesifikasi
I.S :   User terdefinisi
F.S :   profil user diganti dengan yang baru
        jika tidak diganti user hanya menginput ; (MARK)*/

void aturJenisAkun(USER *user);
/*Melakukan procedure perngubahan jenis akun
I.S :   user terdefinisi
F.S :   jenis akun user diubah sesuai dengan pilihan user*/ 

void ubahFotoProfil(USER *user);
/*Melakukan procedure pengubahan foto profil
I.S :   user terdefinisi
F.S :   foto profil user digantikan dengan foto profil baru*/

int userID(USER user);

void daftarTeman(int currentID);
void hapusTeman(int currentID);
void tambahTeman(int currentID);
void batalTambahTeman(int currentID);
void daftarPermintaanTeman(int currentID);
void acceptPertemanan(int currentID);

#endif