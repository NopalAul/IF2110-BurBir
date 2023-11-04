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

void loadPengguna(STRING folder, ListUser *l, RelationMatrix *m, ListFriendRequest *lf);

void readUserFromFile(USER *u, int jumlahUser, ListUser *l, RelationMatrix *m, ListFriendRequest *lf);

#endif

