#include <stdio.h>
#include "lib/wordmachine/wordmachine.h"

STRING stop;

int main(){
    createString(&stop, "STOP");
    readPassword();
    while (!isStringEqual(string, stop)){
        displayString(string);
        readPassword();
    }
    stopRead();
}
