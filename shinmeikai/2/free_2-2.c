#include <time.h>
#include <stdio.h>
#include <string.h>

int sleep (unsigned long x) {
    clock_t c1 = clock(), c2;
    do {
        if ((c2 = clock()) == (clock_t)-1)
            return 0;
    } while (1000.0 * (c2 - c1) / CLOCKS_PER_SEC < x);
    return 1;
}

void gput (const char *s, int speed) {
    int str_len = strlen(s);
    int i;

    for (i = 0; i < str_len; i++) {
        //putchar(s[i]);
        printf("%c", s[i]);
        sleep(speed);
    }
}

void bput (const char *s, int d, int e, int n) {
    int str_len = strlen(s);
    int i;

    for (i = 0; i < n; i++) {
        printf("\r%s", s);
        fflush(stdout);
        sleep(d);
        printf("\r%*s", str_len, "");
        fflush(stdout);
        sleep(e);
    }
}

void telop (const char *s, int direction, int speed, int n) {
    int i, j;
    int str_len = strlen(s);
    int cnt = 0;
    int flow_num = 0;

    for (j = 0; flow_num < n; j++) {
        putchar('\r');
        for (i = 0; i < str_len; i++) {
            if (cnt + i < str_len)
                putchar(s[cnt + i]);
            else
                putchar(s[cnt + i - str_len]);
        }

        fflush(stdout);
        sleep(speed);

        if (direction == 0) {
            if (cnt < str_len -1)
                cnt ++;
            else {
                cnt = 0;
                flow_num++;
            }    
        }
        else {
            if (cnt > 0)
                cnt--;
            else {
                cnt = str_len - 1;
                flow_num++;
            }
        }
    } 
}

int main (void) {
    //gput("Nishiura Takahiro", 50);
    //bput("nishiura takahiro", 100, 100, 10);
    telop("nishiura takahiro ", 1, 100, 5);
    return 0;
}