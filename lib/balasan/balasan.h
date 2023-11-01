#ifndef balasan_h
#define balasan_h

#include "tree.h"
#include "../user/user.h"
#include "../datetime/datetime.h"


typedef struct{
    int id;
    USER user;
    DATETIME date;
    STRING text;

}BALASAN;

typedef struct{
    USER author;
    BALASAN *buffer; //menyimpan info KICAU (modifikasi List Statik)
    int nEFF;
    int capacity;
}ListBalasan;


#define AUTHOR(L) (L).author
#define BUFFER(L) (L).buffer
#define NEFF(L) (L).nEFF
#define CAPACITY(L) (L).capacity

#define ID(l) (l).id
#define user(l) (l).user
#define date(l) (l).date
#define text(l) (l).text


void createListBalasan(ListBalasan *L, int capacity);

void deallocateListBalasan(ListBalasan *L);

void createBalasan(ListBalasan *l,USER user,STRING text);

void addBalasan(ListBalasan *l,BALASAN balasan,int IDKicau, int IDBalasan);

boolean isBalasanFull(ListBalasan l);

boolean isBalasanEmpty(ListBalasan l);

int getBanyakBalasan(ListBalasan l);

void expandBalasan(ListBalasan *l,int num);

void shrinkBalasan(ListBalasan *l,int num);


#endif