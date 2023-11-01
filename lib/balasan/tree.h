// balasan using tree

#ifndef tree_h
#define tree_h

#define IDX_UNDEF -1

typedef struct node* address;
typedef struct node{
    int id;
    struct node *child;
    struct node *sibling;
} Node;

typedef address tree;

#define ROOT(l) (l)
#define id(l) (l)->id
#define CHILD(l) (l)->child
#define SIBLING(l) (l)->sibling





void createTree(tree *T);



#endif