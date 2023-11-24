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

void loadAll(STRING folder, ListKicau *lk);

void loadPengguna(STRING folder);

void readUserFromFile(USER *u, int jumlahUser);

void loadKicau(STRING folder, ListKicau *l);

void loadBalasan(STRING folder, ListKicau *lk);

void loadDraf(STRING folder);

void loadUtas(STRING folder, ListKicau *lk);

#endif