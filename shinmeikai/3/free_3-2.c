#include <time.h>
#include <stdio.h>
#include <stdlib.h>

int human;
int comp_1;
int comp_2;
int win_no;
int lose_no;
int draw_no;

char *hd[] = {"グー", "チョキ", "パー"};

typedef struct  {
    int human;
    int comp_1;
    int comp_2;
} PLAYER;

PLAYER player;

/*--- 初期化処理 ---*/
void initialize (void) {
    win_no = 0;
    lose_no = 0;
    draw_no = 0;

    srand(time(NULL));
    printf("じゃんけんゲーム開始!!\n");
}

/*--- じゃんけん実行 ---*/
void jyanken (void) {
    int i;

    comp_1 = rand() % 3;
    comp_2 = rand() % 3;

    do {
        printf("\n\aじゃんけんポン ・・・");
        for (i = 0; i < 3; i++) {
            printf(" (%d)%s", i, hd[i]);
        }
        printf(":");
        scanf("%d", &human);
    } while (human < 0 || human > 2);
}

void count_disp (int result) {
    switch (result) {
        case 0 : draw_no++; printf("引き分けです。");       break;
        case 1 : lose_no++; printf("あなたの負けです。");   break;
        case 2 : win_no++;  printf("あなたの勝ちです。");   break;
    }
}

char* result_text (int x) {
    switch (x) {
        case 0 : return "引き分け";
        case 1 : return "勝ち";
        case 2 : return "負け";
    }
}

void result_disp (void) {
    char* a = result_text(player.human);
    char* b = result_text(player.comp_1);
    char* c = result_text(player.comp_2);

    printf("\nあなた:%s com 1:%s com 2:%s\n\n", a, b, c);

}

/*---　再挑戦するか確認 ---*/
int confirm_retry (void) {
    int x;

    printf("もう一度しますか・・・(0)いいえ (1)はい:");
    scanf("%d", &x);

    return x;
}

void judge_game (void) {
    int judge;
    int sum;

    sum = (human + comp_1 + comp_2);
    judge = (human + comp_1 + comp_2) % 3;
    
    if (judge == 0) {
        player.human = 0;
        player.comp_1 = 0;
        player.comp_2 = 0;
    } else {
        if (human != 0 && comp_1 != 0 && comp_2 != 0 ) {
            if (human == 1) {
                player.human = 1;
            } else {
                player.human = 2;
            }
            if (comp_1 == 1) {
                player.comp_1 = 1;
            } else {
                player.comp_1 = 2;
            }
            if (comp_2 == 1) {
                player.comp_2 = 1;
            } else {
                player.comp_2 = 2;
            }
        }
        if (human != 1 && comp_1 != 1 && comp_2 != 1 ) {
            if (human == 2) {
                player.human = 1;
            } else {
                player.human = 2;
            }
            if (comp_1 == 2) {
                player.comp_1 = 1;
            } else {
                player.comp_1 = 2;
            }
            if (comp_2 == 2) {
                player.comp_2 = 1;
            } else {
                player.comp_2 = 2;
            }
        }
        if (human != 2 && comp_1 != 2 && comp_2 != 2 ) {
            if (human == 0) {
                player.human = 1;
            } else {
                player.human = 2;
            }
            if (comp_1 == 0) {
                player.comp_1 = 1;
            } else {
                player.comp_1 = 2;
            }
            if (comp_2 == 0) {
                player.comp_2 = 1;
            } else {
                player.comp_2 = 2;
            }
        }
    }
    
}

int main (void) {
    int judge;
    int retry;

    initialize();

    do {
        jyanken();

        printf("com_1は%sで、com_2は%sで、あなたは%sです。\n", hd[comp_1], hd[comp_2], hd[human]);
        judge_game();
        result_disp();

        retry = confirm_retry();

    } while (retry);
    //printf(win_no == 3 ? "\n\n□あなたの勝ちです。 \n" : "\n\n■私の勝ちです。\n");
    //printf("%d勝%d敗%d分けでした。\n", win_no, lose_no, draw_no);
    return 0;
}
