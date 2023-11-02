#include "tree.h"
#include <stdlib.h>
#include <stdio.h>

void createTree(tree *T){
    ROOT(*T) = NULL;
}

void createEmtptyBalasan(BALASAN *b){
    ID(*b) = IDX_UNDEF;
    USER user;
    createUSER(&user);
    USERBAL(*b) = user;
    DATETIME date;
    date = getCurrentDATETIME();
    DATE(*b) = date;
    STRING text;
    createEmptyString(&text);
    createString(&text, "tes");
    TEXT(*b) = text;
}

address newNode(BALASAN balasan){
    address P = (address) malloc(sizeof(Node));
    if(P != NULL){
        BALASAN(P) = balasan;
        CHILD(P) = NULL;
        SIBLING(P) = NULL;
    }
    return P;
}

address getNodeAddress(tree T,int id){
    if(T != NULL){
        if(ID(BALASAN(T)) == id){
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

// root adalah kicau
void addRoot(tree *T,BALASAN *b){
    if(ROOT(*T) == NULL){
        createEmtptyBalasan(b);
        ROOT(*T) = newNode(*b);
    }
}

void addSibling(address n,BALASAN b){
    if(n != NULL){
        if(SIBLING(n) == NULL){
            SIBLING(n) = newNode(b);
        }
        else{
            addSibling(SIBLING(n), b);
        }
    }
}

void addChild(address node,BALASAN b){
    if(node != NULL){
        if(CHILD(node) == NULL){
            CHILD(node) = newNode(b);
        }
        else{
            addSibling(CHILD(node), b);
        }
    }
}
    
int getDepth(int id, tree T){
    if(T != NULL){
        if(ID(BALASAN(T)) == id){
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

void displayBalasan(BALASAN b){
    printf("| ID = %d\n", ID(b));
    printf("|");
    displayString(USERNAME(USERBAL(b)));
    printf("| ");
    displayDATETIME(DATE(b));
    printf("| ");
    displayString(TEXT(b));
}

displayAllBalasan(tree T){
    // display all balasan except root, using dfs
    address temp = T;
    if(temp==NULL){
        return;
    }
    while(temp){
        printf("\n");
        if(temp!=ROOT(T)){
            displayBalasan(BALASAN(temp));
        }
        
        if(CHILD(temp)){
            displayAllBalasan(CHILD(temp));
        }
        temp = SIBLING(temp);
    }
}


// void traverseTree(tree T){
//     address temp = T;
//     if(temp==NULL){
//         return;
//     }
//     while(temp){
//         printf("\n");
//         printf("%d",id(temp));
//         if(CHILD(temp)){
//             traverseTree(CHILD(temp));
//         }
//         temp = SIBLING(temp);
//     }
// }
int main(){
    BALASAN b;
    createEmtptyBalasan(&b);
    tree T;
    T = newNode(b);
    BALASAN b1;
    createEmtptyBalasan(&b1);
    displayNode(T);
}

// 0
// 1  2  3 5
//4 