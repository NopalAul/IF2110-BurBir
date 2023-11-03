#ifndef draft_H
#define draft_H
#include <stdio.h>
#include <stdlib.h>
#include "../boolean/boolean.h"
#include "../wordmachine/wordmachine.c"
#include "../charmachine/charmachine.c"

typedef int TopLoc;
typedef struct{
    STRING *buffer;
    TopLoc Top;
    int nEff;
    int capacity;
} Draft;

/* SELEKTOR */
#define NEFF(d) (d).nEff
#define BUFFER(d) (d).buffer
#define TOP(d) (d).Top
#define INFOTOP(d) (d).buffer[TOP]
#define CAPACITY(d) (d).capacity

void CreateEmptyDraft(Draft *d, int capacity);
/* I.S. sembarang; */
/* F.S. Membuat sebuah stack draft d kosong */
/* jadi indeksnya antara 0.. nEff */
/* Ciri stack kosong : TOP bernilai Nil */

boolean IsEmpty(Draft d);//harusnya boolean
/* Mengirim true jika Stack kosong: lihat definisi di atas */

boolean IsFull(Draft d);//harusnya boolean
/* Mengirim true jika tabel penampung nilai elemen stack penuh */

void PushDraft(Draft *d, STRING s);
/* Menambahkan X sebagai elemen Stack S. */
/* I.S. S mungkin kosong, tabel penampung elemen stack mungkin penuh */
/* F.S. X menjadi TOP yang baru,TOP bertambah 1 */

void PopDraft(Draft * d, STRING* s);
/* Menghapus X dari Stack S. */
/* I.S. S  tidak mungkin kosong */
/* F.S. X adalah nilai elemen TOP yang lama, TOP berkurang 1 */

void expandDraft(Draft *d, int num);
/* Proses : Menambahkan capacity l sebanyak num */
/* I.S. List sudah terdefinisi */
/* F.S. Ukuran list bertambah sebanyak num */

/* Plotting Draft,
1. User memanggil draft di main
2. User mengetik draft dengan kapasitas yang ditentukan
3. User memilih untuk save/upload/delete/cancel draft
4. Draft akan disimpan di list of draft yang menjadi global memory pada main */

#endif