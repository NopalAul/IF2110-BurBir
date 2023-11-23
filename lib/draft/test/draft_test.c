#include <stdio.h>
#include <stdlib.h>
#include "../draft.h"

int main(){
    STRING content;
    int type;
    scanf("%d", &type);
    switch (type)
    {
        case 1:
            // create stack draft
            Draft ContainerDraft1[1];
            createDraft(&ContainerDraft1[0]);
            if (isEmptyDraft(ContainerDraft1[0]))
                printf("%d",1);
            else
                printf("%d",0);
            break;
        case 2:
            // push stack draft
            Draft ContainerDraft2[1];
            createDraft(&ContainerDraft2[0]);
            createString(&content, "tes");
            pushDraft(&ContainerDraft2[0],content);
            displayString(CONTENTDRAFT(ContainerDraft2[0]));
            break;
        case 3:
            // pop stack draft
            Draft ContainerDraft3[1];
            createDraft(&ContainerDraft3[0]);
            createString(&content, "tes");
            pushDraft(&ContainerDraft3[0],content);
            createString(&content, "tes2");
            pushDraft(&ContainerDraft3[0],content);
            displayString(CONTENTDRAFT(ContainerDraft3[0]));
            AddressDraft temp;
            popDraft(&ContainerDraft3[0], &temp);
            free(temp);
            displayString(CONTENTDRAFT(ContainerDraft3[0]));
            break;
    }
}