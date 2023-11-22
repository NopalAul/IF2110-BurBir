#include <stdio.h>
#include "../draft.c"

int main()
{
    StackDraft d;
    STRING sd;
    CreateEmptyDraft(&d, 2);
    readString();
    printf("%d", isLihatDrafCommandValid(string));
    // PushDraft(&d, string);
    // // // printf("%d\n", IsEmptyDraft(d));
    // readString();
    // PushDraft(&d, string);
    // // // printf("%d\n", IsFullDraft(d));
    // readString();
    // PushDraft(&d, string);
    // readString();
    // PushDraft(&d, string);
    // readString();
    // PushDraft(&d, string);
    // displayTop(d);
    // printf("%d", d.capacity);
}