#include "muat.h"

int main ()
{
    ListUser l;
    ListFriendRequest lf;
    RelationMatrix m;
    ListKicau lk;

    readString();
    stopRead();
    createListUser(&l);
    createRelationMatrix(&m);
    createListRequest(&lf);
    createListKicau(&lk, 100);
    loadAll(string, &l, &m, &lf, &lk);
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
    printMatrixRelation(m);
    printf("\n");
    displayKicauan(lk);
    if (!isEmptyListRequest(REQUESTLIST(USER(l,3))) && !isEmptyListRequest(REQUESTLIST(USER(l,2))))
    {
        printf("adaan");
    }
    else
    {
        printf("gaada mas");
    }
    if (isRequestedFriend(m, 0,2))
    {
        printf("\nhooh\n");
    }
    if (isRequestedFriend(m, 1,3))
    {
        printf("\nheeh\n");
    }
}