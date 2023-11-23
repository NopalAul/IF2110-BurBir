#include <stdio.h>
#include "../relation.h"

int main(){
    int type;
    scanf("%d", &type);
    switch (type){
        case 1:
            createRelationMatrix();
            printf("%d\n", RelationLength(RelMatrix));
            RelationLength(RelMatrix) = 20;
            printMatrixRelation();
            break;
        case 2:
            createRelationMatrix();
            RelationVal(RelMatrix, 0, 1) = true;
            RelationVal(RelMatrix, 1, 0) = true;
            printf("%d\n", isFriend(0,1));
            printf("%d\n", isFriend(2,0));
            break;
        case 3:
            createRelationMatrix();
            RelationVal(RelMatrix, 0, 1) = true;
            //RelationVal(RelMatrix, 1, 0) = true;
            printf("%d\n", isRequestedFriend(0,1));
            printf("%d\n", isRequestedFriend(2,0));
            break;
        case 4:
            createRelationMatrix();
            RelationVal(RelMatrix, 0, 1) = true;
            RelationVal(RelMatrix, 1, 0) = true;
            RelationVal(RelMatrix, 0, 2) = true;
            RelationVal(RelMatrix, 2, 0) = true;
            RelationVal(RelMatrix, 0, 3) = true;
            RelationVal(RelMatrix, 3, 0) = true;
            RelationVal(RelMatrix, 0, 4) = true;
            RelationVal(RelMatrix, 4, 0) = true;
            RelationVal(RelMatrix, 0, 5) = true;
            RelationVal(RelMatrix, 5, 0) = true;
            RelationVal(RelMatrix, 0, 6) = true;
            RelationVal(RelMatrix, 6, 0) = true;
            RelationVal(RelMatrix, 0, 7) = true;
            RelationVal(RelMatrix, 7, 0) = true;
            RelationLength(RelMatrix) = 8;
            printf("%d\n", countFriend(0));
            printf("%d\n", countFriend(1));
    }
}