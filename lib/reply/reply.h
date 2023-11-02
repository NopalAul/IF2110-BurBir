#ifndef REPLY_H
#define REPLY_H

#include "../boolean/boolean.h"
#include "../wordmachine/wordmachine.h"
#include "../datetime/datetime.h"


typedef struct replyNode* AddressReply;
typedef struct replyNode {
    int replyID;
    STRING text;
    STRING author;
    DATETIME currTime;
    AddressReply sibling;
    AddressReply child;
} ReplyNode;

#define REPLYID(p) (p)->replyID
#define REPLYTEXT(p) (p)->text
#define REPLYAUTHOR(p) (p)->author
#define REPLYTIME(p) (p)->currTime
#define SIBLING(p) (p)->sibling
#define CHILD(p) (p)->child

AddressReply newReply(int id, STRING Text, STRING Author, DATETIME time);

typedef AddressReply REPLY;

#define firstReply(r) (r)

void CreateREPLY(REPLY* reply);

boolean isEmptyREPLY(REPLY reply);

void addREPLY(REPLY *r, int id, AddressReply reply, boolean *succeed);
void deleteREPLY(REPLY *r, int id, boolean *succeed, AddressReply parent, AddressReply leftSibling);
void deleteReplyTree(REPLY *r, int depth);

void displaySpecificReply(AddressReply p, int tab, boolean isPublic);

void displayReply(REPLY p, int depth);

#endif