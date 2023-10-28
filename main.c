#include <stdio.h>
#include <stdlib.h>
#include "lib/wordmachine/wordmachine.h"

STRING stop;
STRING now;

int main(){
    createString(&stop, "STOP");
    displayString(stop);
    readPassword();
    displayString(string);
    readUsername();
    displayString(string);
    readCommand();
    displayString(string);
    readBio();
    displayString(string);
    readKicauan();
    displayString(string);
    stopRead();
}