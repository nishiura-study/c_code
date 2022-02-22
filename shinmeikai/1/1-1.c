#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_STAGE 10

int main(void) {
    int i;
    int stage;
    int no;
    int ans;
    int num[MAX_STAGE];

    srand(time(NULL));
    ans = rand() % 1000;

    printf("0~999の整数を当ててください。\n\n");

    stage = 0;
    do {
        printf("残り%d回。 いくつかな:", MAX_STAGE - stage);
        scanf("%d", &no);
        num[stage++] = no;

        if (no > ans)
            printf("\aもっと小さいよ \n");
        else if (no < ans)
            printf("\aもっと大きいよ \n");

    } while (no != ans && stage < MAX_STAGE);

    if (no != ans)
        printf("残念。正解は%dでした。\n", ans);
    else{
        printf("正解です。 \n");
        printf("%d回で当たりましたね。\n", stage);
        }

    puts("\n--- 入力履歴 ---");
    for (i = 0; i<stage; i++)
        printf("%2d : %4d %+4d\n", i+1, num[i], num[i]-ans);
        
    return 0;
}