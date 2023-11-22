#include <stdio.h>
#include <stdlib.h>
#include "draft.h"

/* SELEKTOR */
#define NEFF(d) (d).nEff
#define BUFFER(d) (d).buffer
#define TOP(d) (d).Top
#define INFOTOP(d) (d).buffer[TOP]
#define CAPACITY(d) (d).capacity

StackDraft listofdraf[20];

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
    if (!IsEmptyDraft(d))
    {
        printf("Ini draf terakhir anda:\n");
        printf("| ");
        displayDATETIME(d.buffer[d.Top].dt);
        printf("| ");
        displayString(d.buffer[d.Top].kicau);
        printf("\n");
    }
    else
    {
        printf("Yah, anda belum memiliki draf apapun! Buat dulu ya :DD");
    }
}

/* USER SECTION */

void intializeDrafts()
/* Menginisialisasi draft kosong untuk setiap user */
/* I.S. list of drafts dengan length 20 terdefinisi */
/* F.S. mengisi keseluruhan list of drafts dengan empty stack draft */
{
    for (int i = 0; i < 20; i++)
    {
        CreateEmptyDraft(&listofdraf[i], 10);
    }
}

boolean isBuatDrafCommandValid(STRING s)
{
    if (isWordEqual(s, "HAPUS") || isWordEqual(s, "SIMPAN") || isWordEqual(s, "TERBIT"))
    {
        return true;
    }
    else
    {
        return false;
    }
}

boolean isLihatDrafCommandValid(STRING s)
{
    if (isWordEqual(s, "HAPUS") || isWordEqual(s, "UBAH") || isWordEqual(s, "TERBIT") || isWordEqual(s, "KEMBALI"))
    {
        return true;
    }
    else
    {
        return false;
    }
}

void BuatDraf(USER Author)
/* Membuat draft baru untuk current user */
/* I.S. empty stack draft untuk index ID terdefinisi */
/* F.S. membuat draft baru berdasarkan input user  */
{
    STRING draf;
    printf("Masukkan draf:\n");
    readKicauan();
    copyString(&draf, string);
    readCommand();
    while (!isBuatDrafCommandValid(string))
    {
        printf("Maaf input tidak valid, silahkan input ulang:D\n");
        readCommand();
    }
    printf("Apakah anda ingin menghapus, menyimpan, atau menerbitkan draf ini?\n");
    if (isWordEqual(string, "SIMPAN"))
    {
        PushDraft(&listofdraf[userID(Author)], draf);
        printf("Draf berhasil disimpan\n");
    }
    else if (isWordEqual(string, "TERBIT"))
    {
        // createKicau
        printf("Draf berhasil diterbitkan\n"); // sementara
    }
    else
    {
        printf("Draf berhasil dihapus\n");
    }
}

void LihatDraf(USER Author)
{
    displayTop(listofdraf[userID(Author)]);
    printf("Apakah anda ingin mengubah, menghapus, atau menerbitkan draf ini? (KEMBALI jika ingin kembali)");
    readCommand();
    while (!isLihatDrafCommandValid(string))
    {
        printf("Maaf input tidak valid, silahkan input ulang:D\n");
        readCommand();
    }
    if (isWordEqual(string, "UBAH"))
    {
        STRING sd;
        printf("Masukkan draf baru:\n");
        readKicauan();
        PopDraft(&listofdraf[userID(Author)], &sd);
        PushDraft(&listofdraf[userID(Author)], string);
        printf("Draf berhasil disimpan\n");
    }
    else if (isWordEqual(string, "TERBIT"))
    {
        // createKicau
    }
    else
    {
        STRING sd;
        PopDraft(&listofdraf[0], &sd);
        printf("Draf berhasil dihapus\n");
    }
}