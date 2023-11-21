#include "relation.h"
#include <stdio.h>

RelationMatrix RelMatrix;

void createRelationMatrix()
/*Melakukan inisialisasi kosong pada RelatioinMatriks
I.S :   r sembarang
F.S :   r terdefinisi dengan
        r.matrix semuanya berelemen NO_RELATION
        r.length = 0*/
{
    RelationLength(RelMatrix) = 0;
    for (int i = 0; i < MAX_USER_COUNT; i++){
        for (int j = 0; j < MAX_USER_COUNT; j++){
            if (i == j){
                RelationVal(RelMatrix, i, j) = true;
            } 
            else {
                RelationVal(RelMatrix, i, j) = false;
            }
        }
    }
}

boolean isFriend(int id1, int id2)
/*Mengembalikan true jika kedua id1 dan id2 berteman 
definisi berteman : RelationVal(r,id1,id2) = RelationVal(r,id2,id1) = 1*/
{
    return RelationVal(RelMatrix, id1, id2) && RelationVal(RelMatrix, id2, id1); 
}

boolean isRequestedFriend(int id1, int id2)
/*Mengembalikan true jika id1 meminta pertemanan ke id2
definisi meminta pertemanan : RelationVal(r,id1,id2) = 1 dan RelationVal(r,id2,id1) = 0*/
{
    return RelationVal(RelMatrix, id1, id2) && !RelationVal(RelMatrix, id2, id1);
}

int countFriend(int id)
/*Mengembalikan jumlah teman yang dimiliki user dengan ID id
Prekondisi: id valid*/
{   
    int counter = 0;
    for (int i = 0; i < RelMatrix.length; i++){
        if (i != id && isFriend(id,i)){
            counter ++;
        }
    }
    return counter;
}

void printMatrixRelation()
{
    for (int i = 0; i < RelationLength(RelMatrix); i++){
        for (int j = 0 ; j < RelationLength(RelMatrix); j++){
            printf("%d ", RelationVal(RelMatrix,i,j));
        }
        printf("\n");
    }
}
