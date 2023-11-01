#ifndef kicauan_h
#define kicauan_h

#include "../datetime/datetime.h"
#include "../wordmachine/wordmachine.h"
#include "../user/user.h"
#include "../boolean/boolean.h"
#include "../balasan/balasan.h"

#define MAX_KICAULENGTH 280
#define NOT_FOUND -1


typedef struct{
    int id;
    USER user;
    STRING text;
    int like;
    DATETIME datetime;
    BALASAN balasan;
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
#define DATETIME(U) (U).datetime
#define BALASAN(U) (U).balasan
#define NEFF(l) (l).nEFF
#define CAPACITY(l) (l).capacity
#define KICAU(l,i)  (l).buffer[i]
#define BUFFER(l) (l).buffer

void createListKicau(ListKicau *l, int capacity);

void createKicau(ListKicau *l,USER user, STRING text);


int getBanyakKicauan(ListKicau l);

boolean isKicauanFull(ListKicau l);

boolean isKicauanEmpty(ListKicau l);

void sukaKicauan(ListKicau *l,int id );

void ubahKicauan(KICAU *kicau,STRING text);

void sortKicauan(ListKicau *l);

int getAvailableID(ListKicau l);

void expandKicauan(ListKicau *l,int num);

void addKicauan(ListKicau *l, KICAU *kicau);

void shrinkKicauan(ListKicau *l,int num);

void displayKicau(KICAU kicau);

void displayKicauan(ListKicau l);

#endif