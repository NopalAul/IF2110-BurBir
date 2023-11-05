#include <stdio.h>
#include <stdlib.h>
#include "lib/wordmachine/wordmachine.h"
#include "lib/user/user.h"
#include "lib/kicauan/kicauan.h"
#include "lib/boolean/boolean.h"
#include "lib/charmachine/charmachine.h"
#include "lib/datetime/datetime.h"
#include "lib/pcolor/pcolor.h"

int main()
{
    ListUser l;
    createListUser(&l);
    RelationMatrix r;
    createRelationMatrix(&r);
    daftarUSER(&l, &r);
    displayDataUser(USER(l,0));
    gantiProfil(&USER(l,0));
    displayDataUser(USER(l,0));
    ubahFotoProfil(&USER(l,0));
    displayDataUser(USER(l,0));
    stopRead();
}