#include <stdio.h>
#include <stdlib.h>
#include "lib/wordmachine/wordmachine.h"

STRING stop;
STRING now;

int main(){
    createString(&stop, "STOP");
    displayString(stop);
    // readPassword();
    // displayString(string);
    // readUsername();
    // displayString(string);
    // readCommand();
    // displayString(string);
    // readBio();
    // displayString(string);
    readPhoto();
    printf("%s\n", VALID ? "valid mas" : "ga valid mas");
    displayString(string);
    readString();
    printf("length : %d\n", string.length);
    displayString(string);
    readString();
    displayString(string);
    printf("%s\n", isStringSimiliar(string, stop) ?  "sama bang" : "beda mas");
    stopRead();
}