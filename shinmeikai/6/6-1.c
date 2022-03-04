#include <time.h>
#include <stdio.h>

void put_date(const struct tm *timer) {
    char *wday_name[] = {"日", "月", "火", "水", "木", "金", "土"};

    printf("%4d年%02d月%02d日(%s)%02d時%02d分%02d秒",
            timer->tm_year + 1900,
            timer->tm_mon + 1,
            timer->tm_mday,
            wday_name[timer->tm_wday],
            timer->tm_hour,
            timer->tm_min,
            timer->tm_sec);
}

char *asctime2(const struct tm *timeptr) {
    const char wday_name[7][8] = {
       "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"
    };
    const char mon_name[12][3] = {
        "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
    };
    static char result[25];

    sprintf(result, "%.3s %.3s %02d %02d:%02d:%02d %4d", 
                    wday_name[timeptr->tm_wday], mon_name[timeptr->tm_mon],
                    timeptr->tm_mday, timeptr->tm_hour, timeptr->tm_min, timeptr->tm_sec, timeptr->tm_year + 1900);
    return result;
}

int main(void) {
    time_t current;
    struct tm *timer;

    time(&current);
    //timer = localtime(&current);
    timer = gmtime(&current);

    printf("現在の日付・時刻はUTCで");
    put_date(timer);
    printf("です。\n");

    current = time(NULL);
    printf("現在の日付・時刻 : %s", asctime(localtime(&current)));

    return 0;
}