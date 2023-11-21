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
<<<<<<< HEAD
        IDUTAS(p) = IDUtas;
        AUTHOR(p) = user;
        CONTENT(p) = content;
        DATETIME(p) = getCurrentDATETIME() ;
=======
        AUTHORUTAS(p) = user;
        CONTENT(p) = content;
        DATETIMEUTAS(p) = getCurrentDATETIME() ;
>>>>>>> 25974f9a0976b35112fe3027e1f8030f6665d5ab
        NEXT(p) = NULL;
    }
    return p;   
}

<<<<<<< HEAD
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
=======
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

int indexOf(UtasList l, ElType val); //#### belum ganti
>>>>>>> 25974f9a0976b35112fe3027e1f8030f6665d5ab
/* I.S. l, val terdefinisi */
/* F.S. Mencari apakah ada elemen list l yang bernilai val */
/* Jika ada, mengembalikan indeks elemen pertama l yang bernilai val */
/* Mengembalikan IDX_UNDEF jika tidak ditemukan */

/*** PENAMBAHAN ELEMEN ***/
<<<<<<< HEAD
void insertFirst(ListUtas *l, int IDUtas, USER user, STRING content)
=======
void insertFirst(UtasList *l, int IDUtas, USER user, STRING content)
>>>>>>> 25974f9a0976b35112fe3027e1f8030f6665d5ab
/* I.S. l mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen pertama dengan komponen utas jika alokasi berhasil. */
/* Jika alokasi gagal: I.S.= F.S. */
{
    Address p;
    p = newNode(IDUtas, user, content);
    if(p != NULL) {
<<<<<<< HEAD
        NEXT(p) = FIRST(*l);
        FIRST(*l) = p;
    }
}

void insertLast(ListUtas *l, int IDUtas, USER user, STRING content)
=======
        NEXT(p) = FIRSTUTAS(*l);
        FIRSTUTAS(*l) = p;
    }
}

void insertLast(UtasList *l, int IDUtas, USER user, STRING content)
>>>>>>> 25974f9a0976b35112fe3027e1f8030f6665d5ab
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
<<<<<<< HEAD
            Address last = FIRST(*l);
=======
            Address last = FIRSTUTAS(*l);
>>>>>>> 25974f9a0976b35112fe3027e1f8030f6665d5ab
            while(NEXT(last) != NULL) {
                last = NEXT(last);
            }
            NEXT(last) = p;
        }
    }
}

<<<<<<< HEAD
void insertAt(ListUtas *l, int IDUtas, int index, USER user, STRING content)
=======
void insertAt(UtasList *l, int IDUtas, int index, USER user, STRING content)
>>>>>>> 25974f9a0976b35112fe3027e1f8030f6665d5ab
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
<<<<<<< HEAD
            Address at = FIRST(*l);
=======
            Address at = FIRSTUTAS(*l);
>>>>>>> 25974f9a0976b35112fe3027e1f8030f6665d5ab
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
<<<<<<< HEAD
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
=======
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
>>>>>>> 25974f9a0976b35112fe3027e1f8030f6665d5ab
/* I.S. list tidak kosong, idx indeks yang valid dalam l, yaitu 0..length(l) */
/* F.S. Elemen l pada indeks ke-idx dihapus dari l */
{
    if(index == 0) {
        deleteFirst(l);
    }
    else {
<<<<<<< HEAD
        Address p, at = FIRST(*l);
=======
        Address p, at = FIRSTUTAS(*l);
>>>>>>> 25974f9a0976b35112fe3027e1f8030f6665d5ab
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


<<<<<<< HEAD
/****************** PROSES SEMUA ELEMEN LISTUTAS ******************/

int length(ListUtas l)
{
    /* Mengirimkan banyaknya elemen list; mengirimkan 0 jika list kosong */
    Address p = FIRST(l);
=======
/****************** PROSES SEMUA ELEMEN UtasList ******************/

int length(UtasList l)
{
    /* Mengirimkan banyaknya elemen list; mengirimkan 0 jika list kosong */
    Address p = FIRSTUTAS(l);
>>>>>>> 25974f9a0976b35112fe3027e1f8030f6665d5ab
    int len = 0;
    while(p != NULL) {
        p = NEXT(p);
        len++;
    }
    return len;
}

<<<<<<< HEAD
void tulisUtas(ListUtas *l, USER user, int IDKicau)
/* Membuat utas baru dari kicauan utama. Utas dapat dilanjutkan 
I.S :   IDKicau, mungkin bukan milik pengguna saat ini
F.S :   IDUtas terbentuk, index Utas terbentuk, terisi kicauan baru, length ListUtas bertambah */
=======
void tulisUtas(UtasList *l, USER user, int IDKicau)
/* Membuat utas baru dari kicauan utama. Utas dapat dilanjutkan 
I.S :   IDKicau, mungkin bukan milik pengguna saat ini
F.S :   IDUtas terbentuk, index Utas terbentuk, terisi kicauan baru, length UtasList bertambah */
>>>>>>> 25974f9a0976b35112fe3027e1f8030f6665d5ab
{
    if (belumInisialisasi){
        belumInisialisasi = false;
        createString(&Terima, "YA");
        createString(&Tolak, "TIDAK");
    }

    Address p;
<<<<<<< HEAD
    p = FIRST(*l);
=======
    p = FIRSTUTAS(*l);
>>>>>>> 25974f9a0976b35112fe3027e1f8030f6665d5ab
    int IDUtas = -1; // assign apa?
    int index;
    STRING content;

    // if(true) {
    //     // Kondisi IDKicau tidak ditemukan
    //     printf("Kicauan tidak ditemukan\n\n");
    // } 
    // else if(true) {
    //     // Kondisi IDKicau bukan milik pengguna saat ini
    //     printf("Utas ini bukan milik anda!\n\n");
    // }
    // else
    {
        // Kondisi milik pengguna saat ini
        printf("\nUtas berhasil dibuat!\n\n");
        printf("Masukkan kicauan:\n");
        readKicauan();
        copyString(&content, string); 
        printf("\n");
        
        insertFirst(l, IDUtas, user, content);

        do{
            printf("Apakah Anda ingin melanjutkan utas ini? (YA/TIDAK) ");
            readString(); printf("\n");
            if(!isStringSimiliar(Terima, string)) {
                printf("Input Anda tidak valid. Masukkan lagi yuk!\n\n");
            }
        } while(!isStringSimiliar(Terima,string) && !isStringSimiliar(Tolak,string));

        // Pilihan YA, terus lanjutkan utas
        while(isStringSimiliar(Terima, string)) {
            index = length(*l);
            printf("len: %d\n",length(*l)); // delete
            sambungUtas(l, IDUtas, index);
            printf("Apakah Anda ingin melanjutkan utas ini? (YA/TIDAK) ");
            readString(); printf("\n");
            if(!isStringSimiliar(Terima, string)) {
                printf("Input Anda tidak valid. Masukkan lagi yuk!\n\n");
            }
        }
        printf("Utas selesai!\n\n");
    }
}

<<<<<<< HEAD
// int searchIndexUtas(ListUtas l, int index)
// {
//     /* Mengembalikan index sebuah Utas di dalam ListUtas l. Mengembalikan NOT_FOUND jika tidak ditemukan */
=======
// int searchIndexUtas(UtasList l, int index)
// {
//     /* Mengembalikan index sebuah Utas di dalam UtasList l. Mengembalikan NOT_FOUND jika tidak ditemukan */
>>>>>>> 25974f9a0976b35112fe3027e1f8030f6665d5ab
//     Address p;
//     p = FIRST(l);
//     boolean found = false;
//     while(NEXT(p) != NULL && !found) {
//         if(INDEX(p) = index) {
//             found = true;
//         }
//     }

// }

<<<<<<< HEAD
void sambungUtas(ListUtas *l, int IDUtas, int index) //PERLU PARAMETER USER?
=======
void sambungUtas(UtasList *l, int IDUtas, int index) //PERLU PARAMETER USER?
>>>>>>> 25974f9a0976b35112fe3027e1f8030f6665d5ab
/* Melakukan sambung utas, menambah utas di posisi index yang dituju dari sebuah utas utama.
I.S :   IDUtas, mungkin bukan milik pengguna saat ini
F.S :   terisi kicauan baru, index Utas bertambah */
{   
    Address p;
<<<<<<< HEAD
    p = FIRST(*l);
=======
    p = FIRSTUTAS(*l);
>>>>>>> 25974f9a0976b35112fe3027e1f8030f6665d5ab
    STRING content;

    // if(IDUtas == NOT_FOUND) {
    //     // Kondisi tidak ditemukan IDUtas
    //     printf("Utas tidak ditemukan!\n\n");
    // }
    // else if(index > length(*l)) {
    //     // Kondisi index terlalu tinggi
    //     printf("Index terlalu tinggi!\n\n");
    // }
    // else if(IDUtas != -99) {
    //     // Kondisi IDUtas bukan milik pengguna saat ini
    //     printf("Anda tidak bisa menyambung utas ini!\n\n");
    // }
    // else
    {
        // Kondisi valid
        printf("Masukkan kicauan:\n");
        readKicauan(); copyString(&content, string);
        printf("\n");
        

<<<<<<< HEAD
        insertAt(l, IDUtas, index, AUTHOR(p), content);
=======
        insertAt(l, IDUtas, index, AUTHORUTAS(p), content);
>>>>>>> 25974f9a0976b35112fe3027e1f8030f6665d5ab
    }

}

<<<<<<< HEAD
void hapusUtas(ListUtas *l, int IDUtas, int index)
=======
void hapusUtas(UtasList *l, int IDUtas, int index)
>>>>>>> 25974f9a0976b35112fe3027e1f8030f6665d5ab
{
    /* Menghapus utas sesuai posisi index, tidak dapat menghapus index 0 (ID kicauan utama) 
    I.S :   IDUtas, mungkin bukan milik pengguna saat ini
    F.S :   Utas pada index terhapus, index Utas berkurang?*/
    // if(true) {
    //     // Kondisi utas bukan milik pengguna saat ini
    //     printf("Anda tidak bisa menghapus kicauan dalam utas ini!\n\n");
    // }
    // else if(true) {
    //     // Kondisi utas tidak ditemukan
    //     printf("Utas tidak ditemukan!\n\n");
    // }
    // else
    {
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

<<<<<<< HEAD
void cetakUtas(ListUtas l, int IDUtas)
/* Mencetak seluruh kicauan dalam utas dengan id = IDUtas */
{
    Address p;
    p = FIRST(l);
=======
void cetakUtas(UtasList l, int IDUtas)
/* Mencetak seluruh kicauan dalam utas dengan id = IDUtas */
{
    Address p;
    p = FIRSTUTAS(l);
>>>>>>> 25974f9a0976b35112fe3027e1f8030f6665d5ab

    if(isEmpty(l)) {
        printf("Maaf, belum ada utas untuk ditampilkan.");
    }
    else {
        // Cetak kicauan (utas utama)
        // printf("| ID = %d\n",IDKICAU(p)); //IDKicau ganti
        printf("| ID = %d\n",-1); //IDKicau ganti
<<<<<<< HEAD
        printf("| "); displayString(USERNAME(AUTHOR(p))); 
        printf("| "); displayDATETIME(DATETIME(p)); 
=======
        printf("| "); displayString(USERNAME(AUTHORUTAS(p))); 
        printf("| "); displayDATETIME(DATETIMEUTAS(p)); 
>>>>>>> 25974f9a0976b35112fe3027e1f8030f6665d5ab
        printf("| "); displayString(CONTENT(p)); printf("\n");
        
        p = NEXT(p);

        // Cetak seluruh utas
        int index = 1;
        while((p) != NULL) {
            printf("   | INDEX = %d\n",index);
<<<<<<< HEAD
            printf("   | "); displayString(USERNAME(AUTHOR(p)));
            printf("   | "); displayDATETIME(DATETIME(p)); 
=======
            printf("   | "); displayString(USERNAME(AUTHORUTAS(p)));
            printf("   | "); displayDATETIME(DATETIMEUTAS(p)); 
>>>>>>> 25974f9a0976b35112fe3027e1f8030f6665d5ab
            printf("   | "); displayString(CONTENT(p));printf("\n");

            index++;
            p = NEXT(p);
        }
    }
}