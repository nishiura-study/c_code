#include <time.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int a, b, c, d;
    int x;
    time_t start, end;

    srand(time(NULL));

    a = rand() % 100;
    b = rand() % 100;
    c = rand() % 100;
    d = rand() % 100;

    printf("%d + %d + %d + %dは何ですか : ", a, b, c, d);

    start = time(NULL);
    while (1) {
        scanf("%d", &x);
        if (x == a + b + c + d) {
            break;
        }
        printf("違いますよ!!\n再入力してください : ");
    }

    end = time(NULL);

    printf("%.0f秒かかりました。\n", difftime(end, start));

    return 0;
}