#ifndef utas_h
#define utas_h

// #include "../kicauan/kicauan.h"
#include "../user/user.h"
#include "../datetime/datetime.h"
#include "../user/user.h"
#include "../wordmachine/wordmachine.h"
#include "../boolean/boolean.h"

#define ID_UNDEF -1

/* Definisi Node : */
typedef int ElType;
typedef struct utas* Address;
typedef struct utas {
    USER user;
    STRING content;
    DATETIME datetime;
    Address next;
} Utas;

#define AUTHORUTAS(p) (p)->user
#define CONTENT(p) (p)->content
#define DATETIMEUTAS(p) (p)->datetime
#define NEXT(p) (p)->next

Address newNode (int IDUtas, USER user, STRING content);

/* Definisi List : */
/* List kosong : FIRST(l) = NULL */
/* Setiap elemen dengan Address p dapat diacu IDUTAS(p), AUTHOR(p), CONTENT(p), DATETIME(p) dan NEXT(p) */
/* Elemen terakhir list: jika addressnya Last, maka NEXT(Last)=NULL */

typedef struct {
    int IDUtas;
    Address ListUtas;
} UtasList;

#define IDUTAS(p) (p).IDUtas
#define FIRSTUTAS(l) (l).ListUtas


/* PROTOTYPE */
/****************** PEMBUATAN LIST KOSONG ******************/
void CreateListUtas(UtasList *l);
/* I.S. sembarang             */
/* F.S. Terbentuk list kosong */

boolean isEmpty(UtasList l);
/* Mengirim true jika Utas kosong */

int indexOf(UtasList l, ElType val); //#### belum ganti
/* I.S. l, val terdefinisi */
/* F.S. Mencari apakah ada elemen list l yang bernilai val */
/* Jika ada, mengembalikan indeks elemen pertama l yang bernilai val */
/* Mengembalikan IDX_UNDEF jika tidak ditemukan */

/*** PENAMBAHAN ELEMEN ***/
void insertFirst(UtasList *l, int IDUtas, USER user, STRING content);
/* I.S. l mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen pertama dengan nilai val jika alokasi berhasil. */
/* Jika alokasi gagal: I.S.= F.S. */

void insertLast(UtasList *l, int IDUtas, USER user, STRING content);
/* I.S. l mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen list di akhir: elemen terakhir yang baru */
/* bernilai val jika alokasi berhasil. Jika alokasi gagal: I.S.= F.S. */

void insertAt(UtasList *l, int IDUtas, int index, USER user, STRING content);
/* I.S. l tidak mungkin kosong, idx indeks yang valid dalam l, yaitu 0..length(l) */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menyisipkan elemen dalam list pada indeks ke-idx (bukan menimpa elemen di i) */
/* yang bernilai val jika alokasi berhasil. Jika alokasi gagal: I.S.= F.S. */

/*** PENGHAPUSAN ELEMEN ***/
void deleteFirst(UtasList *l);
/* I.S. List l tidak kosong  */
/* F.S. Elemen pertama list dihapus: nilai info disimpan pada x */
/*      dan alamat elemen pertama di-dealokasi */

void deleteAt(UtasList *l, int index);
/* I.S. list tidak kosong, idx indeks yang valid dalam l, yaitu 0..length(l) */
/* F.S. val diset dengan elemen l pada indeks ke-idx. */
/*      Elemen l pada indeks ke-idx dihapus dari l */


/****************** PROSES SEMUA ELEMEN LISTUTAS ******************/

int length(UtasList l);
/* Mengirimkan banyaknya elemen list; mengirimkan 0 jika list kosong */

// void tulisUtas(UtasList *l, USER user, int IDKicau);
// /* Membuat utas baru dari kicauan utama. Utas dapat dilanjutkan 
// I.S :   IDKicau, mungkin bukan milik pengguna saat ini
// F.S :   IDUtas terbentuk, index Utas terbentuk, terisi kicauan baru, length ListUtas bertambah */

int searchIndexUtas(UtasList l, int index);
/* Mengembalikan index sebuah Utas di dalam UtasList l. Mengembalikan NOT_FOUND jika tidak ditemukan */

void sambungUtas(UtasList *l, int IDUtas, int index);
/* Melakukan sambung utas, menambah utas di posisi index yang dituju dari sebuah utas utama.
I.S :   IDUtas, mungkin bukan milik pengguna saat ini
F.S :   terisi kicauan baru, index Utas bertambah */

void hapusUtas(UtasList *l, int IDUtas, int index);
/* Menghapus utas sesuai posisi index, tidak dapat menghapus index 0 (ID kicauan utama) 
I.S :   IDUtas, mungkin bukan milik pengguna saat ini
F.S :   Utas pada index terhapus, index Utas berkurang?*/

void cetakUtas(UtasList l, int IDUtas);
/* Mencetak seluruh kicauan dalam utas dengan id = IDUtas */

#endif
