#ifndef kicauan_h
#define kicauan_h

#include "../datetime/datetime.h"
#include "../wordmachine/wordmachine.h"
#include "../user/user.h"
#include "../boolean/boolean.h"
#include "../reply/reply.h"
#include "../utas/utas.h"

#define MAX_KICAULENGTH 280
#define NOT_FOUND -1


typedef struct{
    int id;
    USER user;
    STRING text;
    int like;
    DATETIME datetime;
    AddressReply balasan;
    UtasList utas;
    int NextReplyID;

} KICAU;

typedef struct{
    KICAU *buffer; //menyimpan info KICAU (modifikasi List Statik)
    int nEFF;
    int capacity;         //meyimpan banyak kicauan
    int NextUtasID;
} ListKicau;


#define ID(U) (U).id
#define AUTHOR(U) (U).user
#define TEXT(U) (U).text
#define LIKE(U) (U).like
#define DATETIME(U) (U).datetime
#define BALASAN(U) (U).balasan
#define NEFF(l) (l).nEFF
#define CAPACITY(l) (l).capacity
#define KICAU(l,i)  (l).buffer[i]
#define BUFFER(l) (l).buffer
#define UTAS(U) (U).utas

void createListKicau(ListKicau *l, int capacity);

void createKicau(ListKicau *l,USER user, STRING text);


int getBanyakKicauan(ListKicau l);

boolean isKicauanFull(ListKicau l);

boolean isKicauanEmpty(ListKicau l);

void sukaKicauan(ListKicau *l,int id,USER currUser );

// void ubahKicauan(KICAU *kicau,STRING text,USER currUser);

void sortKicauan(ListKicau *l);

int getAvailableID(ListKicau l);

void expandKicauan(ListKicau *l,int num);

void addKicauan(ListKicau *l, KICAU *kicau);

void shrinkKicauan(ListKicau *l,int num);

void displayKicau(KICAU kicau);

void displayKicauan(ListKicau l,USER currUser);

boolean isAuthorKicauPublicOrFriend(KICAU kicau,USER currUser);

void buatKicau(ListKicau *l,USER currUser);

void ubahKicauan(ListKicau *l,USER currUser,int id);

void tulisUtas(ListKicau *l, USER user, int IDKicau);
/* Membuat utas baru dari kicauan utama. Utas dapat dilanjutkan 
I.S :   IDKicau, mungkin bukan milik pengguna saat ini
F.S :   IDUtas terbentuk, index Utas terbentuk, terisi kicauan baru, length ListUtas bertambah */
#endif