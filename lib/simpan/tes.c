#include <stdio.h>
#include "simpan.h"

int main ()
{
    ListUser L;

    createListUser(&L);
    daftarUSER(&L);
    saveAll(L);

    return 0;
}