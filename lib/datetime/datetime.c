#include "datetime.h"
#include <stdio.h>
void createDATETIME(DATETIME *dt)
{
    DAY(*dt) = 0;
    MONTH(*dt) = 0;
    YEAR(*dt) = 0;
    HOUR(*dt) = 0;
    MINUTE(*dt) = 0;
    SECOND(*dt) = 0;
}

DATETIME getCurrentDATETIME()
{
    DATETIME dt;
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    DAY(dt) = tm.tm_mday;
    MONTH(dt) = tm.tm_mon + 1;
    YEAR(dt) = tm.tm_year + 1900;
    HOUR(dt) = tm.tm_hour;
    MINUTE(dt) = tm.tm_min;
    SECOND(dt) = tm.tm_sec;
    return dt;
}

void displayDATETIME(DATETIME dt)
{
    printf("%02d/%02d/%04d %02d:%02d:%02d\n", DAY(dt), MONTH(dt), YEAR(dt), HOUR(dt), MINUTE(dt), SECOND(dt));
}
