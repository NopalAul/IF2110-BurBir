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
    ListKicau l;
    createListKicau(&l, 10);
    USER user;
    ListUser listUser;
    createListUser(&listUser);
    user = USER(listUser, 0);
    STRING text;
    createString(&text, "Halo Dunia");
    createKicau(&l, user, text);
    displayKicauan(l);
}