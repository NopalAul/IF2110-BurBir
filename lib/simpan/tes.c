#include <stdio.h>
#include "simpan.h"

int main ()
{
    ListUser L;
    RelationMatrix m;
    ListFriendRequest lf;
    createRelationMatrix(&m);
    createListRequest(&lf);
    createListUser(&L);
    daftarUSER(&L, &m);
    daftarUSER(&L, &m);
    daftarUSER(&L, &m);
    saveAll(L, m, lf);

    return 0;
}