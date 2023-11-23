#include <stdio.h>
#include "simpan.h"

int main ()
{
    RelationMatrix m;
    ListKicau lk;
    STRING text, draftt;
    char az[3] = "pes";
    char kicau[10] = "gacor kang";
    AddressReply p, p1, p2, p3;

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
    printf("%d\n", RelationLength(RelMatrix));
    for (int i = 0; i < 20; i++)
    {
        createDraft(&ContainerDraft[i]);
    }

    char drafto[28] = "ini draft, semoga gacor kang";

    createEmptyString(&draftt);
    createString(&draftt, "gacorz");
    pushDraft(&ContainerDraft[0], draftt);
    char pes[6] = "nigger";
    createEmptyString(&draftt);
    createString(&draftt, drafto);
    pushDraft(&ContainerDraft[1], draftt);
    createEmptyString(&draftt);
    createString(&draftt, "nigger hitam");
    pushDraft(&ContainerDraft[1], draftt);
    insertFirstUtas(&UTAS(KICAU(lk, 0)), 1, USER(UserList, 0), draftt);
    p = newReply(1, text, USERNAME(USER(UserList, 1)), getCurrentDATETIME());
    printf("cek\n");
    boolean succeed = false;
    addREPLY(&BALASAN(KICAU(lk, 0)), -1, p, &succeed);
    printf("cek\n");
    p1 = newReply(2, text, USERNAME(USER(UserList, 2)), getCurrentDATETIME());
    printf("cek\n");
    succeed = false;
    addREPLY(&BALASAN(KICAU(lk, 0)), 1, p1, &succeed);
    p1 = newReply(3, text, USERNAME(USER(UserList, 3)), getCurrentDATETIME());
    printf("cek\n");
    succeed = false;
    addREPLY(&BALASAN(KICAU(lk, 0)), 2, p1, &succeed);
    displayReply(BALASAN(KICAU(lk, 0)), 0);
    saveAll(string, UserList, RelMatrix, lk);

    return 0;
}