#include <stdio.h>
#include <stdlib.h>
#include "utas.h"

STRING Accept;
STRING Reject;
boolean acceptNotInitialized = true;

Address newNode (int IDUtas, STRING author, STRING content)
/* Definisi List : */
/* List kosong : FIRST(l) = NULL */
/* Setiap elemen dengan Address p dapat diacu INFO(p), NEXT(p) */
/* Elemen terakhir list: jika addressnya Last, maka NEXT(Last)=NULL */
{
    Address p = (Address)malloc(sizeof(Utas));
    if(p != NULL) {
        IDUTAS(p) = IDUtas;
        // index?
        AUTHOR(p) = author;
        CONTENT(p) = content;
        // datetime?
        NEXT(p) = NULL;
    }
    return p;   
}


void CreateListUtas(ListUtas *l)
/* I.S. sembarang             */
/* F.S :   terbentuk ListUtas kosong l (l.length = 0) */
{
    FIRST(*l) = NULL;
}

/****************** TEST LIST KOSONG ******************/
boolean isEmpty(ListUtas l)
/* Mengirim true jika ListUtas kosong */
{
    return (FIRST(l) == NULL);
}

int indexOf(ListUtas l, ElType val); //#### belum ganti
/* I.S. l, val terdefinisi */
/* F.S. Mencari apakah ada elemen list l yang bernilai val */
/* Jika ada, mengembalikan indeks elemen pertama l yang bernilai val */
/* Mengembalikan IDX_UNDEF jika tidak ditemukan */

/****************** PRIMITIF BERDASARKAN NILAI ******************/
/*** PENAMBAHAN ELEMEN ***/
void insertFirst(ListUtas *l, int IDUtas, STRING author, STRING content)
/* I.S. l mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen pertama dengan nilai val jika alokasi berhasil. */
/* Jika alokasi gagal: I.S.= F.S. */
{
    Address p;
    p = newNode(IDUtas, author, content);
    if(p != NULL) {
        NEXT(p) = FIRST(*l);
        FIRST(*l) = p;
    }
}

void insertLast(ListUtas *l, int IDUtas, STRING author, STRING content)
/* I.S. l mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen list di akhir: elemen terakhir yang baru */
/* bernilai val jika alokasi berhasil. Jika alokasi gagal: I.S.= F.S. */
{
    if (isEmpty(*l)) {
        insertFirst(l, IDUtas, author, content);
    }
    else {
        Address p = newNode(IDUtas, author, content);
        if(p != NULL) {
            Address last = FIRST(*l);
            while(NEXT(last) != NULL) {
                last = NEXT(last);
            }
            NEXT(last) = p;
        }
    }
}

void insertAt(ListUtas *l, int IDUtas, int index, STRING author, STRING content)
/* I.S. l tidak mungkin kosong, idx indeks yang valid dalam l, yaitu 0..length(l) */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menyisipkan elemen dalam list pada indeks ke-idx (bukan menimpa elemen di i) */
/* yang bernilai val jika alokasi berhasil. Jika alokasi gagal: I.S.= F.S. */
{
    if(index == 0) { // perhatikan index 0 atau 1?
        insertFirst(l, IDUtas, author, content);
    }
    else {
        Address p = newNode(IDUtas, author, content);
        if(p != NULL) {
            Address at = FIRST(*l);
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

/*** PENGHAPUSAN ELEMEN ***/
void deleteFirst(ListUtas *l)
/* I.S. List l tidak kosong  */
/* F.S. Elemen pertama list dihapus: nilai info disimpan pada x */
/*      dan alamat elemen pertama di-dealokasi */
{
    Address p = FIRST(*l);
    // *val = INFO(p);
    FIRST(*l) = NEXT(p);
    free(p);
}

void deleteLast(ListUtas *l)
/* I.S. list tidak kosong */
/* F.S. Elemen terakhir list dihapus: nilai info disimpan pada x */
/*      dan alamat elemen terakhir di-dealokasi */
{
    if(NEXT(*l) == NULL) { 
        deleteFirst(l);
    }
    else{
        Address p = FIRST(*l), last = NULL;
        while(NEXT(p) != NULL) {
            last = p;
            p = NEXT(p);
        }
        if(last == NULL) {
            FIRST(*l) = NULL;
        }
        else {
            NEXT(last) = NULL;
        }
        // *val = INFO(p);
        free(p);
    }
}

void deleteAt(ListUtas *l, int index)
/* I.S. list tidak kosong, idx indeks yang valid dalam l, yaitu 0..length(l) */
/* F.S. val diset dengan elemen l pada indeks ke-idx. */
/*      Elemen l pada indeks ke-idx dihapus dari l */
{
    if(index == 0) {
        deleteFirst(l);
    }
    else {
        Address p, at = FIRST(*l);
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


/****************** PROSES SEMUA ELEMEN LIST ******************/
void displayList(ListUtas l);
// void printInfo(List l);
/* I.S. List mungkin kosong */
/* F.S. Jika list tidak kosong, iai list dicetak ke kanan: [e1,e2,...,en] */
/* Contoh : jika ada tiga elemen bernilai 1, 20, 30 akan dicetak: [1,20,30] */
/* Jika list kosong : menulis [] */
/* Tidak ada tambahan karakter apa pun di awal, akhir, atau di tengah */

int length(ListUtas l)
{
    /* Mengirimkan banyaknya elemen list; mengirimkan 0 jika list kosong */
    Address p = FIRST(l);
    int len = 0;
    while(p != NULL) {
        p = NEXT(p);
        len++;
    }
    return len;
}

void tulisUtas(ListUtas *l, int IDKicau)
/* Membuat utas baru dari kicauan utama. Utas dapat dilanjutkan 
I.S :   IDKicau, mungkin bukan milik pengguna saat ini
F.S :   IDUtas terbentuk, index Utas terbentuk, terisi kicauan baru, length ListUtas bertambah */
{
    if (acceptNotInitialized){
        acceptNotInitialized = false;
        createString(&Accept, "YA");
        createString(&Reject, "TIDAK");
    }

    // CREATELISTUTAS kah?
    Address p;
    p = FIRST(*l);
    int IDUtas;
    int index; //?
    // datetime?

    if(true) {
        // Kondisi IDKicau tidak ditemukan
        printf("Kicauan tidak ditemukan\n\n");
    } 
    else if(true) {
        // Kondisi IDKicau bukan milik pengguna saat ini
        printf("Utas ini bukan milik anda!\n\n");
    }
    else{
        // Kondisi milik pengguna saat ini
        printf("\nUtas berhasil dibuat!\n\n");
        printf("Masukkan kicauan:\n");
        readKicauan(); copyString(&CONTENT(p), string);
        printf("\n");
        
        insertFirst(l, IDUtas, AUTHOR(p), CONTENT(p));

        do{
            printf("Apakah Anda ingin melanjutkan utas ini? (YA/TIDAK)");
            readString(); printf("\n");
            if(!isStringSimiliar(Accept, string)) {
                printf("Input Anda tidak valid. Masukkan lagi yuk!\n\n");
            }
        } while(!isStringSimiliar(Accept,string) && !isStringSimiliar(Reject,string));

        // Pilihan YA, terus lanjutkan utas
        while(isStringSimiliar(Accept, string)) {
            sambungUtas(&l, IDUtas, index);
        }
        printf("Utas selesai!\n\n");
    }
}

int searchIndexUtas(ListUtas l, int index)
{
    /* Mengembalikan index sebuah Utas di dalam ListUtas l. Mengembalikan NOT_FOUND jika tidak ditemukan */
    Address p;
    p = FIRST(l);
    boolean found = false;
    while(NEXT(p) != NULL && !found) {
        if(INDEX(p) = index) {
            found = true;
        }
    }

}

void sambungUtas(ListUtas *l, int IDUtas, int index)
/* Melakukan sambung utas, menambah utas di posisi index yang dituju dari sebuah utas utama.
I.S :   IDUtas, mungkin bukan milik pengguna saat ini
F.S :   terisi kicauan baru, index Utas bertambah */
{
    Address p;
    p = FIRST(*l);

    if(true) {
        // Kondisi tidak ditemukan IDUtas
        printf("Utas tidak ditemukan!\n\n");
    }
    else if(true) {
        // Kondisi index terlalu tinggi
        printf("Utas tidak ditemukan!\n\n");
    }
    else if(true) {
        // Kondisi IDUtas bukan milik pengguna saat ini
        printf("Anda tidak bisa menyambung utas ini!\n\n");
    }
    else {
        // Kondisi valid
        printf("Masukkan kicauan:\n");
        readKicauan(); copyString(&CONTENT(p), string);
        printf("\n");
        
        insertFirst(l, IDUtas, AUTHOR(p), CONTENT(p));
    }

}

void hapusUtas(ListUtas *l, int IDUtas, int index);
/* Menghapus utas sesuai posisi index, tidak dapat menghapus index 0 (ID kicauan utama) 
I.S :   IDUtas, mungkin bukan milik pengguna saat ini
F.S :   Utas pada index terhapus, index Utas berkurang?*/

void cetakUtas(ListUtas l, int IDUtas)
/* Mencetak seluruh kicauan dalam utas dengan id = IDUtas */
{
    Address p;
    p = FIRST(l);

    if(isEmpty(l)) {
        printf("Maaf, belum ada utas untuk ditampilkan.");
    }
    else {
        // Cetak kicauan (utas utama)
        // printf("| ID = %d\n",IDKICAU(p));
        printf("| "); displayString(AUTHOR(p));
        printf("ini tempat datetime");
        displayString(CONTENT(p));
        p = NEXT(p);

        // Cetak seluruh utas
        while(NEXT(p) != NULL) {
            printf("   | INDEX = ");
            printf("   |"); displayString(AUTHOR(p));
            printf("ini tempat datetime");
            displayString(CONTENT(p));
        }
    }
}