#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "../charmachine/charmachine.h"
#include "../wordmachine/wordmachine.h"
#include "../user/user.h"

void loadPengguna(STRING folder, ListUser *l);

void readUserFromFile(USER *u, int jumlahUser, ListUser *l);

