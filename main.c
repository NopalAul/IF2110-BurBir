#include <stdio.h>
#include <stdlib.h>
#include "lib/wordmachine/wordmachine.h"



int main(){
    STRING *stop = (STRING*)malloc(sizeof(STRING));
    STRING *now = (STRING*)malloc(sizeof(STRING));
    createString(stop, "STOP");
    displayString(*stop);
    readPassword();
    while (!isStringEqual(string, *stop)){
        displayString(string);
        readPassword();
    }
    stopRead();
    createString(now, "aasdasdasddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddd");
    displayString(*now);
}
