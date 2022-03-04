#include <time.h>
#include <stdio.h>

int dayofweek(int year, int month, int day) {
    struct tm t;

    t.tm_year = year - 1900;
    t.tm_mon = month - 1;
    t.tm_mday = day;
    t.tm_hour = 0;
    t.tm_min = 0;
    t.tm_sec = 0;
    t.tm_isdst = -1;

    if (mktime(&t) == (time_t)-1) {
        return -1;
    }
    return t.tm_wday;
}

int dayofweek2(int year, int month, int day) {
    if (month == 1 || month == 2) {
        year--;
        month += 12;
    }
    return (year + year/4 - year/100 + year/400 + (13*month+8)/5 + day) % 7;
}

int main(void) {
    int y, m, d, w;
    char *ws[] = {"日", "月", "火", "水", "木", "金", "土"};

    printf("曜日を求めます。\n");
    printf("年 : "); scanf("%d", &y);
    printf("月 : "); scanf("%d", &m);
    printf("日 : "); scanf("%d", &d);

    w = dayofweek2(y, m, d);
    if (w != -1) {
        printf("それは%s曜日です。\n", ws[w]);
    } else {
        printf("求められませんでした。\n");
    }
    return 0;
}