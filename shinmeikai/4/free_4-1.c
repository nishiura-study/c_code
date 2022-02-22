#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define MAX_TRY (10)

int hint_num = 0;

/*--- 問題の生成 ---*/
void make4digits (int x[], int *k_num) {
    int i, j, val;

    for (i = 0; i < *k_num; i++) {
        val = rand() % 10;
        x[i] = val;
    }
    for (i = 0; i < *k_num; i++) {
        printf("%d", x[i]);
    }
}

/*--- 入力の妥当性 ---*/
int check(const char s[], int *k_num) {
    int i, j;

    if (strlen(s) != *k_num) {
        return 1;
    }

    for (i = 0; i < *k_num; i++) {
        if (!isdigit(s[i])) {
            return 2;
        }
    }
    return 0;
}

/*--- hit & blowの判定 ---*/
void judge (const char s[], const int no[], int *hit, int *blow, int *k_num) {
    int i, j;

    char s_copy[*k_num];
    int no_copy[*k_num];
    
    for (int i = 0; i < *k_num; ++i) {
        s_copy[i] = s[i];
    }

    for (int i = 0; i < *k_num; ++i) {
        no_copy[i] = no[i];
    }

    *hit = *blow = 0;
    for (i = 0; i < *k_num; i++) {
        for (j = 0; j < *k_num; j++) {
            if (s[i] == '0' + no[j]) {
                if (i == j) {
                    (*hit)++;
                    s_copy[i] = 'A';
                    no_copy[i] = -1;
                } 
            }
        }
    }
    for (i = 0; i < *k_num; i++) {
        for (j = 0; j < *k_num; j++) {
            if (s_copy[i] == s_copy[j]) {
                if (i != j) {
                    s_copy[j] = 'A';
                }
            }
        }
    }
    for (i = 0; i < *k_num; i++) {
        for (j = 0; j < *k_num; j++) {
            if (s_copy[i] == '0' + no_copy[j]) {
                (*blow)++;
            }
        }
    }
}

/*--- 結果の表示 ---*/
void print_result (int snum, int spos, int *k_num) {
    if (spos == *k_num) {
        printf("正解です!!");
    } else if (snum == 0) {
        printf("それらの数字はまったく含みません。\n");
    } else {
        printf("それらの数字中%d個の数字が含まれます。\n", snum);

        if (spos == 0) {
            printf("    ただし位置もあっている数字はありません。\n");
        } else {
            printf("    その中の%d個は位置もあっています。\n", spos);
        }
    }
    putchar('\n');
}

int hint_disp (char h[], int no[]) {
    hint_num++;
    if (h[0] == 'h') {
        if (hint_num == 1) {
            printf("初めの数字は%dです。\n\n", no[0]);
            return 1;
        } else if (hint_num == 2) {
            printf("二つ目の数字は%dです。\n\n", no[1]);
            return 1;
        } else if (hint_num > 2) {
            printf("自分でがんばれバーカ\n\n");
            return 1;
        }
    }
    return 0;
}

int main (void) {
    int try_no = 0;
    int chk;
    int hit;
    int blow;
    int no[4];
    int hint;
    int *k_num;
    char buff[10];

    clock_t start, end;

    srand(time(NULL));

    puts("■ マスターマインドをしましょう。");
    puts("■ 数字の並びを当ててください。");
    puts("■ 同じ数字が複数含まれることはありません。");
    puts("■ 4307のように連続して入力してください。");
    puts("■ スペース文字などを入力してはいけません。\n");

    printf("何桁で行いますか？:");
    scanf("%d", k_num);
    //printf("%d", *k_num);

    make4digits(no, k_num);

    start = clock();

    do {
        do {
            hint = 0;
            printf("挑戦回数%d/%d\n", try_no + 1, MAX_TRY);
            printf("入力してください(hでヒント):");
            scanf("%s", buff);

            hint = hint_disp(buff, no);
            if (hint == 1 && try_no > MAX_TRY-2) {
                break;
            } else if (hint == 1) {
                try_no++;
                continue;
            } 

            chk = check(buff, k_num);
            switch (chk) {
                case 1: printf("きちんと%d文字で入力してください。", *k_num); break;
                case 2: puts("数字以外の文字を入力しないでください。"); break;
            }
        } while (chk != 0);

        try_no++;
        judge(buff, no, &hit, &blow, k_num);
        print_result(hit + blow, hit, k_num);       
    } while (hit < *k_num && try_no < MAX_TRY);

    end = clock();
    if (try_no < MAX_TRY) {
        printf("%d回かかりました。\n所要時間は%.1f秒でした。\n", try_no, (double)(end - start) / CLOCKS_PER_SEC);
    } else {
        printf("最大挑戦回数%dを超えました。", MAX_TRY);
    }
    return 0;
}