#include <stdio.h>

#define MAX 5

int main (void) {
    int i;
    int a[MAX];
    int cnt = 0;
    int retry;

    printf("整数を入力してください。\n");
    do {
        printf("%d個目の整数:", cnt + 1);
        scanf("%d", &a[cnt++ % MAX]);

        printf("続けますか？（Yes・・・1/No・・・0）:");
        scanf("%d", &retry);

    } while (retry == 1);

    i = cnt - MAX;
    if (i < 0) i = 0;

    for ( ; i < cnt; i++) {
        printf("%2d個目 : %d\n", i + 1, a[i % MAX]);
    }
    return 0;
}