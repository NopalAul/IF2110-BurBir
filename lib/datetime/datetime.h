#ifndef datetime_h
#define datetime_h

#include "../boolean/boolean.h"

#include "time.h"

typedef struct{
    int day;
    int month;
    int year;
    int second;
    int minute;
    int hour;
} DATETIME;

#define DAY(D) (D).day
#define MONTH(D) (D).month
#define YEAR(D) (D).year
#define SECOND(D) (D).second
#define MINUTE(D) (D).minute
#define HOUR(D) (D).hour

void createDATETIME(DATETIME *datetime);


DATETIME getCurrentDATETIME();


void displayDATETIME(DATETIME datetime);
#endif