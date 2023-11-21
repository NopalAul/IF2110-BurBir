#include <stdio.h>
#include <stdlib.h>
#include "lib/wordmachine/wordmachine.h"
#include "lib/user/user.h"
#include "lib/kicauan/kicauan.h"
#include "lib/boolean/boolean.h"
#include "lib/charmachine/charmachine.h"
#include "lib/datetime/datetime.h"
#include "lib/pcolor/pcolor.h"
#include "lib/listRequest/listRequest.h"


void login(USER *currentuser){
    printf("Masukkan nama:");
            readString();
            STRING username = string;
            if(searchUser(string)!=NOT_FOUND){
                printf("Masukkan password:");
                readString();
                if(isStringEqual(string,PASSWORD(USER(UserList,searchUser(username))))){
                    *currentuser = USER(UserList,searchUser(username));
                    printf("Selamat datang !");
                    displayString(USERNAME(*currentuser));
                    printf("\n");
                }
                else{
                    displayString(USERNAME(USER(UserList,searchUser(username))));
                    displayString(string);
                    displayString(PASSWORD(USER(UserList,searchUser(username))));
                    printf("Password salah!\n");
                }
            }
            else{
                printf("Wah, nama yang Anda cari tidak ada. Masukkan nama lain!");
            }
}

int main()
{
    USER currentuser;
    createListUser();

    createRelationMatrix();
    ListKicau listkicauan;
    createListKicau(&listkicauan,100);

    printf("WELCOME\n");
    while(1){
        printf(">>> ");
        readCommand();
        if(isWordEqual(string,"DAFTAR")){
            daftarUSER();
            currentuser = USER(UserList,LENGTH(UserList)-1);
        }
        else if(isWordEqual(string,"MASUK")){
            login(&currentuser);
        }
        else if(isWordEqual(string,"KICAU")){
            buatKicau(&listkicauan,currentuser);
        }
        else if(isWordEqual(string,"KICAUAN")){
            displayKicauan(listkicauan,currentuser);
        }
        else if(isWordEqual(string,"SUKA_KICAUAN")){
            int id = stringToInteger(leftInfo);
            sukaKicauan(&listkicauan,id,currentuser);
        }
        else if(isWordEqual(string,"UBAH_KICAUAN")){
            int id = stringToInteger(leftInfo);
            ubahKicauan(&listkicauan,currentuser,id);
        }
        
    }
}

// gcc -o tes main.c lib/wordmachine/wordmachine.c lib/user/user.c lib/kicauan/kicauan.c lib/charmachine/charmachine.c lib/datetime/datetime.c lib/pcolor/pcolor.c lib/listRequest/listRequest.c lib/matrix/matrix.c lib/relation/relation.c lib/reply/reply.c