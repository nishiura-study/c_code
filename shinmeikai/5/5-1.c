#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LEVEL_MIN   2
#define LEVEL_MAX   6

int sleep (unsigned long x) {
    clock_t c1 = clock(), c2;

    do {
        if ((c2 = clock()) == (clock_t)-1)
            return 0;
    } while (1000.0 * (c2 -c1) / CLOCKS_PER_SEC < x);
    return 1;
}

int main (void) {
    int max_stage;
    int *score;
    int i, stage;
    int level;
    int success;
    clock_t start, end;

    srand(time(NULL));
    printf("プラスワントレーニング開始!!\n");
    printf("2桁の数値を記憶します。\n");
    printf("1を加えた値を入力しましょう。\n");

    do {
        printf("挑戦するレベル (%d～%d) :", LEVEL_MIN, LEVEL_MAX);
        scanf("%d", &level);
    } while (level < LEVEL_MIN || level > LEVEL_MAX);

    do {
        printf("トレーニング回数 : ");
        scanf("%d", &max_stage);
    } while (max_stage <= 0);

    score = calloc(max_stage, sizeof(int));

    success = 0;
    start = clock();

    for (stage = 0; stage < max_stage; stage++) {
        int no[LEVEL_MAX];
        int x[LEVEL_MAX];
        int seikai = 0;

        printf("\n第%dステージ開始!!\n", stage + 1);

        for (i = 0; i < level; i++) {
            no[i] = rand() % 90 + 10;
            printf("%d ", no[i]);
        }
        fflush(stdout);

        sleep(300 * level);
        printf("\r%*s\r", 3 * level, "");
        fflush(stdout);

        for (i = 0; i < level; i++) {
            printf("%d番目の数:", i + 1);
            scanf("%d", &x[i]);
        }

        for (i = 0; i < level; i++) {
            if (x[i] != no[i] + 1)
                printf("✕ ");
            else {
                printf("〇 ");
                seikai++;
            }
        }
        putchar('\n');

        for (i = 0; i < level; i++) {
            printf("%2d ", no[i]);
        }
        printf("・・・%d個正解です。\n", seikai);
        
        score[stage] = seikai;
        success += seikai;
    }

    end = clock();
    
    printf("%d回中%d回成功しました。\n", level * max_stage, success);
    for (stage = 0; stage < max_stage; stage++) {
        printf("第%2dステージ : %d\n", stage+1, score[stage]);
    }
    printf("%.1f秒でした。\n", (double)(end - start) / CLOCKS_PER_SEC);
    free(score);
    return 0;
}
