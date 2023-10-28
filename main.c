#include <stdio.h>
#include <stdlib.h>
#include "lib/wordmachine/wordmachine.h"
#include "lib/user/user.h"




int main(){
    STRING stop;
    STRING now;
    ListUser UserList;
    createListUser(&UserList);
    createEmptyString(&stop);
    createEmptyString(&now);
    displayString(PHOTO(USER(UserList,2)));
    displayDataUser(USER(UserList,0));
    // createString(&stop, "STOP");
    // displayString(stop);
    // readPassword();
    // displayString(string);
    // printf("%s\n", VALID ? "valid mas" : "ga valid mas");
    // readUsername();
    // displayString(string);
    // printf("%s\n", VALID ? "valid mas" : "ga valid mas");
    // readCommand();
    // displayString(string);
    // readBio();
    // displayString(string);
    // readPhoto();
    // printf("%s\n", VALID ? "valid mas" : "ga valid mas");
    // displayString(string);
    // readString();
    // printf("length : %d\n", string.length);
    // displayString(string);
    // readString();
    // displayString(string);
    // printf("%s\n", isStringSimiliar(string, stop) ?  "sama bang" : "beda mas");
    //stopRead();
}