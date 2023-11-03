#include "muat.h"

int main ()
{
    ListUser l;
    readString();
    stopRead();
    loadPengguna(string, &l);
    displayDataUser(USER(l,0));
    for (int i = 0; i < PASSWORD(USER(l,0)).length; i++)
    {
        printf("%c", PASSWORD(USER(l,0)).buffer[i]);
    }
    printf("\n");
    displayDataUser(USER(l,1));
    for (int i = 0; i < PASSWORD(USER(l,1)).length; i++)
    {
        printf("%c", PASSWORD(USER(l,1)).buffer[i]);
    }
    printf("\n");
    displayDataUser(USER(l,2));
    for (int i = 0; i < PASSWORD(USER(l,2)).length; i++)
    {
        printf("%c", PASSWORD(USER(l,2)).buffer[i]);
    }
    printf("\n");
}