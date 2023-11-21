#ifndef draft_H
#define draft_H
#include <stdio.h>
#include <stdlib.h>
#include "../boolean/boolean.h"
#include "../datetime/datetime.c"
#include "../wordmachine/wordmachine.c"
#include "../charmachine/charmachine.c"

typedef struct
{
    STRING kicau;
    DATETIME dt;
} Draft;

typedef int TopLoc;

typedef struct
{
    Draft *buffer; // struktur array dinamis yang berisi komponen draft; STRING, DATETIME
    TopLoc Top;    // mengembalikan indeks dari TOP
    int capacity;
} StackDraft;

/* Tipe stacknya yaitu top berada di last indeks dari array */

/* SELEKTOR */
#define NIL -1
#define NEFF(d) (d).nEff
#define BUFFER(d) (d).buffer
#define TOP(d) (d).Top
#define INFOTOP(d) (d).buffer[TOP]
#define CAPACITY(d) (d).capacity

void CreateEmptyDraft(StackDraft *d, int capacity);
/* I.S. sembarang; */
/* F.S. Membuat sebuah stack StackDraft d kosong */
/* jadi indeksnya antara 0.. nEff */
/* Ciri stack kosong : TOP bernilai Nil */

boolean IsEmptyDraft(StackDraft d); // harusnya boolean
/* Mengirim true jika Stack kosong: lihat definisi di atas */

boolean IsFullDraft(StackDraft d); // harusnya boolean
/* Mengirim true jika tabel penampung nilai elemen stack penuh */

void PushDraft(StackDraft *d, STRING s);
/* Menambahkan X sebagai elemen Stack S. */
/* I.S. S mungkin kosong, tabel penampung elemen stack mungkin penuh */
/* F.S. X menjadi TOP yang baru,TOP bertambah 1 */

void PopDraft(StackDraft *d, STRING *s);
/* Menghapus X dari Stack S dan menyimpan date pembuatan StackDraft. */
/* I.S. S  tidak mungkin kosong */
/* F.S. X adalah nilai elemen TOP yang lama, TOP berkurang 1 */

void dealocateStack(StackDraft *d);
/* I.S. d terdefinisi; */
/* F.S. (d) dikembalikan ke system, CAPACITY(d)=0;*/

void expandDraft(StackDraft *d, int num);
/* Proses : Menambahkan capacity l sebanyak num */
/* I.S. List sudah terdefinisi */
/* F.S. Ukuran list bertambah sebanyak num */

void displayDrafts(StackDraft d);
/* Menampilkan draft terakhir yang user buat */
/* I.S. d terdefinisi */
/* F.S. menampilkan draft top*/

/* Plotting Draft,
1. User memanggil draft di main
2. User mengetik draft dengan kapasitas yang ditentukan
3. User memilih untuk save/upload/delete/cancel draft
4. Draft akan disimpan di list of draft yang menjadi global memory pada main */

#endif