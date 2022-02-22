#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//#define MAX_STAGE 7

int main(void) {


    int i;
    int stage;
    int no;
    int ans;
    int num_1, num_2;
    int max_num;
    int min_num;
    int level;
    int range;

    printf("難易度を選択して下さい。\n Press (1): level1, (2): level2, (3): level3, (4): level4 \n");
    scanf("%d", &level);
    
    if (level == 1)
        range = 10;
    else if (level == 2)
        range = 100;
    else if (level == 3)
        range = 1000;
    else
        range = 10000;

    srand(time(NULL));
    num_1 = rand() % range;
    num_2 = rand() % range;

    if (num_1 >= num_2) {
        max_num = num_1;
        min_num = num_2;
        }
    else {
        max_num = num_2;
        min_num = num_1;
        }
    
    
    int flag = 1;
    int MAX_STAGE = 0;
    int sa = (max_num - min_num);

    while (flag)
    {
        if (sa / 2 > 2)
            {sa = sa / 2;
            ++MAX_STAGE;}
        else
            flag = 0;
    }

    int num[MAX_STAGE];

    ans = min_num + rand() % (max_num - min_num);
    printf("%d~%dの整数を当ててください。\n\n", min_num, max_num);

    stage = 0;
    do {
        printf("残り%d回。 いくつかな:", MAX_STAGE - stage);
        scanf("%d", &no);
        num[stage++] = no;

        if (no > ans)
            printf("\aもっと小さいよ \n");
        else if (no < ans)
            printf("\aもっと大きいよ \n");

    } while ((no != ans && stage < MAX_STAGE));

    if (no != ans)
        printf("残念。正解は%dでした。\n", ans);
    else{
        printf("正解です。 \n");
        printf("%d回で当たりましたね。\n", stage);
        }

    puts("\n--- 入力履歴 ---");
    for (i = 0; i<stage; i++)
        if (num[i]-ans == 0)
            printf("%2d : %4d %4d\n", i+1, num[i], num[i]-ans);
        else
            printf("%2d : %4d %+4d\n", i+1, num[i], num[i]-ans);
        
    return 0;
}