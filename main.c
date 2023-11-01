#include <stdio.h>
#include <stdlib.h>
#include "lib/wordmachine/wordmachine.h"
#include "lib/user/user.h"


int main(){
    ListUser UserList;
    RelationMatrix pertemanan;
    createListUser(&UserList);
    createRelationMatrix(&pertemanan);
    daftarUSER(&UserList, &pertemanan); //0
    daftarUSER(&UserList,&pertemanan); //1
    daftarUSER(&UserList,&pertemanan); //2
    daftarUSER(&UserList,&pertemanan);//3
    daftarUSER(&UserList,&pertemanan);//4
    daftarUSER(&UserList,&pertemanan);//5
    tambahTeman(&UserList, 0, &pertemanan); //1
    tambahTeman(&UserList, 0, &pertemanan);//2
    tambahTeman(&UserList, 0, &pertemanan);//3
    tambahTeman(&UserList, 0, &pertemanan);//4
    tambahTeman(&UserList, 0, &pertemanan);//5
    acceptPertemanan(&UserList, 1, &pertemanan); //0
    acceptPertemanan(&UserList, 2, &pertemanan);
    acceptPertemanan(&UserList, 3, &pertemanan);
    acceptPertemanan(&UserList, 4, &pertemanan);
    acceptPertemanan(&UserList, 5, &pertemanan);
    daftarTeman(UserList,0,pertemanan);
    hapusTeman(UserList,1,&pertemanan); //0
    daftarTeman(UserList,0,pertemanan);
    hapusTeman(UserList,0,&pertemanan); //1
    hapusTeman(UserList,2,&pertemanan); //0
    daftarTeman(UserList, 0, pertemanan); 
    printMatrixRelation(pertemanan);
    //daftarUSER(&UserList);
    //displayDataUser(USER(UserList,1));
    stopRead();
}