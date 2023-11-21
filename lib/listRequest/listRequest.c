#include "listRequest.h"

void createListRequest(ListFriendRequest *l)
/*Melakukan proses inisialisasi kosong pada l
I.S :   l sembarang
F.S :   l.count diset 0
        l.Head = IDX_INIT*/
{
    HeadLRF(*l) = IDX_INIT;
    CountLRF(*l) = 0;
}

boolean isEmptyListRequest(ListFriendRequest l)
/*Mengirim true jika l kosong*/
{
    return CountLRF(l) == 0;
}
boolean isFullListRequest(ListFriendRequest l)
/*mengirim true jika l penuh*/
{
    return CountLRF(l) == MAX_USER_COUNT-1;
}

void enqueueListRequest(ListFriendRequest *l, UserPopularity u)
/*Melakukan proses penambahan u pada l dengan aturan terurut mengecil
I.S :   l terdefinisi boleh kosong, tidak penuh
F.S :   u ditambahkan ke dalam l dengan aturan tetap terurut mengecil */
{
    if (isEmptyListRequest(*l)){
        HeadLRF(*l) = 0;
        CountLRF(*l) = 1;
        infoLRF(*l,HeadLRF(*l)) = u;
    } else {
        // 0 0 0 0 0 5 3 1 0 0 0
        // 0 1 2 3 4 5 6 7 8 9 10
        int idx = (HeadLRF(*l)+CountLRF(*l)-1)%19;
        int end = HeadLRF(*l) - 1;
        if (end < 0){
            end = MAX_USER_COUNT-2;
        }
        while (idx != end && u.friendCount > FriendCount(*l,idx)){
            infoLRF(*l,(idx+1)%(MAX_USER_COUNT-1)) = infoLRF(*l,idx);
            idx --;
            if (idx < 0){
                idx = MAX_USER_COUNT-2;
            }
        }
        infoLRF(*l,(idx+1)%(MAX_USER_COUNT-1)) = u;
        CountLRF(*l)++;
    }
}

void dequeueListRequest(ListFriendRequest *l, UserPopularity *u)
/*Proses menghapus nilai head pada l dan dicopy ke u
I,S :   l terdefinisi tidak kosong
F.S :   head l dicopy ke dalam u dan dihapus dari l*/
{
    *u = infoLRF(*l, HeadLRF(*l));
    if (CountLRF(*l) == 1){
        HeadLRF(*l) = IDX_INIT;
    } else {
        HeadLRF(*l)++;
        if (HeadLRF(*l) >= MAX_USER_COUNT-1){
            HeadLRF(*l) = 0;
        }
    }
    CountLRF(*l)--;
}