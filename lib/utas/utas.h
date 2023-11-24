#ifndef utas_h
#define utas_h

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

Address getLast(UtasList l);

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

int searchIndexUtas(UtasList l, int index);
/* Mengembalikan index sebuah Utas di dalam UtasList l. Mengembalikan NOT_FOUND jika tidak ditemukan */


#endif