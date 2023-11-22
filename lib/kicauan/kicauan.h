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
    int nextReplyID;
    Address utas;

} KICAU;

typedef struct{
    KICAU *buffer; //menyimpan info KICAU (modifikasi List Statik)
    int nEFF;
    int capacity;         //meyimpan banyak kicauan
} ListKicau;


#define ID(U) (U).id
#define AUTHOR(U) (U).user
#define TEXT(U) (U).text
#define LIKE(U) (U).like
#define NEXTREPLYID(U) (U).nextReplyID
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

void BALAS(ListKicau *lk, int currentID);
void DISPLAYBALASAN(ListKicau *lk, int currentID);
void displayBalasanHandler(REPLY r, int currentID, int depth);
void HAPUSBALASAN(ListKicau *lk, int currentID);
#endif