#ifndef utas_h
#define utas_h

#include "../wordmachine/wordmachine.h"
#include "../boolean/boolean.h"

#define NOT_FOUND -1

typedef struct{
    int IDKicau;
    int IDUtas;
    // int index; //atau Tab[anu]?
    STRING author;
    STRING kicauan;   //menyimpan isi utas
    // datetime
    // account type?

} Utas;
typedef struct{
    int IDKicau;
    int IDUtas;
    // int index; //atau Tab[anu]?
    STRING author;
    STRING kicauan;   //menyimpan isi utas
    // datetime
    // account type?

} Utas;

/* Selektor */
#define IDKICAU(u) (u).IDKicau
#define IDUTAS(u) (u).IDUtas
#define AUTHOR(u) (u).author
#define KICAUAN(u) (u).kicauan
// #define DATETIME(u) (u).datetime


typedef struct{
    ListSambungUtas Tab[280];  //menyimpan info ListSambungUtas (berapa enaknya ya?)
    int length;     //meyimpan banyak utas
} ListUtas;

typedef struct{
    Utas Tab[280];  //menyimpan info Utas
} ListSambungUtas;

#define LENGTH(l) (l).length
#define Utas(l,i) (l).Tab[i]    //akses di index utas utama (kicauan utama)

void createUtas();

void createListUtas();
/* Inisialisasi ListUtas l untuk menyimpan seluruh utas
I.S :   l sembarang
F.S :   terbentuk ListUtas kosong l (l.length = 0) */

void tulisUtas();
/* Membuat utas baru dari kicauan utama. Utas dapat dilanjutkan 
I.S :   IDKicau, mungkin bukan milik pengguna saat ini
F.S :   IDUtas terbentuk, index Utas terbentuk, terisi kicauan baru, length ListUtas bertambah */

int searchUtas(ListUtas l);
/* Mengembalikan index sebuah Utas di dalam ListUtas l. Mengembalikan NOT_FOUND jika tidak ditemukan */

void sambungUtas();
/* Melakukan sambung utas, menambah utas di posisi index yang dituju dari sebuah utas utama.
I.S :   IDUtas, mungkin bukan milik pengguna saat ini
F.S :   terisi kicauan baru, index Utas bertambah */

void hapusUtas();
/* Menghapus utas sesuai posisi index, tidak dapat menghapus index 0 (ID kicauan utama) 
I.S :   IDUtas, mungkin bukan milik pengguna saat ini
F.S :   Utas pada index terhapus, index Utas berkurang?*/

void cetakUtas();
/* Mencetak seluruh kicauan dalam utas dengan id = IDUtas */


#endif