#include <stdio.h>
#include "simpan.h"

int main ()
{
    RelationMatrix m;
    ListKicau lk;
    STRING text;
    char kicau[10] = "gacor kang";
    createString(&text, kicau);
    createListUser(&UserList);
    createListKicau(&lk, 100000);
    createRelationMatrix(&RelMatrix);
    daftarUSER();
    daftarUSER();
    daftarUSER();
    daftarUSER();
    createKicau(&lk, USER(UserList, 0),text);
    tambahTeman(0);
    tambahTeman(1);
    printf("Masukkan nama folder: ");
    readString();
    stopRead();
    printMatrixRelation(RelMatrix);
    printf("%d", RelationLength(RelMatrix));
    saveAll(string, UserList, RelMatrix, lk);

    return 0;
}