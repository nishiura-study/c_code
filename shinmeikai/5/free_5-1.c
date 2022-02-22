#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define LEVEL_MIN   2
#define LEVEL_MAX   6
#define CHAR_NUM

int check_txt(int, char *, char);

int sleep (unsigned long x) {
    clock_t c1 = clock(), c2;

    do {
        if ((c2 = clock()) == (clock_t)-1)
            return 0;
    } while (1000.0 * (c2 -c1) / CLOCKS_PER_SEC < x);
    return 1;
}

int no_int(int level) {
    int num;
    int no;

    num = (int)pow(10, level);
    no = rand() % (num - (num/10)) + (num/10);

    return no;
}

char no_char(int level, char no[]) {
    int i;

    no[0] = '1' + rand() % 9;
    for (i = 1; i < level; i++) {
        no[i] = '0' + rand() % 10;
    }
    no[level] = '\0';
}

char tex_char(int level, char no[]) {
    int i;
    int uol;
    int txt_num;
    int chk;
    
    for (i = 0; i < level; i++) {
        uol = rand() % 2;
        if (uol == 0) {
            txt_num = rand() % 26 + 65;
        } else {
            txt_num = rand() % 26 + 97;
        }
        chk = check_txt(i, no, txt_num);
        
        if (chk == 0) {
            no[i] = txt_num;
        } else {
            i--;
        }
    }
    no[level] = '\0';
}

int check_txt(int i, char no[], char txt) {
    int j;
    for (j = 0; j < i; j++) {
        if (txt == no[j]) {
            return 1;
        } else {
            return 0;
        }
    }
}

int reverse_int(int no) {
    int reverse = 0;
    while (no > 0) {
        reverse = reverse * 10 + no % 10;
        no /= 10;
    }
    return reverse;
}

char reverse_char(int level, char reverse[], char no[]) {
    int i;
    for (i = 0; i < level; i++) {
        reverse[i] = no[level - 1 -i];
    }
    reverse[level] = '\0';
}

int get_int(int level, int no) {
    int pos;
    int get_num;

    pos = rand() % (level) + 1;
    printf("%d桁の数字を入力してください。\n", pos);
    get_num = (no / (int)pow(10, (level - pos))) % 10;
    //printf("check_pos_num%d, %d", no / (int)pow(10, (level - pos)), get_num);
    return get_num;
}

char get_char(int level, char no[]) {
    int pos;
    char get_num;

    pos = rand() % (level) + 1;
    printf("\n%d桁の英字を入力してください。\n", pos);
    get_num = no[pos-1];
    return get_num;
}

char get_pos(int level, char no[]) {
    int pos;
    char txt;

    pos = rand() % (level) + 1;
    txt = no[pos];
    printf("%cは何番目ですか？\n", txt);
    return pos+1;    
}

int main (void) {
    int max_stage;
    int *score;
    int i, stage;
    int level;
    int success;
    clock_t start, end;

    srand(time(NULL));
    printf("指定する桁の英字を回答してください。\n");
    
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
        #ifdef CHAR_NUM
            char no[level + 1];
            char x[2 * level];
            char reverse[level + 1];
            char keta;
            int pos;
            int pos_num;
        #else
            int no;
            int x;
            int reverse = 0;
            int keta;
        #endif

        int seikai = 0;

        printf("\n第%dステージ開始!!\n", stage + 1);
        //no = no_int(level);
        //no_char(level, no);
        tex_char(level, no);
        //reverse_char(level, reverse, no);

        printf("%s", no);
        fflush(stdout);

        sleep(300 * level);
        printf("\r%*s\r", 3 * level, "");
        fflush(stdout);

        //keta = get_int(level, no);
        //keta = get_char(level, no);
        pos = get_pos(level, no);

        //printf("%s, %d\n", no, pos);
        //printf("逆順にしてください:");
        scanf("%d", &pos_num);

        //if (strcmp(reverse, x) != 0) {
        if (pos != pos_num) {
            printf("不正解!");
        } else {
            printf("正解!");
            seikai++;
        }
        putchar('\n');

        score[stage] = seikai;
        success += seikai;
    }

    end = clock();
    
    printf("%d回中%d回成功しました。\n", max_stage, success);
    for (stage = 0; stage < max_stage; stage++) {
        printf("第%2dステージ : %d\n", stage+1, score[stage]);
    }
    printf("%.1f秒でした。\n", (double)(end - start) / CLOCKS_PER_SEC);
    free(score);
    return 0;
}
