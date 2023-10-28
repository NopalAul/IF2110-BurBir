#include <stdio.h>
#include <stdlib.h>
#include "wordmachine.h"

STRING string;
boolean VALID;

void createEmptyString(STRING *str, int MaxCap)
/* Melakukan proses alokasi memori buffer
I.S : string sembarang, dan MaxCap terdefinisi
F.S : string terdefinisi dengan buffer string dialokasikan 
      sebesar MaxCap dan length diset = 0*/
{
    if ((*str).buffer != NULL){
        free((*str).buffer);
    }
    (*str).buffer = (char*)malloc(MaxCap*sizeof(char));
    int i = 0;
    while ((*str).buffer == NULL && i < 100){
        (*str).buffer = (char*)malloc(MaxCap*sizeof(char));
        i++;
    }
    (*str).length = 0;
}

void createString(STRING *str, char input[])
/* Melakukan copy isi input ke dalam STRING str
I.S : str sembarang, input terdefinisi
F.S : str disimpan dalam ukuran DEFAULT_CAPACITY 
      jika ukuran input melebihi alokasi memori
      (*str).buffer maka akan dilakukan ekspansi memori
      sebesar 2 kali ukuran awal*/
{
    createEmptyString(str, DEFAULT_CAPACITY);
    while (input[str->length] != '\0'){
        if ((*str).length == (*str).MaxEl){
            expandString(str);
        }
        (*str).buffer[str->length] = input[str->length];
        (*str).length++;
    }
}

void expandString(STRING *str)
/* Melakukan ekspansi memori (*str).buffer
I.S : str terdefinisi
F.S : ukuran memori (*str).buffer terekspansi*/
{
    int newMaxEl = (*str).MaxEl * 2;
    char arr[(*str).length];
    for (int i = 0; i < (*str).length; i++){
        arr[i] = (*str).buffer[i];
    }
    free((*str).buffer);
    (*str).buffer = (char*) malloc(newMaxEl*sizeof(char));
    int i = 0;
    while ((*str).buffer == NULL && i < 100){
        (*str).buffer = (char*) malloc(newMaxEl*sizeof(char));
        i++;
    }
    (*str).MaxEl = newMaxEl;
    for (int i = 0; i < (*str).length; i++){
        (*str).buffer[i] = arr[i];
    }
}

void copyString(STRING *str, STRING input)
/* Melakukan copy string input ke dalam string str
I.S : str sembarang, input terdefinisi
F.S : str terdefinisi sebagai hasil copy dari input*/
{
    createEmptyString(str, input.MaxEl);
    for (int i = 0; i < input.length; i++){
        str->buffer[i] = input.buffer[i];
    }
    str->length = input.length;
}

void ignoreBlanks()
/*Melakukan adv jika currentChar adalah BLANK*/
{   
    while (currentChar == BLANK){
        ADV();
    }
}

void ignoreNewline()
/*Melakukan adv jika currentChar adalah NEWLINE*/
{
    while (currentChar == NEWLINE){
        ADV();
    }
}

void readPassword()
/* Melakukan proses akuisi string dan menyimpannya ke dalam string
I.S : string sembarang
F.S : alokasi memori string diset dengan PASSWORD_CAPACITY
      kemudian dilakukan pembacaan string dan disimpan ke string*/
{
    createEmptyString(&string, PASSWORD_CAPACITY);
    START();
    while (!EOP && string.length < PASSWORD_CAPACITY){
        string.buffer[string.length] = currentChar;
        ADV();
        string.length++;
    }
    VALID = EOP == true;
    ADV();
}

void readUsername()
/* Melakukan proses akuisi string dan menyimpannya ke dalam string
I.S : string sembarang
F.S : alokasi memori string diset dengan USERNAME_CAPACITY
      kemudian dilakukan pembacaan string dan disimpan ke string*/
{
    createEmptyString(&string, USERNAME_CAPACITY);
    START();
    while (!EOP && string.length < USERNAME_CAPACITY){
        string.buffer[string.length] = currentChar;
        ADV();
        string.length++;
    }
    VALID = EOP == true;
    ADV();
}

void readCommand()
/* Melakukan proses akuisi string dan menyimpannya ke dalam string
I.S : string sembarang
F.S : alokasi memori string diset dengan DEFAULT_CAPACITY
      kemudian dilakukan pembacaan string dan disimpan ke string*/
{
    createEmptyString(&string, DEFAULT_CAPACITY);
    START();
    ignoreBlanks();
    while (!EOP && string.length < DEFAULT_CAPACITY){
        string.buffer[string.length] = currentChar;
        ADV();
        string.length++;
    }
    ADV();
}

void readBio()
/* Melakukan proses akuisi string dan menyimpannya ke dalam string untuk BIO
I.S : string sembarang
F.S : alokasi memori string diset dengan BIO_CAPACITY
      kemudian dilakukan pembacaan string dan disimpan ke string*/
{
    createEmptyString(&string, BIO_CAPACITY);
    START();
    while (!EOP && string.length < BIO_CAPACITY){
        string.buffer[string.length] = currentChar;
        ADV();
        string.length++;
    }
    ADV();
}

void readKicauan()
/* Melakukan proses akuisi string dan menyimpannya ke dalam string untuk Kicauan
I.S : string sembarang
F.S : alokasi memori string diset dengan KICAUAN_CAPACITY
      kemudian dilakukan pembacaan string dan disimpan ke string*/
{
    createEmptyString(&string, KICAUAN_CAPACITY);
    START();
    while (!EOP && string.length < KICAUAN_CAPACITY){
        string.buffer[string.length] = currentChar;
        ADV();
        string.length++;
    }
    ADV();
}

boolean isStringEqual(STRING s1, STRING s2)
/* Mengembalikan true jika s1 sama dengan s2, false jika tidak*/
{
    if (s1.length != s2.length){
        return false;
    }
    for (int i = 0 ; i < s1.length; i++){
        if (s1.buffer[i] != s2.buffer[i]){
            return false;
        }
    }
    return true;
}

void displayString(STRING s)
/*Menampilkan ke layar hasil akuisisi string
I.S : string terdefinisi
F.S : isi string s ditampilkan ke layar*/
{
    for (int i = 0; i < s.length; i++){
        printf("%c", s.buffer[i]);
    }
    printf("\n");
}