#include <stdio.h>
#include "../draft.c"

int main()
{
    StackDraft d;
    STRING sd;
    CreateEmptyDraft(&d, 2);
    readString();
    PushDraft(&d, string);
    // // printf("%d\n", IsEmptyDraft(d));
    readString();
    PushDraft(&d, string);
    // // printf("%d\n", IsFullDraft(d));
    readString();
    PushDraft(&d, string);
    readString();
    PushDraft(&d, string);
    PopDraft(&d, &sd);
    PopDraft(&d, &sd);
    PopDraft(&d, &sd);
    PopDraft(&d, &sd);
    displayTop(d);
    displayString(sd);
}