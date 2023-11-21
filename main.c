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
#include "lib/utas/utas.h"

int currentID;   // GLOBAL VARIABEL

void login(){
    if (UserList.length == 0){
        printf("Wahh, belum ada pengguna terdaftar! Silahkan daftar dulu, Gan.\n\n");
    } else {
        int idFound;
        do {
            printf("Masukkan nama:\n");
            readUsername();
            idFound = searchUser(string);
            if (idFound == NOT_FOUND){
                printf("Wah, nama yang Anda cari tidak ada. Masukkan nama lain.\n\n");
            } else {
                int i = 0;
                do {
                    printf("Masukkan kata sandi:\n");
                    readPassword();
                    if (!isStringEqual(string, PASSWORD(USER(UserList,idFound)))){
                        printf("Wah, kata sandi yang Anda masukkan belum tepat. Perikas kembali kata sandi Anda!\n\n");
                        i++;
                    }
                } while (i!= 3 && !isStringEqual(string, PASSWORD(USER(UserList,idFound))));
                if (i == 3) printf("Wah sayang sekali kesempatan Anda habis!\n\n");
                else {
                    currentID = idFound;
                    printf("Anda telah berhasil masuk dengan nama ");
                    displayStringNoNewline(USERNAME(USER(UserList,currentID)));
                    printf(". Mari membuang waktu di Burbir bersama Ande-Ande Lumut!\n\n");
                }
            }
        } while (idFound == NOT_FOUND);
    }
}


int main()
{   
    currentID = -1;
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
        }
        else if(isWordEqual(string,"MASUK")){
            login();
        }
        else if(isWordEqual(string,"KICAU")){
            buatKicau(&listkicauan,USER(UserList,currentID));
        }
        else if(isWordEqual(string,"KICAUAN")){
            displayKicauan(listkicauan,USER(UserList,currentID));
        }
        else if(isWordEqual(string,"SUKA_KICAUAN")){
            int id = stringToInteger(leftInfo);
            sukaKicauan(&listkicauan,id,USER(UserList,currentID));
        }
        else if(isWordEqual(string,"UBAH_KICAUAN")){
            int id = stringToInteger(leftInfo);
            ubahKicauan(&listkicauan,USER(UserList,currentID),id);
        }
        else if(isWordEqual(string,"UTAS")){
            //tulisUtas();
        }
    }
}

// gcc -o tes main.c lib/wordmachine/wordmachine.c lib/user/user.c lib/kicauan/kicauan.c lib/charmachine/charmachine.c lib/datetime/datetime.c lib/pcolor/pcolor.c lib/listRequest/listRequest.c lib/matrix/matrix.c lib/relation/relation.c lib/reply/reply.c
