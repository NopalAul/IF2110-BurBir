#include <stdio.h>
#include <stdlib.h>
#include "draft.h"

/* SELEKTOR */
#define NEFF(d) (d).nEff
#define BUFFER(d) (d).buffer
#define TOP(d) (d).Top
#define INFOTOP(d) (d).buffer[TOP]
#define CAPACITY(d) (d).capacity

void CreateEmptyDraft(StackDraft *d, int capacity)
/* I.S. sembarang; */
/* F.S. Membuat sebuah stack StackDraft d kosong */
/* jadi indeksnya antara 0.. nEff */
/* Ciri stack kosong : TOP bernilai Nil */
{
    d->buffer = (Draft *)malloc(capacity * sizeof(Draft));
    d->capacity = capacity;
    d->Top = NIL;
}

boolean IsEmptyDraft(StackDraft d)
/* Mengirim true jika Stack kosong: lihat definisi di atas */
{
    return (d.Top == NIL);
}

boolean IsFullDraft(StackDraft d)
/* Mengirim true jika tabel penampung nilai elemen stack penuh */
{
    return (d.Top == d.capacity - 1);
}

void dealocateStack(StackDraft *d)
/* I.S. d terdefinisi; */
/* F.S. (d) dikembalikan ke system, CAPACITY(d)=0, TOP(d)=NIL*/
{
    d->capacity = 0;
    d->Top = NIL;
    free(d->buffer);
}

void expandDraft(StackDraft *d, int num)
/* Proses : Menambahkan capacity l sebanyak num */
/* I.S. List sudah terdefinisi */
/* F.S. Ukuran list bertambah sebanyak num */
{
    Draft temp[CAPACITY(*d)];
    int init_cap = d->capacity;
    for (int i = 0; i < d->capacity; i++)
    {
        temp[i] = d->buffer[i];
    }
    dealocateStack(d);
    CreateEmptyDraft(d, init_cap + num);
    for (int i = 0; i < init_cap; i++)
    {
        d->buffer[i] = temp[i];
        d->Top++;
    }
}

void PushDraft(StackDraft *d, STRING s)
/* Menambahkan X sebagai elemen Stack S. */
/* I.S. S mungkin kosong, tabel penampung elemen stack mungkin penuh */
/* F.S. X menjadi TOP yang baru,TOP bertambah 1 */
{
    if (!IsFullDraft(*d))
    {
        d->Top++;
        d->buffer[d->Top].kicau = s;
        d->buffer[d->Top].dt = getCurrentDATETIME();
    }
    else
    {
        expandDraft(d, d->capacity);
        d->Top++;
        d->buffer[d->Top].kicau = s;
        d->buffer[d->Top].dt = getCurrentDATETIME();
    }
}

void PopDraft(StackDraft *d, STRING *s)
/* Menghapus X dari Stack S dan menyimpan date pembuatan StackDraft. */
/* I.S. S  tidak mungkin kosong */
/* F.S. X adalah nilai elemen TOP yang lama, TOP berkurang 1 */
{
    *s = d->buffer[d->Top].kicau;
    d->Top--;
}

void displayTop(StackDraft d)
/* Menampilkan draft terakhir yang user buat */
/* I.S. d terdefinisi */
/* F.S. menampilkan draft top*/
{
    printf("Ini draf terakhir anda:\n");
    printf("| %d/%d/%d %.02d:%.02d:%.02d\n", d.buffer[d.Top].dt.day, d.buffer[d.Top].dt.month, d.buffer[d.Top].dt.year, d.buffer[d.Top].dt.hour, d.buffer[d.Top].dt.minute, d.buffer[d.Top].dt.second);
    printf("| ");
    displayString(d.buffer[d.Top].kicau);
    printf("\n");
}