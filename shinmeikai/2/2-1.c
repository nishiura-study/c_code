#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int main (void) {
    int stage;
    int a, b, c;
    int X;
    int n;
    clock_t start, end;

    srand(time(NULL));

    printf("視野拡大暗算トレーニング開始!!\n");
    start = clock();

    for (stage=0; stage < 10; stage++) {
        a = 10 + rand() % 90;
        b = 10 + rand() % 90;
        c = 10 + rand() % 90;
        n = rand() % 17;

        printf("%d%*s+%*s%d%*s+%*s%d :", a, n, "", n, "", b, n, "", n, "", c);
        do {
            scanf("%d", &X);
            if (X == a + b + c) {
                break;
            }
            printf("\a違います。再入力してください : ");
        } while (1);
    }

    end = clock();

    printf("%.1f秒かかりました。\n", (double) (end - start) / CLOCKS_PER_SEC);

    return 0;
}