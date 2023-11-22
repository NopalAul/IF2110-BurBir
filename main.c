#include <stdio.h>
#include <stdlib.h>
#include "lib/wordmachine/wordmachine.h"
#include "lib/user/user.h"
#include "lib/kicauan/kicauan.h"
#include "lib/boolean/boolean.h"
#include "lib/charmachine/charmachine.h"
#include "lib/datetime/datetime.h"
#include "lib/pcolor/pcolor.h"
#include "lib/utas/utas.h"
#include "lib/draft/draft.h"

#define nl printf("\n")

void DisplayHeader();

int currentID;   // GLOBAL VARIABEL

void login(){
    if (UserList.length == 0){
        printf("\nWahh, belum ada pengguna terdaftar! Silahkan daftar dulu, Gan.\n\n");
    } else {
        int idFound;
        do {
            printf("\nMasukkan nama:\n");
            readUsername();
            idFound = searchUser(string);
            if (idFound == NOT_FOUND){
                printf("\nWah, nama yang Anda cari tidak ada. Masukkan nama lain.\n");
            } else {
                int i = 0;
                do {
                    printf("\nMasukkan kata sandi:\n");
                    readPassword();
                    if (!isStringEqual(string, PASSWORD(USER(UserList,idFound)))){
                        printf("Wah, kata sandi yang Anda masukkan belum tepat. Perikas kembali kata sandi Anda!\n\n");
                        i++;
                    }
                } while (i!= 3 && !isStringEqual(string, PASSWORD(USER(UserList,idFound))));
                if (i == 3) printf("Wah sayang sekali kesempatan Anda habis!\n\n");
                else {
                    currentID = idFound;
                    printf("\nAnda telah berhasil masuk dengan nama ");
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

    createContainerDraft();

    boolean running = true;

    DisplayHeader();

    while(running){
        print_red('>');
        print_red('>');
        print_red('>');
        printf(" ");
        readCommand();
        if (isWordEqual(string, "DAFTAR")){
            if (currentID < 0){
                daftarUSER();
            } else {
                printf("\nWalawe, Anda sedang login. Keluar dulu yuk untuk daftar akun baru!\n\n");
            }
        } else if (isWordEqual(string, "KELUAR")){
            if (currentID < 0){
                printf("\nWalawe, Anda belum login. Masuk atau daftar akun baru dulu yuk!\n\n");
            } else {
                currentID = -1;
                printf("\nAnda berhasil logout. Sampai jumpa di pertemuan berikutnya!\n\n");
            }
        } else if (isWordEqual(string, "MASUK")) {
            if (currentID < 0){
                login();
            } else {
                printf("\nWalawe, Anda sedang login. Keluar dulu kalau ingin ganti akun.\n\n");
            }
        } else if (isWordEqual(string, "TUTUP_PROGRAM")){
            currentID = -1;
            running = false;
        } else if (isWordEqual(string, "GANTI_PROFIL")){
            if (currentID < 0){
                printf("\nWalawe, Anda belum login! Masuk terlebih dahulu untuk menikmati layanan Burbir.\n\n");
            } else {
                gantiProfil(&USER(UserList,currentID));
            }
        } else if (isWordEqual(string, "LIHAT_PROFIL")){
            if (currentID < 0){
                printf("\nWalawe, Anda belum login! Masuk terlebih dahulu untuk menikmati layanan Burbir.\n\n");
            } else {
                LIHAT_PROFIL(currentID);
            }
        } else if (isWordEqual(string, "ATUR_JENIS_AKUN")){
            if (currentID < 0){
                printf("\nWalawe, Anda belum login! Masuk terlebih dahulu untuk menikmati layanan Burbir.\n\n");
            } else {
                aturJenisAkun(&USER(UserList,currentID));
            }
        } else if (isWordEqual(string, "UBAH_FOTO_PROFIL")){
            if (currentID < 0){
                printf("\nWalawe, Anda belum login! Masuk terlebih dahulu untuk menikmati layanan Burbir.\n\n");
            } else {
                ubahFotoProfil(&USER(UserList, currentID));
            }
        } else if (isWordEqual(string, "DAFTAR_TEMAN")){
            if (currentID < 0){
                printf("\nWalawe, Anda belum login! Masuk terlebih dahulu untuk menikmati layanan Burbir.\n\n");
            } else {
                daftarTeman(currentID);
            }
        } else if (isWordEqual(string, "HAPUS_TEMAN")){
            if (currentID < 0){
                printf("\nWalawe, Anda belum login! Masuk terlebih dahulu untuk menikmati layanan Burbir.\n\n");
            } else {
                hapusTeman(currentID);
            }
        } else if (isWordEqual(string, "TAMBAH_TEMAN")){
            if (currentID < 0){
                printf("\nWalawe, Anda belum login! Masuk terlebih dahulu untuk menikmati layanan Burbir.\n\n");
            } else {
                tambahTeman(currentID);
            }
        } else if (isWordEqual(string, "DAFTAR_PERMINTAAN_PERTEMANAN")){
            if (currentID < 0){
                printf("\nWalawe, Anda belum login! Masuk terlebih dahulu untuk menikmati layanan Burbir.\n\n");
            } else {
                daftarPermintaanTeman(currentID);
            }
        } else if (isWordEqual(string, "SETUJUI_PERTEMANAN")){
            if (currentID < 0){
                printf("\nWalawe, Anda belum login! Masuk terlebih dahulu untuk menikmati layanan Burbir.\n\n");
            } else {
                acceptPertemanan(currentID);
            }
        } else if (isWordEqual(string, "KICAU")){
            if (currentID < 0){
                printf("\nWalawe, Anda belum login! Masuk terlebih dahulu untuk menikmati layanan Burbir.\n\n");
            } else {
                buatKicau(&listkicauan, USER(UserList, currentID));
            }
        } else if (isWordEqual(string, "KICAUAN")){
            if (currentID < 0){
                printf("\nWalawe, Anda belum login! Masuk terlebih dahulu untuk menikmati layanan Burbir.\n\n");
            } else {
                displayKicauan(listkicauan, USER(UserList, currentID));
            }
        } else if (isWordEqual(string, "SUKA_KICAUAN")){
            if (currentID < 0){
                printf("\nWalawe, Anda belum login! Masuk terlebih dahulu untuk menikmati layanan Burbir.\n\n");
            } else {
                if (!isStringNumeric(leftInfo)){
                    printf("\nCommand yang Anda masukkan tidak sesuai. Masukkan command yang sesuai!\n\n");
                } else {
                    int target = stringToInteger(leftInfo);
                    sukaKicauan(&listkicauan, target, USER(UserList, currentID));
                }
            }
        } else if (isWordEqual(string, "UBAH_KICAUAN")){
            if (currentID < 0){
                printf("\nWalawe, Anda belum login! Masuk terlebih dahulu untuk menikmati layanan Burbir.\n\n");
            } else {
                if (!isStringNumeric(leftInfo)){
                    printf("\nCommand yang Anda masukkan tidak sesuai. Masukkan command yang sesuai!\n\n");
                } else {
                    int target = stringToInteger(leftInfo);
                    ubahKicauan(&listkicauan, USER(UserList, currentID), target);
                }
            }
        } else if (isWordEqual(string, "BALAS")){
            if (currentID < 0){
                printf("\nWalawe, Anda belum login! Masuk terlebih dahulu untuk menikmati layanan Burbir.\n\n");
            } else {
                BALAS(&listkicauan, currentID);
            }
        } else if (isWordEqual(string, "BALASAN")){
            if (currentID < 0){
                printf("\nWalawe, Anda belum login! Masuk terlebih dahulu untuk menikmati layanan Burbir.\n\n");
            } else {
                DISPLAYBALASAN(&listkicauan, currentID);
            }
        } else if (isWordEqual(string, "HAPUS_BALASAN")){
            if (currentID < 0){
                printf("\nWalawe, Anda belum login! Masuk terlebih dahulu untuk menikmati layanan Burbir.\n\n");
            } else {
                HAPUSBALASAN(&listkicauan, currentID);
            }
        } else if (isWordEqual(string, "BUAT_DRAFT")){
            if (currentID < 0){
                printf("\nWalawe, Anda belum login! Masuk terlebih dahulu untuk menikmati layanan Burbir.\n\n");
            } else {
                BUAT_DRAFT(currentID, &listkicauan);
            }
        } else if (isWordEqual(string, "LIHAT_DRAFT")){
            if (currentID < 0){
                printf("\nWalawe, Anda belum login! Masuk terlebih dahulu untuk menikmati layanan Burbir.\n\n");
            } else {
                LIHAT_DRAFT(currentID, &listkicauan);
            }
        } else if (isWordEqual(string, "UTAS")){
            if (currentID < 0){
                printf("\nWalawe, Anda belum login! Masuk terlebih dahulu untuk menikmati layanan Burbir.\n\n");
            } else {
                tulisUtas(&listkicauan, USER(UserList, currentID), stringToInteger(leftInfo));
            }
        } else if (isWordEqual(string, "SAMBUNG_UTAS")){
            if (currentID < 0){
                printf("\nWalawe, Anda belum login! Masuk terlebih dahulu untuk menikmati layanan Burbir.\n\n");
            } else {
                sambungUtas(&listkicauan, stringToInteger(leftInfo), stringToInteger(rightInfo), USER(UserList, currentID));
            }
        } else if (isWordEqual(string, "HAPUS_UTAS")){
            if (currentID < 0){
                printf("\nWalawe, Anda belum login! Masuk terlebih dahulu untuk menikmati layanan Burbir.\n\n");
            } else {
                hapusUtas(&listkicauan, stringToInteger(leftInfo), stringToInteger(rightInfo), USER(UserList, currentID));
            }
        } else if (isWordEqual(string, "CETAK_UTAS")){
            if (currentID < 0){
                printf("\nWalawe, Anda belum login! Masuk terlebih dahulu untuk menikmati layanan Burbir.\n\n");
            } else {
                cetakUtas(listkicauan, stringToInteger(leftInfo));
            }
        } else if (isWordEqual(string, "SIMPAN")){
            //do procedure
        } else if (isWordEqual(string, "MUAT")){
            if (currentID < 0){
                //do procedure
            } else {
                printf("\nWalawe, Anda masih login. Keluar dulu ya kalau ingin melakukan MUAT!\n\n");
            }
        } else {
            printf("\nWalawe, command yang Anda masukkan tidak sesuai!\n\n");
        }
    }
    stopRead();
    printf("\nAnda telah keluar dari program Burbir.\nSampai jumpa di penjelajahan berikutnya.\n\n");
}

// gcc -o tes main.c lib/wordmachine/wordmachine.c lib/user/user.c lib/kicauan/kicauan.c lib/charmachine/charmachine.c lib/datetime/datetime.c lib/pcolor/pcolor.c lib/listRequest/listRequest.c lib/matrix/matrix.c lib/relation/relation.c lib/reply/reply.c


void DisplayHeader(){
    printf(".______    __    __  .______      .______    __  .______");
    nl;
    printf("|   _  \\  |  |  |  | |   _  \\     |   _  \\  |  | |   _  \\    ");
    nl;
    printf("|  |_)  | |  |  |  | |  |_)  |    |  |_)  | |  | |  |_)  |    ");
    nl;
    printf("|   _  <  |  |  |  | |      /     |   _  <  |  | |      /     ");
    nl;
    printf("|  |_)  | |  `--'  | |  |\\  \\----.|  |_)  | |  | |  |\\  \\----. ");
    nl;
    printf("|______/   \\______/  | _| `._____||______/  |__| | _| `._____| ");
    nl;
    nl;
}