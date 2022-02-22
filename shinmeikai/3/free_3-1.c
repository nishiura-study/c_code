#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int human;
int comp;
int win_no;
int lose_no;
int draw_no;
int try_no;
int init_hd = 0;
int all_try;

char *hd[] = {"パー", "グー", "チョキ"};

typedef struct {
    int *array;  // 配列本体のポインタ
    int capa;  // 配列の要素数（上限数）
    int len;  // 配列の現在の長さ
} DynamicArray;

DynamicArray * DynamicArray_New(void) {
    // 構造体自身のメモリを確保
    DynamicArray *self = calloc(1, sizeof(*self));
    if (!self) {
        return NULL;
    }

    // 配列のメモリを初期値で確保
    self->capa = 2;  // 初期容量（テストのため少なめに設定）
    self->array = calloc(self->capa, sizeof(int));
    if (!self->array) {
        free(self);
        return NULL;
    }

    return self;
}

DynamicArray * DynamicArray_Resize(DynamicArray *self, int capa) {
    int byte = sizeof(int);  // 要素1つのサイズ（バイト）
    int size = capa * byte;  // 配列全体のサイズ（バイト）
    int *tmp = realloc(self->array, size);  // メモリを再確保
    if (!tmp) {
        return NULL;
    }

    self->array = tmp;  // 再確保に成功したらポインタを保存する
    self->capa = capa;  // リサイズ後の容量に更新する

    return self;
}

DynamicArray * DynamicArray_PushBack(DynamicArray *self, int elem) {
    // プッシュ前に配列のリサイズを行う
    // 現在の配列の長さが容量以上だったらリサイズ
    if (self->len >= self->capa) {
        if (!DynamicArray_Resize(self, self->capa * 2)) {
            return NULL;
        }
    }

    self->array[self->len++] = elem;  // 要素を配列に保存

    return self;
}

/*--- 初期化処理 ---*/
void initialize (void) {
    win_no = 0;
    lose_no = 0;
    draw_no = 0;
    all_try = 0;

    srand(time(NULL));
    printf("じゃんけんゲーム開始!!\n");
}

void decition_try (void) {
    printf("何回勝負しますか。:");
    scanf("%d", &try_no);
}

/*--- じゃんけん実行 ---*/
void jyanken (void) {
    int i;

    comp = rand() % 3;

    if (init_hd == 0) {
        comp = 1;
        init_hd++;
    }

    if (all_try % 5 == 0) {
        comp = (human + 2) % 3;
    }

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
        case 0 : draw_no++; printf("引き分けです。\n");       break;
        case 1 : lose_no++; printf("あなたの負けです。\n");   break;
        case 2 : win_no++;  printf("あなたの勝ちです。\n");   break;
    }
}

/*---　再挑戦するか確認 ---*/
int confirm_retry (void) {
    int x;

    printf("もう一度しますか・・・(0)いいえ (1)はい:");
    scanf("%d", &x);

    return x;
}

char* hand_judge (int hand) {
    switch (hand) {
        case 0 : return hd[0];
        case 1 : return hd[1];
        case 2 : return hd[2];
    }
}

char* result_judge (int result) {
    switch (result) {
        case 0 : return "引き分け";
        case 1 : return "負け";
        case 2 : return "勝ち";
    }
}

int main (void) {
    int judge;
    int retry;
    int i;

    decition_try();
    initialize();

    DynamicArray *history = DynamicArray_New();

    do {
        jyanken();

        printf("私は%sで、あなたは%sです。\n", hd[comp], hd[human]);
        judge = (human - comp + 3) % 3;

        count_disp(judge);
        DynamicArray_PushBack(history, human);
        DynamicArray_PushBack(history, comp);
        DynamicArray_PushBack(history, judge);
        //disp_result(judge);
        //retry = confirm_retry();
        ++all_try;

    } while (win_no < try_no && lose_no < try_no);
    printf(win_no == try_no ? "\n□あなたの勝ちです。 \n" : "\n■私の勝ちです。\n");
    printf("%d勝%d敗%d分けでした。\n", win_no, lose_no, draw_no);

    int turn = 0;
    char* a;
    char* b;
    char* c;

    printf("\n対戦履歴\n");
    for (i=0; i<all_try; i++) {
        turn = i * 3;
        a = hand_judge(history->array[turn]);
        b = hand_judge(history->array[turn+1]);
        c = result_judge(history->array[turn+2]);

        printf("%d回戦: あなた:%s, あいて:%s, 結果:%s\n", i+1, a, b, c);
    }
    return 0;
}
