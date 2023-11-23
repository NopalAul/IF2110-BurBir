#ifndef listrequest_h
#define listrequest_h

#include "../boolean/boolean.h"
#include "../relation/relation.h"

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
#define IDHead(l) (l).listRequest[(l).Head].id
#define FriendCountHead(l) (l).listRequest[(l).Head].friendCount
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