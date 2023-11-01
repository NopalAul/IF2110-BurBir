#include <stdio.h>
#include <stdlib.h>
#include "lib/wordmachine/wordmachine.h"
#include "lib/user/user.h"


int main(){
    ListUser UserList;
    RelationMatrix pertemanan;
    createListUser(&UserList);
    createRelationMatrix(&pertemanan);
    daftarUSER(&UserList);
    displayDataUser(USER(UserList,0));
    daftarUSER(&UserList);
    printf("-------%d", UserList.length);
    displayDataUser(USER(UserList,0));
    daftarPermintaanTeman(UserList, 0);
    tambahTeman(&UserList, 0, &pertemanan);
    daftarPermintaanTeman(UserList, 1);
    acceptPertemanan(&UserList, 1, &pertemanan);
    daftarTeman(UserList,0,pertemanan);
    //daftarUSER(&UserList);
    //displayDataUser(USER(UserList,1));
    stopRead();
}