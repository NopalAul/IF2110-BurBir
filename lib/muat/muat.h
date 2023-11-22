#ifndef MUAT_H
#define MUAT_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "../charmachine/charmachine.h"
#include "../wordmachine/wordmachine.h"
#include "../user/user.h"
#include "../relation/relation.h"
#include "../matrix/matrix.h"
#include "../simpan/simpan.h"
#include "../kicauan/kicauan.h"

void loadAll(STRING folder, ListUser *l, RelationMatrix *m, ListKicau *lk);

void loadPengguna(STRING folder, ListUser *l, RelationMatrix *m);

void readUserFromFile(USER *u, int jumlahUser, ListUser *l, RelationMatrix *m);

void loadKicau(STRING folder, ListKicau *l, ListUser lu);
#endif

