#include <stdio.h>
#include <stdlib.h>
#include "lib/wordmachine/wordmachine.h"
#include "lib/user/user.h"
#include "lib/kicauan/kicauan.h"
#include "lib/draft/draft.h"
#include "lib/boolean/boolean.h"
#include "lib/charmachine/charmachine.h"
#include "lib/datetime/datetime.h"
#include "lib/reply/reply.h"

int main()
{
    createListUser();
    createRelationMatrix();
    daftarUSER(UserList, RelMatrix);
    displayDataUser(USER(UserList, 0));
    gantiProfil(&USER(UserList, 0));
    displayDataUser(USER(UserList, 0));
    ubahFotoProfil(&USER(UserList, 0));
    displayDataUser(USER(UserList, 0));
    stopRead();
}