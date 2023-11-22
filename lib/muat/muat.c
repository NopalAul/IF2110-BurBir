#include "muat.h"

void loadAll(STRING folder, ListUser *l, RelationMatrix *m, ListKicau *lk)
{
    char path[113] = "../../config/";
    for (int j = 0; j < folder.length; j++) // menambahkan input user ke dalam path
    {
        path[13+j] = folder.buffer[j];
    }
    if (!isDirExist(path))
    {
        printf("Tidak ada folder yang dimaksud!");
    }
    else
    {
        loadPengguna(folder, l, m);
        loadKicau(folder, lk, *l);
    }
}

void loadPengguna(STRING folder, ListUser *l, RelationMatrix *m)
{
    char path[113] = "../../config/";
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
    LENGTH(*l) = N;
    ADV();
    ignoreBlankCarriageNewline();
    createUSER(&currentUser);
    readUserFromFile(&currentUser, N, l, m);
}

void readUserFromFile(USER *u, int jumlahUser, ListUser *l, RelationMatrix *m)
{
    int i, j, tempIdx, IDreceiver, FriendListCounter;
    STRING processedString;
    UserPopularity userP;

    // Read user
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
                        ignoreCarriage();
                        ADV();
                    }
                }
            }
            else
            {
                while (currentChar != NEWLINE)
                {
                    processedString.buffer[j] = currentChar;
                    processedString.length++;
                    j++;
                    ADV();
                    if (currentChar == CARIAGE)
                    {
                        ignoreCarriage();
                    }
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
    
    // Read matrix pertemanan
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
            ignoreBlanks();  
        }
        ignoreBlankCarriageNewline();    
    }
    createEmptyString(&processedString);
    // Read friend request
    i = 0;
    while (currentChar != '\n')
    {
        processedString.buffer[i] = currentChar;
        processedString.length++;
        i++;
        ADV();
        if (currentChar == CARIAGE)
        {
            ignoreCarriage();
        }
    }
    FriendListCounter = stringToInteger(processedString);
    ignoreNewline();

    for (int i = 0; i < FriendListCounter; i++)
    {
        ignoreNewline();
        createEmptyString(&processedString);
        tempIdx = 0;
        while (currentChar != BLANK)
        {
            processedString.buffer[tempIdx] = currentChar;
            tempIdx++;
            processedString.length++;
            ADV();
        }
        userP.id = stringToInteger(processedString);
        ignoreBlanks();
        createEmptyString(&processedString);
        tempIdx = 0;
        while (currentChar != BLANK)
        {
            processedString.buffer[tempIdx] = currentChar;
            tempIdx++;
            processedString.length++;
            ADV();
        }
        IDreceiver = stringToInteger(processedString);
        ignoreBlanks();
        createEmptyString(&processedString);
        tempIdx = 0;
        while (currentChar != NEWLINE)
        {
            processedString.buffer[tempIdx] = currentChar;
            tempIdx++;
            processedString.length++;
            ADV();
            if (currentChar == CARIAGE)
            {
                ignoreCarriage();
            }
        }
        userP.friendCount = stringToInteger(processedString);
        enqueueListRequest(&REQUESTLIST(USER(*l, IDreceiver)), userP);
    }
}

void loadKicau(STRING folder, ListKicau *l, ListUser lu)
{
    char path[113] = "../../config/";
    char kicauan[15] = "/kicauan.config";
    STRING text;
    int jumlahKicauan, textIdx, k;
    KICAU kicau;
    boolean found;
    char tempMark;

    for (int j = 0; j < folder.length; j++) // menambahkan input user ke dalam path
    {
        path[13+j] = folder.buffer[j];
    }
    for (int i = 0; i < 15; i++)
    {
        path[13+folder.length+i] = kicauan[i];
    }
    createEmptyString(&text);
    startFile(path);
    text.buffer[0] = currentChar;
    text.length = 1;
    jumlahKicauan = stringToInteger(text);
    ADV();
    ignoreBlankCarriageNewline();
    createEmptyString(&text);

    for (int i = 0; i < jumlahKicauan; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            createEmptyString(&text);
            textIdx = 0;
            if (j == 4)
            {
                for (int x = 0; x < 2; x++)
                {
                    textIdx = 0;
                    createEmptyString(&text);
                    while (currentChar != '/')
                    {
                        text.buffer[textIdx] = currentChar;
                        text.length++;
                        textIdx++;
                        ADV();
                    }
                    if (x == 0)
                    {
                        DAY(DATETIME(kicau)) = stringToInteger(text);
                    }
                    else
                    {
                        MONTH(DATETIME(kicau)) = stringToInteger(text);
                    }
                    ADV();
                }
                textIdx = 0;
                createEmptyString(&text);
                while (currentChar != BLANK)
                {
                    text.buffer[textIdx] = currentChar;
                    text.length++;
                    textIdx++;
                    ADV();
                }
                YEAR(DATETIME(kicau)) = stringToInteger(text);
                ignoreBlanks();
                for (int x = 0; x < 2; x++)
                {
                    textIdx = 0;
                    createEmptyString(&text);
                    while (currentChar != ':')
                    {
                        text.buffer[textIdx] = currentChar;
                        text.length++;
                        textIdx++;
                        ADV();
                    }
                    if (x == 0)
                    {
                        HOUR(DATETIME(kicau)) = stringToInteger(text);
                    }
                    else
                    {
                        MINUTE(DATETIME(kicau)) = stringToInteger(text);
                    }
                    ADV();
                }
                textIdx = 0;
                createEmptyString(&text);
                while (currentChar != NEWLINE)
                {
                    text.buffer[textIdx] = currentChar;
                    text.length++;
                    textIdx++;
                    ADV();
                }
                SECOND(DATETIME(kicau)) = stringToInteger(text);
                ADV();
            }
            else
            {
                while (currentChar != NEWLINE)
                {
                    text.buffer[textIdx] = currentChar;
                    text.length++;
                    textIdx++;
                    ADV();
                }
                if (j == 0)
                {
                    IDKICAUAN(kicau) = stringToInteger(text);
                }
                if (j == 1)
                {
                    TEXTKICAUAN(kicau) = text;
                }
                if (j == 2)
                {
                    LIKE(kicau) = stringToInteger(text);
                }
                if (j == 3)
                {
                    k = 0;
                    found = false;
                    while (k < LENGTH(lu) && !found)
                    {
                        if (isStringEqual(USERNAME(USER(lu, k)), text))
                        {
                            AUTHOR(kicau) = USER(lu, k);
                            found = true;
                        }
                        else
                        {
                            k++;
                        }
                    }
                }
                ADV();
            }
        }
        addKicauan(l, &kicau);
    }
}