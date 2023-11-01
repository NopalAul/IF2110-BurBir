#include "tree.h"
#include <stdlib.h>
#include <stdio.h>
void createTree(tree *T){
    ROOT(*T) = NULL;
}

address newNode(int id){
    address P = (address) malloc(sizeof(Node));
    if(P != NULL){
        id(P) = id;
        CHILD(P) = NULL;
        SIBLING(P) = NULL;
    }
    return P;
}
address getNodeAddress(tree T,int id){
    if(T != NULL){
        if(id(T) == id){
            return T;
        }
        else{
            address P = getNodeAddress(CHILD(T), id);
            if(P == NULL){
                P = getNodeAddress(SIBLING(T), id);
            }
            return P;
        }
    }
    else{
        return NULL;
    }
}

void addRoot(tree *T,int id){
    if(ROOT(*T) == NULL){
        ROOT(*T) = newNode(id);
    }
}

void addSibling(address n,int id){
    if(n != NULL){
        if(SIBLING(n) == NULL){
            SIBLING(n) = newNode(id);
        }
        else{
            addSibling(SIBLING(n), id);
        }
    }
}

void addChild(address node,int id){
    if(node != NULL){
        if(CHILD(node) == NULL){
            CHILD(node) = newNode(id);
        }
        else{
            addSibling(CHILD(node), id);
        }
    }
}
    
int getDepth(int id, tree T){
    if(T != NULL){
        if(id(T) == id){
            return 0;
        }
        else{
            int depth = getDepth(id, CHILD(T));
            if(depth == -1){
                depth = getDepth(id, SIBLING(T));
            }
            if(depth == -1){
                return -1;
            }
            else{
                return depth + 1;
            }
        }
    }
    else{
        return -1;
    }
}
void deleteNodeCascade(address* node){
    if(*node != NULL){
        deleteNodeCascade(&SIBLING(*node));
        deleteNodeCascade(&CHILD(*node));
        free(*node);
        *node = NULL;
    }
}

void displayNode(address node){
    if(node != NULL){
        printf("%d ", id(node));
    }
}



void traverseTree(tree T){
    address temp = T;
    if(temp==NULL){
        return;
    }
    while(temp){
        printf("\n");
        printf("%d",id(temp));
        if(CHILD(temp)){
            traverseTree(CHILD(temp));
        }
        temp = SIBLING(temp);
    }
}
int main(){
    tree T;
    createTree(&T);
    addRoot(&T, 0);
    addChild(ROOT(T), 1);
    addChild(ROOT(T), 2);
    addSibling(getNodeAddress(T,1), 3);
    addChild(getNodeAddress(T,1), 4);
    addSibling(getNodeAddress(T,2), 5);

    traverseTree(T);
    printf("\ntes");
}

// 0
// 1  2  3 5
//4 