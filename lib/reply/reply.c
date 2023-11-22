#include <stdlib.h>
#include <stdio.h>
#include "reply.h"

AddressReply newReply(int id, STRING Text, STRING Author, DATETIME time)
{
    AddressReply p = (AddressReply)malloc(sizeof(ReplyNode));
    if (p != NULL){
        REPLYID(p) = id;
        copyString(&REPLYTEXT(p), Text);
        copyString(&REPLYAUTHOR(p), Author);
        REPLYTIME(p) = time;
        SIBLING(p) = NULL;
        CHILD(p) = NULL;
    }
    return p;
}

void CreateREPLY(REPLY* reply)
{
    firstReply(*reply) = NULL;
}

boolean isEmptyREPLY(REPLY reply)
{
    return reply == NULL;
}

void addREPLY(REPLY *r, int id, AddressReply reply, boolean *succeed)
{
    if (id == -1){
        if (isEmptyREPLY(*r)){
            firstReply(*r) = reply;
        } else {
            AddressReply p = *r;
            while (SIBLING(p) != NULL){
                p = SIBLING(p);
            }
            SIBLING(p) = reply;
        }
    } else {
        if (!isEmptyREPLY(*r) && !(*succeed)){
            if (REPLYID(*r) == id){
                AddressReply p = CHILD(*r);
                if (p == NULL){
                    CHILD(*r) = reply;
                } else {
                    while (SIBLING(p) != NULL){
                        p = SIBLING(p);
                    }
                    SIBLING(p) = reply;
                }
                *succeed = true;
            }
            else {
                addREPLY(&CHILD(*r), id, reply, succeed);
                addREPLY(&SIBLING(*r),id, reply, succeed);
            }
        }
    }
}

void deleteREPLY(REPLY *r, int id, boolean *succeed, AddressReply parent, AddressReply leftSibling)
{
    if (!isEmptyREPLY(*r) && !(*succeed)){
        if (REPLYID(*r) == id){
            if (parent == NULL && leftSibling == NULL){
                AddressReply clear = firstReply(*r);
                firstReply(*r) = SIBLING(*r);
                deleteReplyTree(&clear, 0);
            } else if (parent == NULL){
                AddressReply clear = firstReply(*r);
                SIBLING(leftSibling) = SIBLING(*r);
                deleteReplyTree(&clear,0);
            } else {
                AddressReply clear = firstReply(*r);
                CHILD(parent) = SIBLING(*r);
                deleteReplyTree(&clear,0);
            }
            *succeed = true;
        } else {
            deleteREPLY(&CHILD(*r), id, succeed, *r, NULL);
            deleteREPLY(&SIBLING(*r), id, succeed, NULL, *r);
        }
    }
}

void deleteReplyTree(REPLY *r, int depth)
{
    if (!isEmptyREPLY(*r)){
        deleteReplyTree(&CHILD(*r),depth+1);
        if (depth != 0){
            deleteReplyTree(&SIBLING(*r), depth);
        }
        free(*r);
    }
}

void displaySpecificReply(AddressReply p, int tab, boolean isPublic)
{   
    int multiplier = 5;
    printf("%*c ID = %d\n", tab*multiplier, '|', REPLYID(p));
    if (isPublic){
        printf("%*c ", tab*multiplier, '|');
        displayStringNoNewline(REPLYAUTHOR(p));
        printf("\n");
        printf("%*c ", tab*multiplier, '|');
        displayDATETIME(REPLYTIME(p));
        printf("%*c ", tab*multiplier, '|');
        displayStringNoNewline(REPLYTEXT(p));
        printf("\n\n");
    } else {
        printf("%*c PRIVAT\n", tab*multiplier, '|');
        printf("%*c PRIVAT\n", tab*multiplier, '|');
        printf("%*c PRIVAT\n\n", tab*multiplier, '|');
    }
}

void displayReply(REPLY p, int depth)
{
    if (isEmptyREPLY(p)){
    } else {
        displaySpecificReply(p, depth, true);
        displayReply(CHILD(p), depth + 1);
        displayReply(SIBLING(p), depth);
    }
}


void ReplyAuhtor(REPLY r, int id, STRING *Author)
{
    if (!isEmptyREPLY(r) && (*Author).length == 0){
        if (REPLYID(r) == id){
            copyString(Author, REPLYAUTHOR(r));
        } else {
            ReplyAuhtor(CHILD(r), id, Author);
            ReplyAuhtor(SIBLING(r), id, Author);
        }
    }
}
