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

int main (void) {
    int i;
    char name[] = "Nishiura Takahiro ";
    int name_len = strlen(name);
    int cnt = name_len;

    while (1) {
        putchar('\r');
        for (i = 0; i < name_len; i++) {
            if (cnt + i >= name_len)
                putchar(name[cnt + i - name_len]);
            else
                putchar(name[cnt + i]);
        }

        fflush(stdout);
        sleep(500);

        if (cnt > 0)
            cnt--;
        else
            cnt = name_len - 1;
    } 
    return 0;
}
