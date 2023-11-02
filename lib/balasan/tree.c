#include "tree.h"
#include <stdlib.h>
#include <stdio.h>

void createTree(tree *T){
    (*T) = (tree) malloc(sizeof(Node));
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

void createTesBalasan(BALASAN *b,int id){
    ID(*b) = id;
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


// JANGAN LUPA IMPLEMEN KALAU POINTEE = address di KICAU

address getPointee(tree T,address node){
    if(T!=NULL){
        if(SIBLING(T)|| CHILD(T) == node){
            return T;
        }
        else{
            address P = getPointee(CHILD(T),node);
            if(P == NULL){
                P = getPointee(SIBLING(T),node);
            }
            return P;
        }
    }
    else{
        return NULL;
    }
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

// root adalah kicau MASIH NEED FIX
void addRoot(tree *T,BALASAN *b){
    if(ROOT(*T) == NULL){
        createEmtptyBalasan(b);
        ROOT(*T) = newNode(*b);
    }
}

void addSibling(address n,BALASAN b,address *val){
    if(n != NULL){
        if(SIBLING(n) == NULL){
            SIBLING(n) = newNode(b);
            *val = SIBLING(n);
        }
        else{
            addSibling(SIBLING(n), b, val);
        }
    }
}

void addChild(address node,BALASAN b,address *val){
    if(node != NULL){
        if(CHILD(node) == NULL){
            CHILD(node) = newNode(b);
            *val = CHILD(node);
        }
        else{
            addSibling(CHILD(node), b, val);
        }
    }
}
    


void addSpaceTab(int depth){
    for(int i = 0; i < depth; i++){
        printf("   ");
    }
}


void displayBalasan(BALASAN b,int depth){
    addSpaceTab(depth);printf("| ID = %d\n", ID(b));
    addSpaceTab(depth);printf("|");
    displayString(USERNAME(USERBAL(b)));
    addSpaceTab(depth);printf("| ");
    displayDATETIME(DATE(b));
    addSpaceTab(depth);printf("| ");
    displayString(TEXT(b));
}

void displayAllBalasan(tree T,int depth){
    address temp = T;
    if(temp==NULL){
        return;
    }
    while(temp){
        printf("\n");
        // if(temp!=ROOT(T)){
            displayBalasan(BALASAN(temp),depth);
        // }
        
        if(CHILD(temp)){
    
            displayAllBalasan(CHILD(temp),depth + 1);
        }
        
        temp = SIBLING(temp);
    }
}


void deleteAllChild(address node){
    if((node)==NULL){
        return;
    }
    deleteAllChild(CHILD(node));

    deleteAllChild(SIBLING(node));
    
    CHILD(node) = NULL;

}

void cascadeDelete(tree T, address node){
    address pointee = getPointee(T,node);
    address newPoint = SIBLING(node);

    if(SIBLING(pointee)==node){
        SIBLING(pointee) = newPoint;
    }
    else if(CHILD(pointee)==node){
        CHILD(pointee) = newPoint;
    }


    deleteAllChild(node);
   
}

void tambahBalasan(tree *T,BALASAN b,int idbalasan){
    address target = getNodeAddress((*T),idbalasan);
    address temp;
    addChild(target,b,&temp);
}

void hapusBalasan(tree *T,int idbalasan){
    address target = getNodeAddress((*T),idbalasan);
    if(target==(*T)){
        deleteAllChild(target);
        (*T) = SIBLING(*T);

    }
    else{

        cascadeDelete(*T,target);
    }
}

int main(){
    BALASAN b;
    address temp;
    createTesBalasan(&b,1);
    tree T;
    createTree(&T);
    T = newNode(b);
    BALASAN b1;
    createTesBalasan(&b1,2);
    address a1;
    a1 = newNode(b1);
    addSibling(T,b1,&temp);
    BALASAN b2;
    createTesBalasan(&b2,3);
    address a2;
    a2 = newNode(b2);
    addChild(T,b2,&temp);
    BALASAN b3;
    createTesBalasan(&b3,4);
    address a3;
    addChild(temp,b3,&temp);
    // deleteAllChild(getNodeAddress(T,3));
    createTesBalasan(&b3,5);
    addChild(getNodeAddress(T,3),b3,&temp);
    createTesBalasan(&b3,6);
    addSibling(getNodeAddress(T,3),b3,&temp);
    createTesBalasan(&b3,7);
    addSibling(getNodeAddress(T,3),b3,&temp);
    hapusBalasan(&T,1);
    
    // BALASAN b2;
    // createEmtptyBalasan(&b2);
    // addChild(T,b2,&temp);
    // BALASAN b3;
    // createEmtptyBalasan(&b3);
    // addChild(T,get)
    displayAllBalasan(T,1);
    // displayBalasan(BALASAN(a1),1);
}

// 0
// 1  2  3 5
//4 