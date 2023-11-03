#include <stdio.h>
#include "draft.c"

int main(){
    Draft d;
    STRING s;
    CreateEmptyDraft(&d, 10);
    readString();
    PushDraft(&d, string);
    readString();
    PushDraft(&d, string);
    PopDraft(&d, &s);
    displayString(d.buffer[d.Top]);
    displayString(s);
}