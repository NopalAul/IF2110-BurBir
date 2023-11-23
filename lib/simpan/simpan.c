#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "simpan.h"
#include "../wordmachine/wordmachine.h"

void saveAll(STRING folder, ListUser l, RelationMatrix m, ListKicau lk)
/*  Melakukan penyimpanan data ke dalam folder config
I.S : keberadaan folder dan file di dalamnya sembarang
F.S : folder terbentuk dan berisi file config 
      yang menyimpan data program */
{
    char path[113] = "config/";     // path untuk folder config
    int pathLen = 7;  

    pathLen += folder.length;
    
    for (int j = 0; j < string.length; j++) // menambahkan input user ke dalam path
    {
        path[7+j] = string.buffer[j];
    }
    
    if (!isDirExist(path))
    {
        printf("\nBelum terdapat %s. Akan dilakukan pembuatan %s terlebih dahulu.\n", string.buffer, string.buffer);
        printf("\nMohon tunggu...\n");
        printf("1...\n");
        printf("2...\n");
        int result = mkdir(path, 0777);
        printf("3...\n");

        if(!result){
            printf("\n%s sudah berhasil dibuat.\n", string.buffer); 
        }
        else{
            printf("Pembuatan folder gagal.\n");
        }
    }   
    printf("\nAnda akan melakukan penyimpanan di %s.\n", string.buffer);
    printf("\nMohon tunggu...\n");
    printf("1...\n");
    printf("2...\n");
    printf("3...\n");
    savePengguna(path, pathLen, l, m);
    saveKicauan(path, pathLen, lk);
    saveBalasan(path, pathLen, lk);
    saveDraf(path, pathLen);
    saveUtas(path, pathLen, lk);
    printf("\nPenyimpanan telah berhasil dilakukan!\n");
}


void savePengguna(char path[], int len, ListUser LU, RelationMatrix m)
/*  Melakukan proses penyimpanan data pengguna ke dalam folder config
I.S : folder ada dan file pengguna.config di dalamnya sembarang
F.S : file pengguna.config tersimpan dalam folder config */
{
    int length = len, FriendReqCount = 0;
    UserPopularity val;
    char configName[17] = "/pengguna.config";
    ListFriendRequest tempReq;

    for (int i = 0; i < 17; i++)    // Mengatur ulang path dari folder yang di-input oleh user
    {
        path[length] = configName[i];
        length++;
    }

    FILE* user = fopen(path, "w");

    // Save jumlah pengguna
    fprintf(user,"%d\n", LENGTH(LU));

    // Save data pengguna
    for (int i = 0; i < LENGTH(LU); i++)
    {
        fprintf(user, "%s\n", USERNAME(USER(LU,i)).buffer);
        fprintf(user, "%s\n", PASSWORD(USER(LU,i)).buffer);
        if (LENGTH(BIO(USER(LU,i))) == 0 )
        {
            fprintf(user, "\n");
        }
        else
        {
            fprintf(user, "%s\n", BIO(USER(LU,i)).buffer);
        }
        if (LENGTH(NOHP(USER(LU,i))) == 0 )
        {
            fprintf(user, "\n");
        }
        else
        {
            fprintf(user, "%s\n", NOHP(USER(LU,i)).buffer);
        }
        if (LENGTH(WETON(USER(LU,i))) == 0 )
        {
            fprintf(user, "\n");
        }
        else
        {
            fprintf(user, "%s\n", WETON(USER(LU,i)).buffer);
        }
        if (ACCOUNTTYPE(USER(LU,i)))
        {
            fprintf(user, "%s\n", "Publik");
        }
        else
        {
            fprintf(user, "%s\n", "Privat");
        }
        // Matrix foto
        for (int q = 0; q < 5; q++)
        {
            for (int j = 0; j < 5; j++)
            {
                fprintf(user, "%c ", PhotoElmt(PHOTO(USER(LU,i)), i, j).color);
                fprintf(user, "%c", PhotoElmt(PHOTO(USER(LU,i)), i, j).info);
                if (j != 4)
                {
                    fprintf(user, " ");
                }
            }
            fprintf(user, "\n");
        }
    }

    // Save matrix pertemanan
    for (int i = 0; i < RelationLength(m); i++)
    {
        for (int j = 0; j < RelationLength(m); j++)
        {
            if (RelationVal(m, i, j))
            {
                fprintf(user, "1");
            }
            else
            {
                fprintf(user, "0");
            }
            if (j != RelationLength(m)-1)
            {
                fprintf(user, " ");
            }
            else
            {
                fprintf(user, "\n");
            }
        } 
    }

    // Save jumlah permintaan berteman
    for (int i = 0; i < LENGTH(LU); i++)
    {
        FriendReqCount += CountLRF(REQUESTLIST(USER(LU,i)));
    }
    if (FriendReqCount == 0)
    {
        fprintf(user, "0\n");
    }
    else
    {
        fprintf(user, "%d\n", FriendReqCount);
    }

    // Save permintaan berteman dari seluruh user
    for (int i = 0; i < LENGTH(LU); i++)
    {
        createListRequest(&tempReq);
        for (int j = 0; j < CountLRF(REQUESTLIST(USER(LU,i))); j++)
        {
            dequeueListRequest(&REQUESTLIST(USER(LU,i)), &val);
            fprintf(user, "%d ", val.id);
            fprintf(user, "%d ", i);
            fprintf(user, "%d\n", val.friendCount);
            enqueueListRequest(&tempReq, val);
        }
        CountLRF(tempReq) = CountLRF(REQUESTLIST(USER(LU,i)));
        REQUESTLIST(USER(LU,i)) = tempReq;
    }

    
    fclose(user);
}

void saveKicauan(char path[], int len, ListKicau l)
/*  Melakukan proses penyimpanan data kicauan ke dalam folder config
I.S : folder ada dan file kicauan.config di dalamnya sembarang
F.S : file kicauan.config tersimpan dalam folder config */
{
    int length = len;
    char configName[16] = "/kicauan.config";
    for (int i = 0; i < 16; i++)
    {
        path[length] = configName[i];
        length++;
    }
    FILE* kicau = fopen(path, "w");
    fprintf(kicau,"%d\n", NEFF(l));
    for (int i = 0; i < NEFF(l); i++)
    {
        fprintf(kicau, "%d\n", IDKICAUAN(KICAU(l, i)));
        fprintf(kicau, "%s\n", TEXTKICAUAN(KICAU(l, i)).buffer);
        fprintf(kicau, "%d\n", LIKE(KICAU(l, i)));
        fprintf(kicau, "%s\n", USERNAME(AUTHOR(KICAU(l, i))).buffer);
        fprintf(kicau, "%d/%d/%d %d:%d:%d\n", DAY(DATETIME(KICAU(l, i))), MONTH(DATETIME(KICAU(l, i))), YEAR(DATETIME(KICAU(l, i))), HOUR(DATETIME(KICAU(l, i))), MINUTE(DATETIME(KICAU(l, i))), SECOND(DATETIME(KICAU(l, i))));
    }
    fclose(kicau);
}

void saveBalasan(char path[], int len, ListKicau lk)
/*  Melakukan proses penyimpanan data balasan ke dalam folder config
I.S : folder ada dan file balasan.config di dalamnya sembarang
F.S : file balasan.config tersimpan dalam folder config */
{
    int length = len, count;

    char configName[16] = "/balasan.config";
    for (int i = 0; i < 16; i++)
    {
        path[length] = configName[i];
        length++;
    }
    FILE* balas = fopen(path, "w");
    for (int i = 0; i < NEFF(lk); i++)
    {
        if (BALASAN(KICAU(lk,i)) != NULL)
        {
            count++;
        }
    }
    fprintf(balas, "%d\n", count);
    for (int i = 0; i < NEFF(lk); i++)
    {
        if (BALASAN(KICAU(lk,i)) != NULL)
        {
            fprintf(balas, "%d\n", IDKICAUAN(KICAU(lk, i)));
            fprintf(balas, "%d\n", lengthReply(BALASAN(KICAU(lk, i))));
            saveReplyTree(BALASAN(KICAU(lk, i)), balas, -1);
        }
    }

    fclose(balas);
}

void saveDraf(char path[], int len)
/*  Melakukan proses penyimpanan data draf ke dalam folder config
I.S : folder ada dan file draf.config di dalamnya sembarang
F.S : file draf.config tersimpan dalam folder config */
{
    int length = len, count;
    char configName[13] = "/draf.config";
    for (int i = 0; i < 13; i++)
    {
        path[length] = configName[i];
        length++;
    }
    FILE* draf = fopen(path, "w");
    count = 0;
    for (int i = 0; i < 20; i++)    // hitung user yang punya draft
    {
        if (!isEmptyDraft(ContainerDraft[i]))
        {
            count++;
        }
    }
    fprintf(draf, "%d\n", count);
    for (int i = 0; i < 20; i++)    // 
    {
        if (!isEmptyDraft(ContainerDraft[i]))
        {
            fprintf(draf, "%s %d\n", USERNAME(USER(UserList, i)).buffer, lengthDraft(ContainerDraft[i]));
            AddressDraft p = TOPDRAFT(ContainerDraft[i]);
            while (p != NULL)
            {
                fprintf(draf, "%s\n", CONTENTDRAFT(p).buffer);
                fprintf(draf, "%d/%d/%d %d:%d:%d\n", DAY(TIMEDRAFT(p)), MONTH(TIMEDRAFT(p)), YEAR(TIMEDRAFT(p)), HOUR(TIMEDRAFT(p)), MINUTE(TIMEDRAFT(p)), SECOND(TIMEDRAFT(p)));
                p = NEXTDRAFT(p);
            }
        }
    }

    fclose(draf);
}

void saveUtas(char path[], int len, ListKicau lk)
/*  Melakukan proses penyimpanan data utas ke dalam folder config
I.S : folder ada dan file utas.config di dalamnya sembarang
F.S : file utas.config tersimpan dalam folder config */
{
    int lengt = len, count;
    char configName[13] = "/utas.config";
    for (int i = 0; i < 13; i++)
    {
        path[lengt] = configName[i];
        lengt++;
    }
    FILE* utas = fopen(path, "w");
    count = 0;
    for (int i = 0; i < NEFF(lk); i++)
    {
        if (!isEmpty(UTAS(KICAU(lk, i))))
        {
            count++;
        }
    }
    fprintf(utas, "%d\n", count);
    for (int i = 0; i < NEFF(lk); i++)
    {
        if (!isEmpty(UTAS(KICAU(lk, i))))
        {
            Address u = FIRSTUTAS(UTAS(KICAU(lk, i)));
            fprintf(utas, "%d\n", IDKICAUAN(KICAU(lk, i)));
            fprintf(utas, "%d\n", length(UTAS(KICAU(lk, i))));
            for (int j = 0; j < length(UTAS(KICAU(lk, i))); i++)
            {
                fprintf(utas, "%s\n", CONTENT(u).buffer);
                fprintf(utas, "%s\n", USERNAME(AUTHORUTAS(u)).buffer);
                fprintf(utas, "%d/%d/%d %d:%d:%d\n", DAY(DATETIMEUTAS(u)), MONTH(DATETIMEUTAS(u)), YEAR(DATETIMEUTAS(u)), HOUR(DATETIMEUTAS(u)), MINUTE(DATETIMEUTAS(u)), SECOND(DATETIMEUTAS(u)));
                u = NEXT(u);
            }
        }
    }
    fclose(utas);
}

void saveReplyTree(REPLY r, FILE *f, int parent)
{
    if (!isEmptyREPLY(r))
    {
        fprintf(f, "%d %d\n", parent, REPLYID(r));
        fprintf(f, "%s\n", REPLYTEXT(r).buffer);
        fprintf(f, "%s\n", REPLYAUTHOR(r).buffer);
        fprintf(f, "%d/%d/%d %d:%d:%d\n", DAY(REPLYTIME(r)), MONTH(REPLYTIME(r)), YEAR(REPLYTIME(r)), HOUR(REPLYTIME(r)), MINUTE(REPLYTIME(r)), SECOND(REPLYTIME(r)));
        saveReplyTree(SIBLING(r), f, parent);
        saveReplyTree(CHILD(r), f, REPLYID(r));
    }
    
}

boolean isDirExist(char dir[])
/*  Memeriksa keberadaan sebuah path atau folder
    Mengirimkan true jika folder ada dan false
    folder tidak ada */
{
    struct stat sb;
    boolean check;
    if (stat(dir, &sb) == 0 && S_ISDIR(sb.st_mode)) {
        check = true;
    } else {
        check = false;
    }
    return check;
}