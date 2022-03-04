#include <stdio.h>

int mday[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

int dayofweek(int year, int month, int day) {
    if (month == 1 || month == 2) {
        year--;
        month += 12;
    }
    return (year + year/4 - year/100 + year/400 + (13*month+8)/5 + day) % 7;
}

int is_leap(int year) {
    return year % 4 == 0 && year % 100 != 0 || year % 400 == 0;
}

int monthday(int year, int month) {
    if (month-- != 2) {
        return mday[month];
    }
    return mday[month] + is_leap(year);
}

void put_calender(int y, int m) {
    int i;
    int wd = dayofweek(y, m, 1);
    int mday = monthday(y, m);

    printf(" 日 月 火 水 木 金 土 \n");
    printf("---------------------\n");

    printf("%*s", 3 * wd, "");

    for (i = 1; i <= mday; i++) {
        printf("%3d", i);
        if (++wd % 7 == 0){
            putchar('\n');
        }
    }
    if (wd % 7 != 0){
        putchar('\n');
    }
}

int main(void) {
    int y, m;

    printf("カレンダーを表示します。\n");
    printf("年 : ");    scanf("%d", &y);
    printf("月 : ");    scanf("%d", &m);

    putchar('\n');

    put_calender(y, m);

    return 0;
}
