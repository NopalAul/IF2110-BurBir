#include <stdio.h>
#include "reply.h"


int main() {
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

    displayAllBalasan(T,1);

}
