#include "muat.h"

int main ()
{
    startFile("../../config/car/pengguna.config");
    int count = 0;
    while (currentChar != 'q')
    {
        if (currentChar == '\r')
        {
            printf("ahay\n");
        }
        if (currentChar == '\n')
        {
            printf("ewe\n");
        }
        printf("%c", currentChar);
        ADV();
    }



    return 0;
}