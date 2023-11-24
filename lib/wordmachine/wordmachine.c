#include <stdio.h>
#include <stdlib.h>
#include "wordmachine.h"

STRING string;
boolean VALID;
STRING leftInfo;
STRING rightInfo;


void createEmptyString(STRING *str)
/* Melakukan proses alokasi memori buffer
I.S : string sembarang, dan MaxCap terdefinisi
F.S : string terdefinisi dengan buffer string dialokasikan 
      sebesar MaxCap dan length diset = 0*/
{
    // if ((*str).buffer != NULL){
    //     free((*str).buffer);
    // }
    // (*str).buffer = (char*)malloc(MaxCap*sizeof(char));
    // int i = 0;
    // while ((*str).buffer == NULL && i < 100){
    //     (*str).buffer = (char*)malloc(MaxCap*sizeof(char));
    //     i++;
    // }
    for (int i = 0 ; i  < 300; i++){
        (*str).buffer[i] = '\0';
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
    createEmptyString(str);
    while (input[str->length] != '\0' && str->length < MAX_CAPACITY){
        // if ((*str).length == (*str).MaxEl){
        //     expandString(str);
        // }
        str->buffer[str->length] = input[str->length];
        str->length++;
    }
}

// void expandString(STRING *str)
// /* Melakukan ekspansi memori (*str).buffer
// I.S : str terdefinisi
// F.S : ukuran memori (*str).buffer terekspansi*/
// {
//     int newMaxEl = (*str).MaxEl * 2;
//     char arr[(*str).length];
//     for (int i = 0; i < (*str).length; i++){
//         arr[i] = (*str).buffer[i];
//     }
//     free((*str).buffer);
//     (*str).buffer = (char*) malloc(newMaxEl*sizeof(char));
//     int i = 0;
//     while ((*str).buffer == NULL && i < 100){
//         (*str).buffer = (char*) malloc(newMaxEl*sizeof(char));
//         i++;
//     }
//     (*str).MaxEl = newMaxEl;
//     for (int i = 0; i < (*str).length; i++){
//         (*str).buffer[i] = arr[i];
//     }
// }

void copyString(STRING *str, STRING input)
/* Melakukan copy string input ke dalam string str
I.S : str sembarang, input terdefinisi
F.S : str terdefinisi sebagai hasil copy dari input*/
{
    createEmptyString(str);
    for (int i = 0; i < input.length; i++){
        str->buffer[i] = input.buffer[i];
    }
    str->length = input.length;
}

void ignoreCarriage()
/*Melakukan adv jika currentChar adalah CARRIAGE*/
{
    while (currentChar == CARIAGE){
        ADV();
    }
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

void ignoreBlankNewline()
/*Melakukan adv jika currentChar adalah NEWLINE atau BLANK*/
{
    while (currentChar == NEWLINE || currentChar == BLANK){
        ADV();
    }
}

void ignoreCarriageNewline()
/*Melakukan ADV jia currentChar adalah NEWLINE atau CARRIAGE*/
{
    while (currentChar == NEWLINE || currentChar == CARIAGE){
        ADV();
    }
}

void ignoreBlankCarriageNewline()
/*Melakukan ADV jika currentChar adalah BLANK, NEWLINE, atau CARRIAGE*/
{
    while (currentChar == BLANK || currentChar == NEWLINE || currentChar == CARIAGE){
        ADV();
    }
}

void readPassword()
/* Melakukan proses akuisi string dan menyimpannya ke dalam string
I.S : string sembarang
F.S : alokasi memori string diset dengan PASSWORD_CAPACITY
      kemudian dilakukan pembacaan string dan disimpan ke string*/
{
    createEmptyString(&string);
    START();
    ignoreCarriageNewline();
    VALID = true;
    while (!EOP && string.length < PASSWORD_CAPACITY){
        string.buffer[string.length] = currentChar;
        if (currentChar == '\n' || currentChar == '\r') VALID = false;
        ADV();
        string.length++;
    }
    while (!EOP){
        ADV();
        string.length++;
    }
    VALID = VALID && string.length <= USERNAME_CAPACITY;
    ADV();
}

void readUsername()
/* Melakukan proses akuisi string dan menyimpannya ke dalam string
I.S : string sembarang
F.S : alokasi memori string diset dengan USERNAME_CAPACITY
      kemudian dilakukan pembacaan string dan disimpan ke string*/
{
    createEmptyString(&string);
    VALID = true;
    START();
    ignoreCarriageNewline();
    while (!EOP && string.length < USERNAME_CAPACITY){
        string.buffer[string.length] = currentChar;
        if (currentChar == '\n' || currentChar == '\r') VALID = false;
        ADV();
        string.length++;
    }
    while (!EOP){
        ADV();
        string.length++;
    }
    VALID = VALID && string.length > 0 && string.length <= USERNAME_CAPACITY;
    ADV();
}

void readCommand()
/* Melakukan proses akuisi string dan menyimpannya ke dalam string
I.S : string sembarang
F.S : alokasi memori string diset dengan DEFAULT_CAPACITY
      kemudian dilakukan pembacaan string dan disimpan ke string*/
{
    createEmptyString(&string);
    START();
    ignoreBlankCarriageNewline();
    while (string.length < MAX_CAPACITY && currentChar != ' ' && !EOP){
        string.buffer[string.length] = currentChar;
        ADV();
        string.length++;
    }
    if (! EOP){
        ignoreBlankNewline();
    }
    leftInfo.length = 0;
    while (!EOP && currentChar != ' ' && currentChar != '\n'){
        leftInfo.buffer[leftInfo.length] = currentChar;
        leftInfo.length++;
        ADV();
    }
    if (! EOP){
        ignoreBlankNewline();
    }
    rightInfo.length = 0;
    while (!EOP && currentChar != ' ' && currentChar != '\n'){
        rightInfo.buffer[rightInfo.length] = currentChar;
        rightInfo.length++;
        ADV();
    }
    while (!EOP){
        ADV();
    }
    ADV();
}

void readBio()
/* Melakukan proses akuisi string dan menyimpannya ke dalam string untuk BIO
I.S : string sembarang
F.S : alokasi memori string diset dengan BIO_CAPACITY
      kemudian dilakukan pembacaan string dan disimpan ke string*/
{
    createEmptyString(&string);
    START();
    ignoreCarriageNewline();
    while (!EOP && string.length < BIO_CAPACITY){
        string.buffer[string.length] = currentChar;
        ADV();
        string.length++;
    }
    while (!EOP){
        ADV();
    }
    ADV();
}

void readKicauan()
/* Melakukan proses akuisi string dan menyimpannya ke dalam string untuk Kicauan
I.S : string sembarang
F.S : alokasi memori string diset dengan KICAUAN_CAPACITY
      kemudian dilakukan pembacaan string dan disimpan ke string*/
{
    createEmptyString(&string);
    START();
    ignoreCarriageNewline();
    while (!EOP && string.length < KICAUAN_CAPACITY){
        string.buffer[string.length] = currentChar;
        ADV();
        string.length++;
    }
    while (!EOP){
        ADV();
    }
    VALID = isKicauValid();
    ADV();
}

void readPhoto()
/* Melakukan proses akuisisi string dan menyimpannya ke dalam string untuk Foto profil
I.S : string sembarang
F.S : alokasi memori string diset dengan BIO_CAPACITY
      kemudian dilakukan pembacaan string dan disimpan ke string*/
{
    createEmptyString(&string);
    START();
    ignoreCarriageNewline();
    VALID = true;
    int cnt = 0;
    while (!EOP && string.length < BIO_CAPACITY){
        // if (string.length == string.MaxEl){
        //     expandString(&string);
        // }
        string.buffer[string.length] = currentChar;
        if (cnt%2 == 1){
            if (currentChar != ' ' && (cnt+1)%20!=0){
                VALID = false;
            } else if (currentChar != '\n' && (cnt+1)%20==0){
                VALID = false;
            }
        } else if (cnt%4 == 0){
            if (currentChar != 'R' && currentChar != 'G' && currentChar != 'B'){
                VALID = false;
                printf("--- %d\n", cnt);
            }
        } else {
            if (currentChar == ' '){
                VALID = false;
                //printf("inii --- %d\n", cnt);
            }
        }
        ignoreCarriage();
        ADV();
        string.length++;
        cnt++;
    }
    while (!EOP){
        ADV();
    }
    if (VALID){
        VALID = cnt == 99;
        //printf("Di sini bang\n");
    }
    ADV();
}

void readString()
/* Melakukan proses akuisisi string dan menyimpannya ke dalam string selain read di atas
I.S : string sembarang
F.S : alokasi memori string diset dengan DEFAULT_CAPACITY
      kemudian dilakukan pembacaan string dan disimpan ke string*/
{
    createEmptyString(&string);
    START();
    ignoreCarriageNewline();
    while (!EOP && string.length < MAX_CAPACITY){
        // if (string.length == string.MaxEl){
        //     expandString(&string);
        // }
        string.buffer[string.length] = currentChar;
        ADV();
        string.length++;
    }
    while (!EOP){
        ADV();
    }
    ADV();
}

boolean isStringSimiliar(STRING s1, STRING s2)
/* Mengembalikan true jika s1 sama dengan s2 dalam kasus insensitive, false jika tidak*/
{
    if (s1.length != s2.length){
        return false;
    }
    char l,f;
    for (int i = 0 ; i < s1.length; i++){
        l = s1.buffer[i];
        f = s2.buffer[i];
        if (l != f && l+32 != f && l != f+32 && l-32 != f && l != f-32){
            return false;
        }
    }
    return true;
}

boolean isStringEqual(STRING s1, STRING s2) //sace SENSITIVE
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

boolean isStringNumeric(STRING s)
/*Mengembalikan true jika seluruh elemen s adalah bilangan kecuali elemen pertama dapat bernilai '-'*/
{
    if (s.length == 0){
        return false;
    }
    int i = 0;
    if (s.buffer[0] == '-'){
        i = 1;
        if (s.length == 1){
            return false;
        }
    }
    for (int j = i; j < s.length; j++){
        if (s.buffer[j] < '0' || s.buffer[j]>'9'){
            return false;
        }
    }
    return true;
}

boolean isNoHPValid(STRING s){
    if (s.length == 0){
        return true;
    }
    return isStringNumeric(s) && s.buffer[0] != '-';
}

int stringToInteger(STRING s)
/*Mengubah STRING menjadi integer
Prekondisi : seluruh char pada STRING s adalah numeric, kecuali char pertama dapat bernilai'-'*/
{
    int temp = 0;
    int i = 0;
    int sign = 1;
    if (s.buffer[i] == '-'){
        i++;
        sign = -1;
    }
    while (i < s.length){
        temp = temp*10 + (s.buffer[i]-'0');
        i++;
    }
    return temp*sign;
}

void displayStringNoNewline(STRING s)
{
    for (int i = 0; i < s.length; i++){
        printf("%c", s.buffer[i]);
    }
}

boolean isWordEqual(STRING s, char other[])
{
    int len = 0;
    int i = 0;
    while (other[i] != '\0'){
        len++;
        i++;
    }
    if (len != s.length){
        return false;
    }
    i = 0;
    boolean nodiff = true;
    while (other[i] != '\0' && nodiff){
        if (other[i] != s.buffer[i]){
            nodiff = false;
        }
        i++;
    }
    return nodiff;
}

boolean isWordSimiliar(STRING  s, char other[])
{
    int len = 0;
    while (other[len] != '\0'){
        len++;
    }
    if (len != s.length){
        return false;
    }
    char l,f;
    for (int i = 0; i < s.length; i++){
        l = s.buffer[i];
        f = other[i];
        if (l != f && l+32 != f && l != f+32 && l-32 != f && l != f-32){
            return false;
        }
    }
    return true;
}

boolean isKicauValid()
{
    int count = 0;
    for (int i = 0; i < string.length; i++){
        if (string.buffer[i] == '\n' || string.buffer[i] == ' '){
            return false;
        }
        else {
            count++;
        }
    }
    return count > 0;
}

boolean isInputValid()
{
    for (int i = 0 ; i < string.length; i++){
        if (string.buffer[i] == '\n'){
            return false;
        }
    }
    return true;
}