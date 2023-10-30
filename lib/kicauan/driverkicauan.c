#include "kicauan.h"
#include "../datetime/datetime.h"
#include "../wordmachine/wordmachine.h"
#include "../user/user.h"
#include "../boolean/boolean.h"

int main(){
    ListKicau l;
    createListKicau(&l, 10);
    USER user;
    ListUser listUser;
    createListUser(&listUser);
    daftarUSER(&listUser);
    user = USER(listUser,0);
    STRING text;
    createString(&text, "Halo Dunia");
    createKicau(&l, user,text );
    displayKicauan(l);
    
    
   
}
// gcc -o driver driverkicauan.c ../datetime/datetime.c ../wordmachine/wordmachine.c ../user/user.c ../charmachine/charmachine.c ..\pcolor\pcolor.c kicauan.c