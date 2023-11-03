#include <stdio.h>
#include <stdlib.h>
#include "utas.h"

STRING Accept;
STRING Reject;
boolean acceptNotInitialized = true;

Address newNode (int IDUtas, USER user, STRING content)
/* Definisi List : */
/* List kosong : FIRST(l) = NULL */
/* Setiap elemen dengan Address p dapat diacu INFO(p), NEXT(p) */
/* Elemen terakhir list: jika addressnya Last, maka NEXT(Last)=NULL */
{
    Address p = (Address)malloc(sizeof(Utas));
    if(p != NULL) {
        IDUTAS(p) = IDUtas;
        AUTHOR(p) = user;
        CONTENT(p) = content;
        DATETIME(p) = getCurrentDATETIME() ;
        NEXT(p) = NULL;
    }
    return p;   
}

void CreateListUtas(ListUtas *l)
/* I.S. sembarang             */
/* F.S :   terbentuk ListUtas kosong l (length = 0) */
{
    FIRST(*l) = NULL;
}

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

/*** PENAMBAHAN ELEMEN ***/
void insertFirst(ListUtas *l, int IDUtas, USER user, STRING content)
/* I.S. l mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen pertama dengan komponen utas jika alokasi berhasil. */
/* Jika alokasi gagal: I.S.= F.S. */
{
    Address p;
    p = newNode(IDUtas, user, content);
    if(p != NULL) {
        NEXT(p) = FIRST(*l);
        FIRST(*l) = p;
    }
}

void insertLast(ListUtas *l, int IDUtas, USER user, STRING content)
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
            Address last = FIRST(*l);
            while(NEXT(last) != NULL) {
                last = NEXT(last);
            }
            NEXT(last) = p;
        }
    }
}

void insertAt(ListUtas *l, int IDUtas, int index, USER user, STRING content)
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
/* F.S. Elemen pertama list dihapus: alamat elemen pertama di-dealokasi */
{
    Address p = FIRST(*l);
    // *val = INFO(p);
    FIRST(*l) = NEXT(p);
    free(p);
}

void deleteAt(ListUtas *l, int index)
/* I.S. list tidak kosong, idx indeks yang valid dalam l, yaitu 0..length(l) */
/* F.S. Elemen l pada indeks ke-idx dihapus dari l */
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


/****************** PROSES SEMUA ELEMEN LISTUTAS ******************/

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

void tulisUtas(ListUtas *l, USER user, int IDKicau)
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
    int index;

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
        
        insertFirst(l, IDUtas, user, CONTENT(p));

        do{
            printf("Apakah Anda ingin melanjutkan utas ini? (YA/TIDAK)");
            readString(); printf("\n");
            if(!isStringSimiliar(Accept, string)) {
                printf("Input Anda tidak valid. Masukkan lagi yuk!\n\n");
            }
        } while(!isStringSimiliar(Accept,string) && !isStringSimiliar(Reject,string));

        // Pilihan YA, terus lanjutkan utas
        while(isStringSimiliar(Accept, string)) {
            index = length(l)-1;
            sambungUtas(&l, IDUtas, index);
        }
        printf("Utas selesai!\n\n");
    }
}

// int searchIndexUtas(ListUtas l, int index)
// {
//     /* Mengembalikan index sebuah Utas di dalam ListUtas l. Mengembalikan NOT_FOUND jika tidak ditemukan */
//     Address p;
//     p = FIRST(l);
//     boolean found = false;
//     while(NEXT(p) != NULL && !found) {
//         if(INDEX(p) = index) {
//             found = true;
//         }
//     }

// }

void sambungUtas(ListUtas *l, int IDUtas, int index) //PERLU PARAMETER USER?
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
    else if(index > length(*l)-1) {
        // Kondisi index terlalu tinggi
        printf("Index terlalu tinggi!\n\n");
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
        
        insertAt(l, IDUtas, index, AUTHOR(p), CONTENT(p));
    }

}

void hapusUtas(ListUtas *l, int IDUtas, int index)
{
    /* Menghapus utas sesuai posisi index, tidak dapat menghapus index 0 (ID kicauan utama) 
    I.S :   IDUtas, mungkin bukan milik pengguna saat ini
    F.S :   Utas pada index terhapus, index Utas berkurang?*/
    if(true) {
        // Kondisi utas bukan milik pengguna saat ini
        printf("Anda tidak bisa menghapus kicauan dalam utas ini!\n\n");
    }
    else if(true) {
        // Kondisi utas tidak ditemukan
        printf("Utas tidak ditemukan!\n\n");
    }
    else {
        // Kondisi utas milik sendiri
        if(index > length(*l)-1) {
            // Kondisi index utas tidak ditemukan
            printf("Kicauan sambungan dengan index %d tidak ditemukan pada utas!\n\n",index);
        }
        else if(index == 0) {
            // Kondisi index = 0
            printf("Anda tidak bisa menghapus kicauan utama!\n\n");
        }
        else {
            // Kondisi valid
            deleteAt(l,index);
            printf("Kicauan sambungan berhasil dihapus!\n\n");
        }
    }
}

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
        printf("| ID = %d\n",IDKICAU(p)); //IDKicau ganti
        printf("| "); displayString(USERNAME(AUTHOR(p))); 
        printf("| "); displayDATETIME(DATETIME(p)); 
        printf("| "); displayString(CONTENT(p));printf("\n");
        
        p = NEXT(p);

        // Cetak seluruh utas
        int index = 1;
        while(NEXT(p) != NULL) {
            printf("   | INDEX = %d\n",index);
            printf("   |"); displayString(USERNAME(AUTHOR(p)));
            printf("   | "); displayDATETIME(DATETIME(p)); 
            printf("   |"); displayString(CONTENT(p));printf("\n");

            index++;
            p = NEXT(p);
        }
    }
}