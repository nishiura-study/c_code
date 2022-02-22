#include <stdio.h>
#include <stdlib.h>

int main (void) {
    int *x;
    int n;

    printf("確保する配列の要素数 : ");
    scanf("%d", &n);

    x = calloc(n, sizeof(int));

    if (x == NULL) {
        puts("記憶域の確保に失敗しました。");
    } else {
        int i;
        for (i = 0; i < n; i++) {
            x[i] = i;
        }
        for (i = 0; i < n; i++) {
            printf("x[%d] = %d\n", i, x[i]);
        }
        free(x);
    }
    return 0;
}