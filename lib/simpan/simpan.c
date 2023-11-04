#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "simpan.h"
#include "../wordmachine/wordmachine.h"

void saveAll(ListUser l, RelationMatrix m, ListFriendRequest lf, ListKicau lk)
/*  Melakukan penyimpanan data ke dalam folder config
I.S : keberadaan folder dan file di dalamnya sembarang
F.S : folder terbentuk dan berisi file config 
      yang menyimpan data program */
{
    char path[113] = "../../config/";     // path untuk folder config
    int pathLen = 13;  

    printf("Masukkan nama folder penyimpanan\n");
    readString();
    stopRead();
    pathLen += string.length;

    for (int j = 0; j < string.length; j++) // menambahkan input user ke dalam path
    {
        path[13+j] = string.buffer[j];
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
    savePengguna(path, pathLen, l, m, lf);
    saveKicauan(path, pathLen, lk);
    saveBalasan(path, pathLen);
    saveDraf(path, pathLen);
    saveUtas(path, pathLen);
    printf("\nPenyimpanan telah berhasil dilakukan!\n");
}


void savePengguna(char path[], int len, ListUser LU, RelationMatrix m, ListFriendRequest lf)
/*  Melakukan proses penyimpanan data pengguna ke dalam folder config
I.S : folder ada dan file pengguna.config di dalamnya sembarang
F.S : file pengguna.config tersimpan dalam folder config */
{
    int length = len;
    char configName[17] = "/pengguna.config";
    for (int i = 0; i < 17; i++)
    {
        path[length] = configName[i];
        length++;
    }
    FILE* user = fopen(path, "w");
    fprintf(user,"%d\n", LENGTH(LU));
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
        fprintf(user, "%s\n", PHOTO(USER(LU,i)).buffer);
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
    // kurang jumlah permintaan berteman
    // kurang matriks permintaan berteman
    
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
        fprintf(kicau, "%d\n", ID(KICAU(l, i)));
        fprintf(kicau, "%s\n", TEXT(KICAU(l, i)).buffer);
        fprintf(kicau, "%d\n", LIKE(KICAU(l, i)));
        fprintf(kicau, "%s\n", USERNAME(AUTHOR(KICAU(l, i))).buffer);
        fprintf(kicau, "%d/%d/%d %d:%d:%d", DAY(DATETIME(KICAU(l, i))), MONTH(DATETIME(KICAU(l, i))), YEAR(DATETIME(KICAU(l, i))), HOUR(DATETIME(KICAU(l, i))), MINUTE(DATETIME(KICAU(l, i))), SECOND(DATETIME(KICAU(l, i))));
        if (i != NEFF(l)-1)
        {
            fprintf(kicau, "\n");
        }
    }
    
    
    fclose(kicau);
}

void saveBalasan(char path[], int len)
/*  Melakukan proses penyimpanan data balasan ke dalam folder config
I.S : folder ada dan file balasan.config di dalamnya sembarang
F.S : file balasan.config tersimpan dalam folder config */
{
    int length = len;
    char configName[16] = "/balasan.config";
    for (int i = 0; i < 16; i++)
    {
        path[length] = configName[i];
        length++;
    }
    FILE* balas = fopen(path, "w");
    fprintf(balas,"ini test balasan");
    fclose(balas);
}

void saveDraf(char path[], int len)
/*  Melakukan proses penyimpanan data draf ke dalam folder config
I.S : folder ada dan file draf.config di dalamnya sembarang
F.S : file draf.config tersimpan dalam folder config */
{
    int length = len;
    char configName[13] = "/draf.config";
    for (int i = 0; i < 13; i++)
    {
        path[length] = configName[i];
        length++;
    }
    FILE* draf = fopen(path, "w");
    fprintf(draf,"ini test draf");
    fclose(draf);
}

void saveUtas(char path[], int len)
/*  Melakukan proses penyimpanan data utas ke dalam folder config
I.S : folder ada dan file utas.config di dalamnya sembarang
F.S : file utas.config tersimpan dalam folder config */
{
    int length = len;
    char configName[13] = "/utas.config";
    for (int i = 0; i < 13; i++)
    {
        path[length] = configName[i];
        length++;
    }
    FILE* utas = fopen(path, "w");
    fprintf(utas,"ini test utas");
    fclose(utas);
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