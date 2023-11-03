#include <stdio.h>
#include <stdlib.h>
#include "draft.h"
#include "../datetime/datetime.c"


void CreateEmptyDraft(Draft *d, int capacity)
/* I.S. sembarang; */
/* F.S. Membuat sebuah stack draft d kosong */
/* jadi indeksnya antara 0.. nEff */
/* Ciri stack kosong : TOP bernilai Nil */
{
    d->buffer = (STRING *)malloc(capacity * sizeof(STRING));
    d->capacity = capacity;
    d->nEff = 0;
    d->Top=-1;
}

void dealocateDraft(Draft *d)
/* I.S. l terdefinisi; */
/* F.S. (l) dikembalikan ke system, CAPACITY(l)=0; NEFF(l)=0 */
{
    CAPACITY(*d)=0;
    NEFF(*d)=0;
    free(BUFFER(*d));
}

boolean IsEmpty(Draft d)
/* Mengirim true jika Stack kosong: lihat definisi di atas */
{
    return(d.nEff==0 || d.Top==-1);
}

boolean IsFull(Draft d)
/* Mengirim true jika tabel penampung nilai elemen stack penuh */
{
    return(d.nEff==d.capacity || d.Top==d.capacity-1);
}

void expandDraft(Draft *d, int num)
/* Proses : Menambahkan capacity l sebanyak num */
/* I.S. Draft sudah terdefinisi */
/* F.S. Ukuran draft bertambah sebanyak num */
{
    STRING temp[CAPACITY(*d)];
    for(int i=0; i<CAPACITY(*d); i++){
        temp[i]=d->buffer[i];
    }
    dealocateDraft(d);
    CreateEmptyDraft(d, CAPACITY(*d)+num);
    for(int j=0; j<CAPACITY(*d); j++){
        d->buffer[j]=temp[j];
    }
}

void PushDraft(Draft *d, STRING s)
/* Menambahkan X sebagai elemen Stack S. */
/* I.S. S mungkin kosong, tabel penampung elemen stack mungkin penuh */
/* F.S. X menjadi TOP yang baru,TOP bertambah 1 */
{
    if(IsFull(*d)){
        expandDraft(d, d->capacity);
        d->Top++;
        d->nEff++;
        d->buffer[d->Top]=s;
    }else{
        d->Top++;
        d->nEff++;
        d->buffer[d->Top]=s;
    }
}

void PopDraft(Draft * d, STRING* s)
/* Menghapus STRING s dari Stack d. */
/* I.S. d  tidak mungkin kosong */
/* F.S. s adalah elemen TOP yang lama, TOP berkurang 1 */
{
    *s = d->buffer[d->Top];
    d->nEff--;
    d->Top--;
}

void displayDrafts(Draft d)
/* Menampilkan draft terakhir yang user buat */
/* I.S. d terdefinisi */
/* F.S. menampilkan draft top*/
{
    DATETIME dt;
    createDATETIME(&dt);
    dt=getCurrentDATETIME();
    if(IsEmpty(d)){
        printf("Yah, anda belum memiliki draf apapun! Buat dulu ya!:D\n");
    }else{
        printf("Ini draft terakhir anda:\n");
        printf("| ");
        displayDATETIME(dt);
        printf("| ");
        displayString(d.buffer[d.Top]);
    }
}


/* Plotting Draft,
1. User memanggil draft di main.
2. User dapat memilih untuk melihat draft terbarunya atau ingin membuat draft baru.
3. User mengetik draft dengan kapasitas yang ditentukan, apabila berlebihan program akan meminta mengedit, user akan cancel/save draft.
4. User memilih untuk upload/delete draft.
5. Draft akan disimpan di list of draft di global memory main untuk menampung draft per user.
6. Mekanisme save :
    - Setelah mengetik draft, jenis tipe data string akan disimpan (dipush) pada stack draft
7. Mekanisme upload :
    - Setelah melakukan save, apabila user ingin mengupload draft paling baru (top) maka draft paling baru akan dipop dan dimasukkan ke fungsi kicau*/