#ifndef relation_H
#define relation_H

#include "../boolean/boolean.h"

#define MAX_USER_COUNT 20
#define NO_RELATION 0
#define IDX_INIT -1

typedef struct {
    boolean matrix[MAX_USER_COUNT][MAX_USER_COUNT]; //menyimpan matriks relasi pertemanan setiap user.
    int length;     //menyimpan jumlah user yang sudah terdaftar saat ini.

} RelationMatrix;

//selektor
#define RelationVal(r,i,j) (r).matrix[i][j]
#define RelationLength(r) (r).length


void createRelationMatrix(RelationMatrix *r);
/*Melakukan inisialisasi kosong pada RelatioinMatriks
I.S :   r sembarang
F.S :   r terdefinisi dengan
        r.matrix semuanya berelemen NO_RELATION
        r.length = 0*/

boolean isFriend(RelationMatrix r, int id1, int id2);
/*Mengembalikan true jika kedua id1 dan id2 berteman 
definisi berteman : RelationVal(r,id1,id2) = RelationVal(r,id2,id1) = 1*/

boolean isRequestedFriend(RelationMatrix r, int id1, int id2);
/*Mengembalikan true jika id1 meminta pertemanan ke id2
definisi meminta pertemanan : RelationVal(r,id1,id2) = 1 dan RelationVal(r,id2,id1) = 0*/

int countFriend(RelationMatrix r, int id);
/*Mengembalikan jumlah teman yang dimiliki user dengan ID id
Prekondisi: id valid*/

typedef struct {
    int id;         //menyimpan id user yang meminta pertemanan
    int friendCount; //menyimpan jumlah teman user
} UserPopularity;   //infotype untuk ListFriendRequest


typedef struct {
    UserPopularity listRequest[19]; //menyimpan data user permintaan pertemanan
    int Head;           //index di mana head berada
    int count;          //counter jumlah request
} ListFriendRequest;    //modofikasi PrioQueue Circular

//selektor
#define IDUser(l,i) (l).listRequest[i].id
#define FriendCount(l,i) (l).listRequest[i].friendCount
#define infoLRF(l,i) (l).listRequest[i]
#define HeadLRF(l) (l).Head
#define CountLRF(l) (l).count

void createListRequest(ListFriendRequest *l);
/*Melakukan proses inisialisasi kosong pada l
I.S :   l sembarang
F.S :   l.count diset 0
        l.Head = IDX_INIT*/

boolean isEmptyListRequest(ListFriendRequest l);
/*Mengirim true jika l kosong*/
boolean isFullListRequest(ListFriendRequest l);
/*mengirim true jika l penuh*/

void enqueueListRequest(ListFriendRequest *l, UserPopularity u);
/*Melakukan proses penambahan u pada l dengan aturan terurut mengecil
I.S :   l terdefinisi boleh kosong, tidak penuh
F.S :   u ditambahkan ke dalam l dengan aturan tetap terurut mengecil */

void dequeueListRequest(ListFriendRequest *l, UserPopularity *u);
/*Proses menghapus nilai head pada l dan dicopy ke u
I,S :   l terdefinisi tidak kosong
F.S :   head l dicopy ke dalam u dan dihapus dari l*/

#endif