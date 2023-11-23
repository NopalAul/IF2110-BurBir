#include <stdio.h>
#include "../listRequest.h"

int main(){
    int tp;
    scanf("%d", &tp);
    ListFriendRequest l;
    createListRequest(&l);
    UserPopularity p;
    switch (tp){
        case 1:
            printf("%d\n", HeadLRF(l));
            printf("%d\n", CountLRF(l));
            printf("%d\n", isEmptyListRequest(l));
            printf("%d\n", isFullListRequest(l));
            break;
        case 2:
            p.id = 2;
            p.friendCount = 12;
            for (int i = 0; i < 19; i++){
                enqueueListRequest(&l, p);
            }
            printf("%d\n", isEmptyListRequest(l));
            printf("%d\n", isFullListRequest(l));
            break;
        case 3:
            p.id = 2;
            p.friendCount = 3;
            for (int i = 0 ; i  < 10 ; i ++){
                enqueueListRequest(&l, p);
            }
            dequeueListRequest(&l, &p);
            printf("%d %d\n", p.id, p.friendCount);
            break;
    }
}