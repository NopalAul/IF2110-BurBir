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

extern RelationMatrix RelMatrix;

//selektor
#define RelationVal(r,i,j) (r).matrix[i][j]
#define RelationLength(r) (r).length


void createRelationMatrix();
/*Melakukan inisialisasi kosong pada RelatioinMatriks
I.S :   r sembarang
F.S :   r terdefinisi dengan
        r.matrix semuanya berelemen NO_RELATION
        r.length = 0*/

boolean isFriend(int id1, int id2);
/*Mengembalikan true jika kedua id1 dan id2 berteman 
definisi berteman : RelationVal(r,id1,id2) = RelationVal(r,id2,id1) = 1*/

boolean isRequestedFriend(int id1, int id2);
/*Mengembalikan true jika id1 meminta pertemanan ke id2
definisi meminta pertemanan : RelationVal(r,id1,id2) = 1 dan RelationVal(r,id2,id1) = 0*/

int countFriend(int id);
/*Mengembalikan jumlah teman yang dimiliki user dengan ID id
Prekondisi: id valid*/

void printMatrixRelation();

#endif