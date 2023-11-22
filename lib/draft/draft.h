#ifndef draft_h
#define draft_h

#include "../boolean/boolean.h"
#include "../datetime/datetime.h"
#include "../wordmachine/wordmachine.h"
#include "../user/user.h"
#include "../kicauan/kicauan.h"


typedef struct draftNode* AddressDraft;
typedef struct draftNode{
    STRING content;
    DATETIME datetime;
    AddressDraft next;
} DraftNode;

#define CONTENTDRAFT(D) (D)->content
#define TIMEDRAFT(D) (D)->datetime
#define NEXTDRAFT(D) (D)->next

AddressDraft newDraft(STRING content);

typedef AddressDraft Draft;

#define TOPDRAFT(D) (D)

void createDraft(Draft * draft);
boolean isEmptyDraft(Draft draft);

void pushDraft(Draft *draft,  STRING content);
void popDraft(Draft *draft, AddressDraft *outDraft);

void displayDraft(Draft draft);

extern Draft ContainerDraft[20];

void createContainerDraft();

void BUAT_DRAFT(int currentID, ListKicau *lk);
void LIHAT_DRAFT(int currentID, ListKicau *lk);

#endif