// balasan using tree

#ifndef tree_h
#define tree_h

#define IDX_UNDEF -1

#include "../datetime/datetime.h"
#include "../charmachine/charmachine.h"
#include "../user/user.h"



typedef struct{
    int id;
    USER user;
    DATETIME date;
    STRING text;

}BALASAN;

typedef struct node{
    BALASAN balasan;
    struct node *child;
    struct node *sibling;
} Node;

typedef struct node *address;
typedef address tree;

#define ROOT(l) (l)
#define BALASAN(l) (l)->balasan
#define CHILD(l) (l)->child
#define SIBLING(l) (l)->sibling

#define ID(l) (l).id
#define USERBAL(l) (l).user
#define DATE(l) (l).date
#define TEXT(l) (l).text


void createTree(tree *T);


#endif