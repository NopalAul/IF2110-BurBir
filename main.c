#include <stdio.h>
#include <stdlib.h>
#include "lib/wordmachine/wordmachine.h"
#include "lib/user/user.h"




int main(){
    ListUser UserList;
    createListUser(&UserList);
    daftarUSER(&UserList);
    displayDataUser(USER(UserList,0));
    gantiProfil(&USER(UserList,0));
    displayDataUser(USER(UserList,0));
    aturJenisAkun(&USER(UserList,0));
    aturJenisAkun(&USER(UserList,0));
    //daftarUSER(&UserList);
    //displayDataUser(USER(UserList,1));
    stopRead();
}