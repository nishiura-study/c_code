#include <time.h>
#include <stdio.h>
#include <stdlib.h>

int human;
int comp;
int win_no;
int lose_no;
int draw_no;

char *hd[] = {"グー", "チョキ", "パー"};

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

    comp = rand() % 3;

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
}

/*--- 勝ち/負け/引き分け回数を更新 ---*/
void count_no (int result) {
    switch (result) {
        case 0 : draw_no++; break;
        case 1 : lose_no++; break;
        case 2 : win_no++;  break;
    }
}

/*--- 判定結果を表示 ---*/
void disp_result (int result) {
    switch (result) {
        case 0 : printf("引き分けです。");      break;
        case 1 : printf("あなたの負けです。");  break;
        case 2 : printf("あなたの勝ちです。");  break;
    }
}

/*---　再挑戦するか確認 ---*/
int confirm_retry (void) {
    int x;

    printf("もう一度しますか・・・(0)いいえ (1)はい:");
    scanf("%d", &x);

    return x;
}

int main (void) {
    int judge;
    int retry;

    initialize();

    do {
        jyanken();

        printf("私は%sで、あなたは%sです。\n", hd[comp], hd[human]);

        judge = (human - comp + 3) % 3;
        count_disp(judge);
        //disp_result(judge);
        //retry = confirm_retry();

    } while (win_no < 3 && lose_no < 3);
    printf(win_no == 3 ? "\n\n□あなたの勝ちです。 \n" : "\n\n■私の勝ちです。\n");
    printf("%d勝%d敗%d分けでした。\n", win_no, lose_no, draw_no);
    return 0;
}
