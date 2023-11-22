#include <stdio.h>

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
    user = USER(listUser,1);
    STRING text;
    createString(&text, "Halo Dunia");
    createKicau(&l, user,text );
    displayKicau(KICAU(l,0));
    printf("neff: %d\n",l.nEFF);

    printf("idutas: %d\n",IDUTAS(KICAU(l,0).utas));
    printf("username driver:");displayString(USERNAME(user));printf("\n"); //delete
    tulisUtas(&l,user,0);
    cetakUtas(l,IDUTAS(KICAU(l,0).utas));
    // printf("idutas :",IDUTAS(KICAU(l,0).utas));printf("\n"); //delete
    hapusUtas(&l,1,1);
    cetakUtas(l,IDUTAS(KICAU(l,0).utas));
    sambungUtas(&l,1,1);
    cetakUtas(l,IDUTAS(KICAU(l,0).utas));
    return 0;
    
}
// gcc -o driver driverkicauan.c ../datetime/datetime.c ../wordmachine/wordmachine.c ../user/user.c ../charmachine/charmachine.c ../pcolor/pcolor.c ../utas/utas.c ../listRequest/listRequest.c ../relation/relation.c kicauan.c