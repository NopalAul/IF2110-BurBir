#include "muat.h"

char path[113] = "../../config/";

void loadPengguna(STRING folder, ListUser *l, RelationMatrix *m, ListFriendRequest *lf)
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
    createUSER(&currentUser);
    readUserFromFile(&currentUser, N, l, m,lf);
}

void readUserFromFile(USER *u, int jumlahUser, ListUser *l, RelationMatrix *m, ListFriendRequest *lf)
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
                Length(PHOTO(USER(*l, k))) = 5;
                for (int count = 0; count < 5; count++)
                {
                    for (int x = 0; x < 5; x++)
                    {
                        ColorPhoto(PhotoElmt(PHOTO(*u), count, x)) = currentChar;
                        ADV();
                        ignoreBlanks();
                        InfoPhoto(PhotoElmt(PHOTO(*u), count, x)) = currentChar;
                        ADV();
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
            if (i != 6)
            {
                ADV();
            }
        }
        USER(*l, k) = *u; 
    }
    RelationLength(*m) = jumlahUser;
    for (int i = 0; i < jumlahUser; i++)
    {
        for (int j = 0; j < jumlahUser; j++)
        {
            if (currentChar == '1')
            {
                RelationVal(*m, i, j) = true;
            }
            else
            {
                RelationVal(*m, i, j) = false;
            }
            ADV();
            ignoreBlankNewline();  
        }    
    }
    
}