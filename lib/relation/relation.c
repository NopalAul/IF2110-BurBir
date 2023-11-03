#include "relation.h"
#include <stdio.h>

void createRelationMatrix(RelationMatrix *r)
/*Melakukan inisialisasi kosong pada RelatioinMatriks
I.S :   r sembarang
F.S :   r terdefinisi dengan
        r.matrix semuanya berelemen NO_RELATION
        r.length = 0*/
{
    RelationLength(*r) = 0;
    for (int i = 0; i < MAX_USER_COUNT; i++){
        for (int j = 0; j < MAX_USER_COUNT; j++){
            if (i == j){
                RelationVal(*r, i, j) = true;
            } 
            else {
                RelationVal(*r, i, j) = false;
            }
        }
    }
}

boolean isFriend(RelationMatrix r, int id1, int id2)
/*Mengembalikan true jika kedua id1 dan id2 berteman 
definisi berteman : RelationVal(r,id1,id2) = RelationVal(r,id2,id1) = 1*/
{
    return RelationVal(r, id1, id2) == true && RelationVal(r, id2, id1) == true; 
}

boolean isRequestedFriend(RelationMatrix r, int id1, int id2)
/*Mengembalikan true jika id1 meminta pertemanan ke id2
definisi meminta pertemanan : RelationVal(r,id1,id2) = 1 dan RelationVal(r,id2,id1) = 0*/
{
    return RelationVal(r, id1, id2) == true && RelationVal(r, id2, id1) == false;
}

int countFriend(RelationMatrix r, int id)
/*Mengembalikan jumlah teman yang dimiliki user dengan ID id
Prekondisi: id valid*/
{   
    int counter = 0;
    for (int i = 0; i < r.length; i++){
        if (i != id && isFriend(r,id,i)){
            counter ++;
        }
    }
    return counter;
}

void printMatrixRelation(RelationMatrix r)
{
    for (int i = 0; i < RelationLength(r); i++){
        for (int j = 0 ; j < RelationLength(r); j++){
            printf("%d ", RelationVal(r,i,j));
        }
        printf("\n");
    }
}

//
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