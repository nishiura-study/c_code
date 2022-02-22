#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int main (void) {
    int stage;
    int a, b, c;
    int X;
    int n;
    double time_p[10];
    clock_t start, end;
    clock_t p_start, p_end;

    srand(time(NULL));

    printf("視野拡大暗算トレーニング開始!!\n");
    start = clock();

    for (stage=0; stage < 10; stage++) {
        p_start = clock();

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

        p_end = clock();
        time_p[stage] = (double) (p_end - p_start) / CLOCKS_PER_SEC;
    }

    end = clock();

    printf("%.1f秒かかりました。\n", (double) (end - start) / CLOCKS_PER_SEC);
    printf("各回の時間は以下です。\n");
    for (stage=0; stage < 10; stage++) {
        printf("%.1f\n", time_p[stage]);
    }
    printf("平均時間は%.1fです。\n", (double) (end - start) / CLOCKS_PER_SEC / 10);

    return 0;
}