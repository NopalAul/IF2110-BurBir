#include "muat.h"

int main ()
{
    ListFriendRequest lf;
    ListKicau lk;

    readString();
    stopRead();
    createListUser(&UserList);
    createRelationMatrix(&RelMatrix);
    createListKicau(&lk, 100);
    loadAll(string, &UserList, &RelMatrix, &lk);
    displayDataUser(USER(UserList,0));
    for (int i = 0; i < PASSWORD(USER(UserList,0)).length; i++)
    {
        printf("%c", PASSWORD(USER(UserList,0)).buffer[i]);
    }
    printf("\n");
    displayDataUser(USER(UserList,1));
    for (int i = 0; i < PASSWORD(USER(UserList,1)).length; i++)
    {
        printf("%c", PASSWORD(USER(UserList,1)).buffer[i]);
    }
    printf("\n");
    displayDataUser(USER(UserList,2));
    for (int i = 0; i < PASSWORD(USER(UserList,2)).length; i++)
    {
        printf("%c", PASSWORD(USER(UserList,2)).buffer[i]);
    }
    printf("\n");
    printMatrixRelation(RelMatrix);
    printf("\n");
    displayKicauan(lk, USER(UserList, 0));
    if (!isEmptyListRequest(REQUESTLIST(USER(UserList,3))) && !isEmptyListRequest(REQUESTLIST(USER(UserList,2))))
    {
        printf("adaan");
    }
    else
    {
        printf("gaada mas");
    }
    if (isRequestedFriend(0,2))
    {
        printf("\nhooh\n");
    }
    if (isRequestedFriend(1,3))
    {
        printf("\nheeh\n");
    }
    
}