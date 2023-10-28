#ifndef wordmachine_H
#define wordmachine_H

#include "../boolean/boolean.h"
#include "../charmachine/charmachine.h"

#define PASSWORD_CAPACITY 20
#define USERNAME_CAPACITY 20
#define BIO_CAPACITY 135
#define DEFAULT_CAPACITY 75
#define KICAUAN_CAPACITY 280

#define NUMBER_UNDEF -9999

#define BLANK ' '
#define NEWLINE '\n'

typedef struct {
    char * buffer; // menyimpan string 
    int length; // menyimpan panjang string yang sudah disimpan 
    int MaxEl; // menyimpan kapasitas maksimum dari string
} STRING;

/*  Sejauh ini deklarasi variabel untuk STRING harus di luar fungsi main
    supaya alokasi tidak diset di dalam stackframe
    kalau diset dalam fungsi main harus dilakukan malloc terlebih dahulu */

extern STRING string;
extern boolean VALID;
extern int leftNumber;
extern int rightNumber;

void createEmptyString(STRING *str, int MaxCap);
/* Melakukan proses alokasi memori buffer
I.S : string sembarang, dan MaxCap terdefinisi
F.S : string terdefinisi dengan buffer string dialokasikan 
      sebesar MaxCap dan length diset = 0*/

void createString(STRING *str, char input[]);
/* Melakukan copy isi input ke dalam STRING str
I.S : str sembarang, input terdefinisi
F.S : str disimpan dalam ukuran DEFAULT_CAPACITY 
      jika ukuran input melebihi alokasi memori
      str->buffer maka akan dilakukan ekspansi memori
      sebesar 2 kali ukuran awal*/

void expandString(STRING *str);
/* Melakukan ekspansi memori str->buffer
I.S : str terdefinisi
F.S : ukuran memori str->buffer terekspansi*/

void copyString(STRING *str, STRING input);
/* Melakukan copy string input ke dalam string str
I.S : str sembarang, input terdefinisi
F.S : str terdefinisi sebagai hasil copy dari input*/

void ignoreBlanks();
/*Melakukan adv jika currentChar adalah BLANK*/

void ignoreNewline();
/*Melakukan adv jika currentChar adalah NEWLINE*/

void ignoreBlankNewline();
/*Melakukan adv jika currentChar adalah NEWLINE atau BLANK*/

void readPassword();
/* Melakukan proses akuisisi string dan menyimpannya ke dalam string
I.S : string sembarang
F.S : alokasi memori string diset dengan PASSWORD_CAPACITY
      kemudian dilakukan pembacaan string dan disimpan ke string*/

void readUsername();
/* Melakukan proses akuisisi string dan menyimpannya ke dalam string
I.S : string sembarang
F.S : alokasi memori string diset dengan USERNAME_CAPACITY
      kemudian dilakukan pembacaan string dan disimpan ke string*/

void readCommand();
/* Melakukan proses akuisisi string dan menyimpannya ke dalam string
I.S : string sembarang
F.S : alokasi memori string diset dengan DEFAULT_CAPACITY
      kemudian dilakukan pembacaan string dan disimpan ke string*/

void readBio();
/* Melakukan proses akuisisi string dan menyimpannya ke dalam string untuk BIO
I.S : string sembarang
F.S : alokasi memori string diset dengan BIO_CAPACITY
      kemudian dilakukan pembacaan string dan disimpan ke string*/

void readKicauan();
/* Melakukan proses akuisisi string dan menyimpannya ke dalam string untuk Kicauan
I.S : string sembarang
F.S : alokasi memori string diset dengan KICAUAN_CAPACITY
      kemudian dilakukan pembacaan string dan disimpan ke string*/

void readPhoto();
/* Melakukan proses akuisisi string dan menyimpannya ke dalam string untuk Foto profil
I.S : string sembarang
F.S : alokasi memori string diset dengan BIO_CAPACITY
      kemudian dilakukan pembacaan string dan disimpan ke string*/

void readString();
/* Melakukan proses akuisisi string dan menyimpannya ke dalam string selain read di atas
I.S : string sembarang
F.S : alokasi memori string diset dengan DEFAULT_CAPACITY
      kemudian dilakukan pembacaan string dan disimpan ke string*/

boolean isStringSimiliar(STRING s1, STRING s2);
/* Mengembalikan true jika s1 sama dengan s2 dalam kasus insensitive, false jika tidak*/

boolean isStringEqual(STRING s1, STRING s2); //Sensitive
/* Mengembalikan true jika s1 sama dengan s2, false jika tidak*/

void displayString(STRING s);
/*Menampilkan ke layar hasil akuisisi string
I.S : string terdefinisi
F.S : isi string s ditampilkan ke layar*/

#endif