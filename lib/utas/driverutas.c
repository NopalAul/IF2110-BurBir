#include "utas.h"
#include "../datetime/datetime.h"
#include "../wordmachine/wordmachine.h"
#include "../user/user.h"
#include "../boolean/boolean.h"

int main(){
    USER user;
    ListUser listUser; RelationMatrix r;
    createListUser(&listUser); createRelationMatrix(&r);
    daftarUSER(&listUser,&r);
    user = USER(listUser,0);

    ListUtas l;
    CreateListUtas(&l);
    tulisUtas(&l,user,1);
    cetakUtas(l,-99);
    hapusUtas(&l,-99,2);
    cetakUtas(l,-99);
    hapusUtas(&l,-99,1);
    cetakUtas(l,-99);
    sambungUtas(&l,-99,1);
    cetakUtas(l,-99);
    sambungUtas(&l,-99,1);
    cetakUtas(l,-99);

}
// gcc -o driver driverutas.c ../datetime/datetime.c ../wordmachine/wordmachine.c ../user/user.c ../charmachine/charmachine.c ../pcolor/pcolor.c ../relation/relation.c utas.c