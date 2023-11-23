#include <stdio.h>
#include "../wordmachine.h"

int main(){
    int type;
    STRING temp;
    scanf("%d", &type);
    switch (type)
    {
        case 1:
            //test createEmptyString
            createEmptyString(&string);
            printf("%d\n", string.length);
            break;
        case 2:
            //test createString
            createString(&temp, "TEST2");
            displayString(temp);
            break;
        case 3:
            //test copyString
            createString(&temp, "12/12/2023 10:10:10");
            copyString(&string, temp);
            displayString(string);
            break;
        case 4:
            //test readPassword
            do {
                readPassword();
            } while (! VALID);
            displayString(string);
            stopRead();
            break;
        case 5:
            do {
                readUsername();
            } while (! VALID);
            displayString(string);
            stopRead();
            break;
        case 6:
            readCommand();
            displayString(string);
            displayString(leftInfo);
            displayString(rightInfo);
            readCommand();
            displayString(string);
            displayString(leftInfo);
            displayString(rightInfo);
            readCommand();
            displayString(string);
            displayString(leftInfo);
            displayString(rightInfo);
            readCommand();
            displayString(string);
            displayString(leftInfo);
            displayString(rightInfo);
            stopRead();
            break;
        case 7:
            readBio();
            displayString(string);
            stopRead();
            break;
        case 8:
            readKicauan();
            displayString(string);
            stopRead();
            break;
        case 9:
            readKicauan();
            displayString(string);
            stopRead();
            break;
        case 10:
            readString();
            displayString(string);
            stopRead();
            break;
        case 11:
            readString();
            copyString(&temp, string);
            printf("%s\n", isStringSimiliar(temp, string) ? "TRUE" : "FALSE");
            createString(&temp, "TEST11");
            printf("%s\n", isStringSimiliar(temp, string) ? "TRUE" : "FALSE");
            stopRead();
            break;
        case 12:
            readString();
            copyString(&temp, string);
            printf("%s\n", isStringEqual(temp, string) ? "TRUE" : "FALSE");
            createString(&temp, "TEST12");
            printf("%s\n", isStringEqual(temp, string) ? "TRUE" : "FALSE");
            stopRead();
            break;
        case 13:
            readString();
            displayString(string);
            printf("%d\n", isStringNumeric(string));
            printf("%s\n", isStringNumeric(string) ? "TRUE" : "FALSE");
            stopRead();
            break;
        case 14:
            readString();
            displayString(string);
            printf("%s\n", isNoHPValid(string) ? "TRUE" : "FALSE");
            stopRead();
            break;
        case 15:
            readString();
            displayString(string);
            printf("%d\n", stringToInteger(string));
            stopRead();
            break;
        case 16:
            readString(); //input is "case16"
            printf("%s\n", isWordEqual(string, "case16") ? "SAMA" : "BEDA");
            stopRead();
            break;
        case 17:
            readString();
            printf("%d\n", isWordSimiliar(string, "casE17"));
            readString();
            printf("%d\n", isWordSimiliar(string, "casE17"));
            stopRead();
            break;
        case 18:
            do {
                readKicauan();
            } while (!isKicauValid());
            displayString(string);
            stopRead();
            break;
        case 19:
            do {
                readString();
            } while (!isInputValid());
            displayString(string);
            stopRead();
            break;
    }       
}