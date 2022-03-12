#include <time.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

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
    int mdays = monthday(y, m);

    printf(" 日 月 火 水 木 金 土 \n");
    printf("---------------------\n");

    printf("%*s", 3 * wd, "");

    for (i = 1; i <= mdays; i++) {
        printf("%3d", i);
        if (++wd % 7 == 0) {
            putchar('\n');
        }
    }
    if (wd % 7 != 0) {
        putchar('\n');
    }
}

int strncompx(const char *s1, const char *s2, size_t n) {
    while (n && toupper(*s1) && toupper(*s2)) {
        if (toupper(*s1) != toupper(*s2)) {
            return (unsigned char)*s1 - (unsigned char)*s2;
        }
        s1++;
        s2++;
        n--;
    }
    if (!n)     return 0;
    if (*s1)    return 1;
    return -1;
}

int get_month(char *s) {
    int i;
    int m;
    char *month[] = {"", "January", "February", "March", "April", "May", "June",
                     "July", "August", "September", "October", "November", "December"};
    
    m = atoi(s);
    if (m >= 1 && m <= 12)
        return m;
    for (i = 1; i <= 12; i++) {
        if (strncompx(month[i], s, 3) == 0)
            return i;
    }
    return -1;
}

int main(int argc, char *argv[]) {
    int y, m;
    time_t t = time(NULL);
    struct tm *local = localtime(&t);

    y = local->tm_year + 1900;
    m = local->tm_mon + 1;

    if (argc >= 2) {
        m = get_month(argv[1]);
        if (m < 0 || m > 12) {
            fprintf(stderr, "月の値が不正です。\n");
            return 1;
        }
    }
    if (argc >= 3) {
        y = atoi(argv[2]);
        if (y < 0) {
            fprintf(stderr, "年の値が不正です。\n");
            return 1;
        }
    }

    printf("%d年%d月\n\n", y, m);

    put_calender(y, m);

    return 0;
}
