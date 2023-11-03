#include "muat.h"

char path[113] = "../../config/";

void loadPengguna(STRING folder, ListUser *l)
{
    int N;
    STRING text;
    USER currentUser;
    char pengguna[16] = "/pengguna.config";

    for (int j = 0; j < folder.length; j++) // menambahkan input user ke dalam path
    {
        path[13+j] = folder.buffer[j];
    }
    for (int i = 0; i < 16; i++)
    {
        path[13+folder.length+i] = pengguna[i];
    }
    startFile(path);
    text.buffer[0] = currentChar;
    text.length = 1;
    N = stringToInteger(text);
    ADV();
    ignoreBlankCarriageNewline();
    readUserFromFile(&currentUser, N, l);
}

void readUserFromFile(USER *u, int jumlahUser, ListUser *l)
{
    int j;
    STRING processedString;

    for (int k = 0; k < jumlahUser; k++)
    {
        for (int i = 0; i < 7; i++)
        {
            j = 0;
            createEmptyString(&processedString);
            if (i == 6)
            {
                for (int count = 0; count < 5; count++)
                {
                    while (currentChar != NEWLINE)
                    {
                        processedString.buffer[j]= currentChar;
                        processedString.length++;
                        j++;
                        ADV();
                    }
                    if (count!=4)
                    {
                        ADV();
                    }
                }
            }
            else
            {
                while (currentChar != NEWLINE)
                {
                    processedString.buffer[j]= currentChar;
                    processedString.length++;
                    j++;
                    ADV();
                }
            }
            if (i == 0)
            {
                USERNAME(*u) = processedString;
            }
            else if (i == 1)
            {
                PASSWORD(*u) = processedString;
            }
            else if (i == 2)
            {
                BIO(*u) = processedString;
            }
            else if (i == 3)
            {
                NOHP(*u) = processedString;
            }
            else if (i == 4)
            {
                WETON(*u) = processedString;
            }
            else if (i == 5)
            {
                if (processedString.buffer[1] = 'u')
                {
                    ACCOUNTTYPE(*u) = false;
                }
                else
                {
                    ACCOUNTTYPE(*u) = true;
                }
            }
            else if (i == 6)
            {
                PHOTO(*u) = processedString;
            }
            ADV();
        }
        printf("%d", k);
        USER(*l, k) = *u;   
    }
}