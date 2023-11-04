#ifndef SIMPAN_H
#define SIMPAN_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "../wordmachine/wordmachine.h"
#include "../charmachine/charmachine.h"
#include "../boolean/boolean.h"
#include "../user/user.h"
#include "../kicauan/kicauan.h"
#include "../datetime/datetime.h"

void saveAll(ListUser LU, RelationMatrix m, ListFriendRequest lf, ListKicau lk);
/*  Melakukan penyimpanan data ke dalam folder config
I.S : keberadaan folder dan file di dalamnya sembarang
F.S : folder terbentuk dan berisi file config 
      yang menyimpan data program */

void savePengguna(char path[], int len, ListUser LU, RelationMatrix m, ListFriendRequest lf);
/*  Melakukan proses penyimpanan data pengguna ke dalam folder config
I.S : folder ada dan file pengguna.config di dalamnya sembarang
F.S : file pengguna.config tersimpan dalam folder config */

void saveKicauan(char path[], int len, ListKicau l);
/*  Melakukan proses penyimpanan data kicauan ke dalam folder config
I.S : folder ada dan file kicauan.config di dalamnya sembarang
F.S : file kicauan.config tersimpan dalam folder config */

void saveBalasan(char path[], int len);
/*  Melakukan proses penyimpanan data balasan ke dalam folder config
I.S : folder ada dan file balasan.config di dalamnya sembarang
F.S : file balasan.config tersimpan dalam folder config */

void saveDraf(char path[], int len);
/*  Melakukan proses penyimpanan data draf ke dalam folder config
I.S : folder ada dan file draf.config di dalamnya sembarang
F.S : file draf.config tersimpan dalam folder config */

void saveUtas(char path[], int len);
/*  Melakukan proses penyimpanan data utas ke dalam folder config
I.S : folder ada dan file utas.config di dalamnya sembarang
F.S : file utas.config tersimpan dalam folder config */

boolean isDirExist(char dir[]);
/*  Memeriksa keberadaan sebuah path atau folder
    Mengirimkan true jika folder ada dan false
    folder tidak ada */

#endif