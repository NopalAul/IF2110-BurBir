#include "muat.h"

void loadAll(STRING folder, ListKicau *lk)
{
    char path[113] = "config/";
    for (int j = 0; j < folder.length; j++) // menambahkan input user ke dalam path
    {
        path[7+j] = folder.buffer[j];
    }
    if (!isDirExist(path))
    {
        printf("Tidak ada folder yang dimaksud!");
    }
    else
    {   
        createContainerDraft();
        createRelationMatrix();
        free((lk)->buffer);
        createListKicau(lk, MAX_CAPACITY);
        createListUser();
        loadPengguna(folder);
        loadKicau(folder, lk);
        loadDraf(folder);
        loadUtas(folder, lk);
        loadBalasan(folder,lk);
    }
}

void loadPengguna(STRING folder)
{
    char path[113] = "config/";
    int N, idx;
    STRING text;
    USER currentUser;
    char pengguna[16] = "/pengguna.config";

    for (int j = 0; j < folder.length; j++) // menambahkan input user ke dalam path
    {
        path[7+j] = folder.buffer[j];
    }
    for (int i = 0; i < 16; i++)
    {
        path[7+folder.length+i] = pengguna[i];
    }
    createEmptyString(&text);
    startFile(path);
    idx = 0;
    while (currentChar != NEWLINE)
    {
        text.buffer[idx] = currentChar;
        text.length++;
        idx++;
        ADV();
        if (currentChar == CARIAGE)
        {
            ignoreCarriage();
        }   
    }
    N = stringToInteger(text);
    LENGTH(UserList) = N;
    ADV();
    ignoreBlankCarriageNewline();
    createUSER(&currentUser);
    readUserFromFile(&currentUser, N);
}

void readUserFromFile(USER *u, int jumlahUser)
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
                Length(PHOTO(USER(UserList, k))) = 5;
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
                if (processedString.buffer[1] == 'u')
                {
                    ACCOUNTTYPE(*u) = true;
                }
                else
                {
                    ACCOUNTTYPE(*u) = false;
                }
            }
            if (i != 6)
            {
                ADV();
            }
        }
        USER(UserList, k) = *u; 
    }
    
    // Read matrix pertemanan
    RelationLength(RelMatrix) = jumlahUser;
    for (int i = 0; i < jumlahUser; i++)
    {
        for (int j = 0; j < jumlahUser; j++)
        {
            if (currentChar == '1')
            {
                RelationVal(RelMatrix, i, j) = true;
            }
            else
            {
                RelationVal(RelMatrix, i, j) = false;
            }
            ADV();
            if (currentChar == CARIAGE)
            {
                ignoreCarriage();
            }
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
    ADV();

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
        enqueueListRequest(&REQUESTLIST(USER(UserList, IDreceiver)), userP);
    }
}

void loadKicau(STRING folder, ListKicau *l)
{
    char path[113] = "config/";
    char kicauan[15] = "/kicauan.config";
    STRING text;
    int jumlahKicauan, textIdx, k;
    KICAU kicau;
    CreateREPLY(&BALASAN(kicau));
    CreateListUtas(&UTAS(kicau));
    boolean found;

    for (int j = 0; j < folder.length; j++) // menambahkan input user ke dalam path
    {
        path[7+j] = folder.buffer[j];
    }
    for (int i = 0; i < 15; i++)
    {
        path[7+folder.length+i] = kicauan[i];
    }
    createEmptyString(&text);
    startFile(path);
    textIdx = 0;
    while (currentChar != NEWLINE)
    {
        text.buffer[textIdx] = currentChar;
        text.length++;
        textIdx++;
        ADV();
        if (currentChar == CARIAGE)
        {
            ignoreCarriage();
        }
    }
    jumlahKicauan = stringToInteger(text);
    ADV();
    ignoreCarriage();
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
                    if (currentChar == CARIAGE)
                    {
                        ignoreCarriage();
                    }
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
                    if (currentChar == CARIAGE)
                    {
                        ignoreCarriage();
                    }
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
                    while (k < LENGTH(UserList) && !found)
                    {
                        if (isStringEqual(USERNAME(USER(UserList, k)), text))
                        {
                            AUTHOR(kicau) = USER(UserList, k);
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

void loadBalasan(STRING folder, ListKicau *lk)
{
    char path[113] = "config/";
    char balasan[15] = "/balasan.config";
    STRING text, textBalasan, authorReply;
    int jumlahBalasan, idxText, IDKicau, jumlahReply, IDParent, IDReply;
    AddressReply rep;
    DATETIME replyDate;
    boolean succeed;

    for (int j = 0; j < folder.length; j++) // menambahkan input user ke dalam path
    {
        path[7+j] = folder.buffer[j];
    }
    for (int i = 0; i < 15; i++)
    {
        path[7+folder.length+i] = balasan[i];
    } 
    createEmptyString(&text);
    startFile(path);
    idxText = 0;
    while (currentChar != NEWLINE)      // jumlah balasan
    {
        text.buffer[idxText] = currentChar;
        text.length++;
        idxText++;
        ADV();
        if (currentChar == CARIAGE)
        {
            ignoreCarriage();
        }   
    }
    jumlahBalasan = stringToInteger(text);
    ADV();
    ignoreCarriage();
    
    for (int i = 0; i < jumlahBalasan; i++)
    {
        createEmptyString(&text);
        idxText = 0;
        while (currentChar != NEWLINE)      // ID KICAUAN
        {
            text.buffer[idxText] = currentChar;
            text.length++;
            idxText++;
            ADV();
            if (currentChar == CARIAGE)
            {
                ignoreCarriage();
            }   
        }
        ignoreNewline();
        IDKicau = stringToInteger(text);
        idxText = 0;
        createEmptyString(&text);
        while (currentChar != NEWLINE)      // jumlah reply
        {
            text.buffer[idxText] = currentChar;
            text.length++;
            idxText++;
            ADV();
            if (currentChar == CARIAGE)
            {
                ignoreCarriage();
            }   
        }
        ignoreNewline();
        jumlahReply = stringToInteger(text);

        for (int j = 0; j < jumlahReply; j++)   // loop buat semua reply
        {
            idxText = 0;
            createEmptyString(&text);
            while (currentChar != BLANK)        // ID parent reply
            {
                text.buffer[idxText] = currentChar;
                text.length++;
                idxText++;
                ADV();
            }
            ignoreBlanks();
            IDParent = stringToInteger(text);
            idxText = 0;
            createEmptyString(&text);
            while (currentChar != NEWLINE)      // ID reply
            {
                text.buffer[idxText] = currentChar;
                text.length++;
                idxText++;
                ADV();
                if (currentChar == CARIAGE)
                {
                    ignoreCarriage();
                }   
            }
            ignoreNewline();
            IDReply = stringToInteger(text);
            idxText = 0;
            createEmptyString(&text);
            while (currentChar != NEWLINE)      // text reply
            {
                text.buffer[idxText] = currentChar;
                text.length++;
                idxText++;
                ADV();
                if (currentChar == CARIAGE)
                {
                    ignoreCarriage();
                }   
            }
            ignoreNewline();
            createEmptyString(&textBalasan);
            textBalasan = text;
            idxText = 0;
            createEmptyString(&text);
            while (currentChar != NEWLINE)      // author reply
            {
                text.buffer[idxText] = currentChar;
                text.length++;
                idxText++;
                ADV();
                if (currentChar == CARIAGE)
                {
                    ignoreCarriage();
                }   
            }
            ignoreNewline();
            createEmptyString(&authorReply);
            authorReply = text;

            idxText = 0;
            createEmptyString(&text);
            createDATETIME(&replyDate);
            for (int x = 0; x < 2; x++)     // reply datetime
            {
                idxText = 0;
                createEmptyString(&text);
                while (currentChar != '/')
                {
                    text.buffer[idxText] = currentChar;
                    text.length++;
                    idxText++;
                    ADV();
                }
                if (x == 0)
                {
                    DAY(replyDate) = stringToInteger(text);
                }
                else
                {
                    MONTH(replyDate) = stringToInteger(text);
                }
                ADV();
            }
            idxText = 0;
            createEmptyString(&text);
            while (currentChar != BLANK)
            {
                text.buffer[idxText] = currentChar;
                text.length++;
                idxText++;
                ADV();
            }
            YEAR(replyDate) = stringToInteger(text);
            ignoreBlanks();
            for (int x = 0; x < 2; x++)
            {
                idxText = 0;
                createEmptyString(&text);
                while (currentChar != ':')
                {
                    text.buffer[idxText] = currentChar;
                    text.length++;
                    idxText++;
                    ADV();
                }
                if (x == 0)
                {
                    HOUR(replyDate) = stringToInteger(text);
                }
                else
                {
                    MINUTE(replyDate) = stringToInteger(text);
                }
                ADV();
            }
            idxText = 0;
            createEmptyString(&text);
            while (currentChar != NEWLINE)
            {
                text.buffer[idxText] = currentChar;
                text.length++;
                idxText++;
                ADV();
            }
            SECOND(replyDate) = stringToInteger(text);
            ADV();
            succeed = false;
            rep = newReply(IDReply, textBalasan, authorReply, replyDate);
            addREPLY(&BALASAN(KICAU(*lk,IDKicau-1)), IDParent, rep, &succeed);
        } 
    }   
}

void loadDraf(STRING folder)
{
    char path[113] = "config/";
    char draf[12] = "/draf.config";
    STRING text, ownerUsername, drafCount, isiDraft;
    int  idxText, draftOwner, idxCount, banyakDraftperUser, userIdx, len;
    DATETIME draftDate;
    AddressDraft val;
    Draft tempDraft;

    for (int j = 0; j < folder.length; j++) // menambahkan input user ke dalam path
    {
        path[7+j] = folder.buffer[j];
    }
    for (int i = 0; i < 12; i++)
    {
        path[7+folder.length+i] = draf[i];
    } 
    createEmptyString(&text);
    startFile(path);
    idxText = 0;
    while (currentChar != NEWLINE)      // jumlah user yang punya draf
    {
        text.buffer[idxText] = currentChar;
        text.length++;
        idxText++;
        ADV();
        if (currentChar == CARIAGE)
        {
            ignoreCarriage();
        }   
    }
    draftOwner = stringToInteger(text);
    ADV();
    for (int i = 0; i < draftOwner; i++)
    {
        createEmptyString(&text);
        idxText = 0;
        while (currentChar != NEWLINE)      // baca line yang berisi username dan banyaknya draft yang dimiliki
        {
            text.buffer[idxText] = currentChar;
            text.length++;
            idxText++;
            ADV();
            if (currentChar == CARIAGE)
            {
                ignoreCarriage();
            }   
        }
        ADV();
        idxCount = text.length-1;
        while (text.buffer[idxCount] != BLANK)
        {
            idxCount--;     // dapet index blank antara username dan jumlah draf
        }
        createEmptyString(&ownerUsername);
        createEmptyString(&drafCount);
        for (int j = 0; j < idxCount; j++)
        {
            ownerUsername.buffer[j] = text.buffer[j];
            ownerUsername.length++;        
        }
        userIdx = searchUser(ownerUsername);
        for (int j = idxCount+1; j < text.length; j++)
        {
            drafCount.buffer[j-idxCount-1] = text.buffer[j];
            drafCount.length++;
        }
        banyakDraftperUser = stringToInteger(drafCount);
        createDraft(&tempDraft);
        for (int j = 0; j < banyakDraftperUser; j++)    // baca seluruh draft milik user
        {
            createEmptyString(&text);
            idxText = 0;
            while (currentChar != NEWLINE)      // baca isi draf
            {
                text.buffer[idxText] = currentChar;
                text.length++;
                idxText++;
                ADV();
                if (currentChar == CARIAGE)
                {
                    ignoreCarriage();
                }   
            }
            isiDraft = text;
            ADV();

            for (int x = 0; x < 2; x++)     // draft datetime
            {
                idxText = 0;
                createEmptyString(&text);
                while (currentChar != '/')
                {
                    text.buffer[idxText] = currentChar;
                    text.length++;
                    idxText++;
                    ADV();
                }
                if (x == 0)
                {
                    DAY(draftDate) = stringToInteger(text);
                }
                else
                {
                    MONTH(draftDate) = stringToInteger(text);
                }
                ADV();
            }
            idxText = 0;
            createEmptyString(&text);
            while (currentChar != BLANK)
            {
                text.buffer[idxText] = currentChar;
                text.length++;
                idxText++;
                ADV();
            }
            YEAR(draftDate) = stringToInteger(text);
            ignoreBlanks();
            for (int x = 0; x < 2; x++)
            {
                idxText = 0;
                createEmptyString(&text);
                while (currentChar != ':')
                {
                    text.buffer[idxText] = currentChar;
                    text.length++;
                    idxText++;
                    ADV();
                }
                if (x == 0)
                {
                    HOUR(draftDate) = stringToInteger(text);
                }
                else
                {
                    MINUTE(draftDate) = stringToInteger(text);
                }
                ADV();
            }
            idxText = 0;
            createEmptyString(&text);
            while (currentChar != NEWLINE)
            {
                text.buffer[idxText] = currentChar;
                text.length++;
                idxText++;
                ADV();
            }
            
            SECOND(draftDate) = stringToInteger(text);
            pushDraft(&tempDraft, isiDraft);
            TIMEDRAFT(TOPDRAFT(tempDraft)) = draftDate;
            ADV();
        }
        len = lengthDraft(tempDraft);
        for (int j = 0; j < len; j++)
        {
            popDraft(&tempDraft, &val);
            pushDraft(&ContainerDraft[userIdx], CONTENTDRAFT(val));
            TIMEDRAFT(TOPDRAFT(ContainerDraft[userIdx])) = TIMEDRAFT(val);
        } 
    }
}

void loadUtas(STRING folder, ListKicau *lk)
{
    char path[113] = "config/";
    char utas[12] = "/utas.config";
    STRING text;
    int idxText, jumlahUtas, idxKicau, jumlahUtasperKicauan, idUtas = 1;
    Address p;
    DATETIME utasDate;

    for (int j = 0; j < folder.length; j++) // menambahkan input user ke dalam path
    {
        path[7+j] = folder.buffer[j];
    }
    for (int i = 0; i < 12; i++)
    {
        path[7+folder.length+i] = utas[i];
    } 
    createEmptyString(&text);
    startFile(path);
    idxText = 0;
    while (currentChar != NEWLINE)      // jumlah kicauan yang memiliki utas
    {
        text.buffer[idxText] = currentChar;
        text.length++;
        idxText++;
        ADV();
        if (currentChar == CARIAGE)
        {
            ignoreCarriage();
        }   
    }
    jumlahUtas = stringToInteger(text);
    ADV();
    for (int i = 0; i < jumlahUtas; i++)
    {
        createEmptyString(&text);
        idxText = 0;
        while (currentChar != NEWLINE)      // ID Kicauan
        {
            text.buffer[idxText] = currentChar;
            text.length++;
            idxText++;
            ADV();
            if (currentChar == CARIAGE)
            {
                ignoreCarriage();
            }   
        }
        idxKicau = stringToInteger(text);
        ADV();
        createEmptyString(&text);
        idxText = 0;
        while (currentChar != NEWLINE)      // jumlah utas per kicauan
        {
            text.buffer[idxText] = currentChar;
            text.length++;
            idxText++;
            ADV();
            if (currentChar == CARIAGE)
            {
                ignoreCarriage();
            }   
        }
        ADV();
        jumlahUtasperKicauan = stringToInteger(text);
        IDUTAS(UTAS(KICAU(*lk, idxKicau-1))) = idUtas;
        for (int j = 0; j < jumlahUtasperKicauan; j++)
        {
            createEmptyString(&text);
            idxText = 0;
            while (currentChar != NEWLINE)      // baca utas
            {
                text.buffer[idxText] = currentChar;
                text.length++;
                idxText++;
                ADV();
                if (currentChar == CARIAGE)
                {
                    ignoreCarriage();
                }   
            }
            ADV();
            insertLast(&UTAS(KICAU(*lk, idxKicau-1)), idUtas, AUTHOR(KICAU(*lk, idxKicau-1)), text);
            p = getLast(UTAS(KICAU(*lk, idxKicau-1)));
            createEmptyString(&text);
            idxText = 0;
            while (currentChar != NEWLINE)      // baca author utas
            {
                text.buffer[idxText] = currentChar;
                text.length++;
                idxText++;
                ADV();
                if (currentChar == CARIAGE)
                {
                    ignoreCarriage();
                }   
            }
            USERNAME(AUTHORUTAS(p)) = text;
            ADV();
            createDATETIME(&utasDate);
            for (int x = 0; x < 2; x++)     // utas datetime
            {
                idxText = 0;
                createEmptyString(&text);
                while (currentChar != '/')
                {
                    text.buffer[idxText] = currentChar;
                    text.length++;
                    idxText++;
                    ADV();
                }
                if (x == 0)
                {
                    DAY(utasDate) = stringToInteger(text);
                }
                else
                {
                    MONTH(utasDate) = stringToInteger(text);
                }
                ADV();
            }
            idxText = 0;
            createEmptyString(&text);
            while (currentChar != BLANK)
            {
                text.buffer[idxText] = currentChar;
                text.length++;
                idxText++;
                ADV();
            }
            YEAR(utasDate) = stringToInteger(text);
            ignoreBlanks();
            for (int x = 0; x < 2; x++)
            {
                idxText = 0;
                createEmptyString(&text);
                while (currentChar != ':')
                {
                    text.buffer[idxText] = currentChar;
                    text.length++;
                    idxText++;
                    ADV();
                }
                if (x == 0)
                {
                    HOUR(utasDate) = stringToInteger(text);
                }
                else
                {
                    MINUTE(utasDate) = stringToInteger(text);
                }
                ADV();
            }
            idxText = 0;
            createEmptyString(&text);
            while (currentChar != NEWLINE)
            {
                text.buffer[idxText] = currentChar;
                text.length++;
                idxText++;
                ADV();
            }
            SECOND(utasDate) = stringToInteger(text);
            DATETIMEUTAS(p) = utasDate;
            ADV();
        }
        idUtas++;
    }
}