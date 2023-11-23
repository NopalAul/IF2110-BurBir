#include <stdio.h>
#include "../user.h"

int main(){
    int tp;
    scanf("%d", &tp);
    switch (tp){
        case 1:
            USER u1;
            createUSER(&u1);
            printf("%d\n", USERNAME(u1).length);
            printf("%d\n", PASSWORD(u1).length);
            printf("%d\n", BIO(u1).length);
            printf("%d\n", NOHP(u1).length);
            printf("%d\n", WETON(u1).length);
            printf("%d\n", ACCOUNTTYPE(u1));
            break;
        case 2:
            createListUser();
            printf("%d\n", LENGTH(UserList));
            break;
        case 3:
            createListUser();
            STRING str;
            createString(&str, "AUTHORGOD");
            copyString(&USERNAME(USER(UserList, LENGTH(UserList))), str);
            LENGTH(UserList)++;
            displayString(USERNAME(USER(UserList, 0)));
            printf("%d\n", searchUser(str));
            break;
        case 4:
            USER x;
            createUSER(&x);
            STRING s;
            createString(&s, "AUTHORGOD");
            copyString(&USERNAME(x), s);
            createListUser();
            copyString(&USERNAME(USER(UserList, 0)), s);
            LENGTH(UserList)++;
            printf("%d\n", userID(x));
            break;
    }
}