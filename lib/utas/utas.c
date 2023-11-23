#include <stdio.h>
#include <stdlib.h>
#include "utas.h"

STRING Terima;
STRING Tolak;
boolean belumInisialisasi = true;

Address newNode (int IDUtas, USER user, STRING content)
/* Definisi List : */
/* List kosong : FIRST(l) = NULL */
/* Setiap elemen dengan Address p dapat diacu INFO(p), NEXT(p) */
/* Elemen terakhir list: jika addressnya Last, maka NEXT(Last)=NULL */
{
    Address p = (Address)malloc(sizeof(Utas));
    if(p != NULL) {
        AUTHORUTAS(p) = user;
        CONTENT(p) = content;
        DATETIMEUTAS(p) = getCurrentDATETIME();
        NEXT(p) = NULL;
    }
    return p;   
}

void CreateListUtas(UtasList *l)
/* I.S. sembarang             */
/* F.S :   terbentuk UtasList kosong l (length = 0) */
{
    FIRSTUTAS(*l) = NULL;
    IDUTAS(*l) = ID_UNDEF;
}

boolean isEmpty(UtasList l)
/* Mengirim true jika UtasList kosong */
{
    return (FIRSTUTAS(l) == NULL);
}


/*** PENAMBAHAN ELEMEN ***/
void insertFirst(UtasList *l, int IDUtas, USER user, STRING content)
/* I.S. l mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen pertama dengan komponen utas jika alokasi berhasil. */
/* Jika alokasi gagal: I.S.= F.S. */
{
    Address p;
    p = newNode(IDUtas, user, content);
    if(p != NULL) {
        NEXT(p) = FIRSTUTAS(*l);
        FIRSTUTAS(*l) = p;
    }
}

void insertLast(UtasList *l, int IDUtas, USER user, STRING content)
/* I.S. l mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen list di akhir: elemen terakhir yang baru */
/* berisi komponen utas jika alokasi berhasil. Jika alokasi gagal: I.S.= F.S. */
{
    if (isEmpty(*l)) {
        insertFirst(l, IDUtas, user, content);
    }
    else {
        Address p = newNode(IDUtas, user, content);
        if(p != NULL) {
            Address last = FIRSTUTAS(*l);
            while(NEXT(last) != NULL) {
                last = NEXT(last);
            }
            NEXT(last) = p;
        }
    }
}

void insertAt(UtasList *l, int IDUtas, int index, USER user, STRING content)
/* I.S. l tidak mungkin kosong, idx indeks yang valid dalam l, yaitu 0..length(l) */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menyisipkan elemen dalam list pada indeks ke-idx (bukan menimpa elemen di i) */
/* yang berisi komponen utas jika alokasi berhasil. Jika alokasi gagal: I.S.= F.S. */
{
    if(index == 0) { // perhatikan index 0 atau 1?
        insertFirst(l, IDUtas, user, content);
    }
    else {
        Address p = newNode(IDUtas, user, content);
        if(p != NULL) {
            Address at = FIRSTUTAS(*l);
            int i = 0;
            while(i < index-1) {
                at = NEXT(at);
                i++;
            }
            NEXT(p) = NEXT(at);
            NEXT(at) = p;
        }
    }
}

Address getLast(UtasList l)
{
    Address p = FIRSTUTAS(l);
    while (NEXT(p) != NULL)
    {
        p = NEXT(p);
    }
    return p;
}
/*** PENGHAPUSAN ELEMEN ***/
void deleteFirst(UtasList *l)
/* I.S. List l tidak kosong  */
/* F.S. Elemen pertama list dihapus: alamat elemen pertama di-dealokasi */
{
    Address p = FIRSTUTAS(*l);
    // *val = INFO(p);
    FIRSTUTAS(*l) = NEXT(p);
    free(p);
}

void deleteAt(UtasList *l, int index)
/* I.S. list tidak kosong, idx indeks yang valid dalam l, yaitu 0..length(l) */
/* F.S. Elemen l pada indeks ke-idx dihapus dari l */
{
    if(index == 0) {
        deleteFirst(l);
    }
    else {
        Address p, at = FIRSTUTAS(*l);
        int i = 0;
        while(i < index-1) {
            at = NEXT(at);
            i++;
        }
        p = NEXT(at);
        // *val = INFO(p);
        NEXT(at) = NEXT(p);
        free(p);
    }
}


/****************** PROSES SEMUA ELEMEN UtasList ******************/

int length(UtasList l)
{
    /* Mengirimkan banyaknya elemen list; mengirimkan 0 jika list kosong */
    Address p = FIRSTUTAS(l);
    int len = 0;
    while(p != NULL) {
        p = NEXT(p);
        len++;
    }
    return len;
}
