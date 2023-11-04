#include <stdio.h>
#include "simpan.h"

int main ()
{
    ListUser L;
    RelationMatrix m;
    ListFriendRequest lf;
    ListKicau lk;
    STRING text;
    char kicau[10] = "gacor kang";
    createString(&text, kicau);
    createListKicau(&lk, 100000);
    createRelationMatrix(&m);
    createListRequest(&lf);
    createListUser(&L);
    daftarUSER(&L, &m);
    daftarUSER(&L, &m);
    daftarUSER(&L, &m);
    createKicau(&lk, USER(L, 0),text);
    saveAll(L, m, lf, lk);

    return 0;
}