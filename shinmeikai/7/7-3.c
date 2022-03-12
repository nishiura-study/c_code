#include <conio.h>
#include <ctype.h>
#include <stdio.h>

int main(void) {
    int ch;
    int retry;

    do {
        printf("キーを入力してください。");
        ch = getch();

        printf("\n押されたキーは%cで値は%dです。\n", isprint(ch) ? ch : ' ', ch);

        printf("もう一度？ (Y/N) :");
        retry = getch();
        if (isprint(retry))
            putch(retry);
        putchar('\n');
    } while (retry == 'Y' || retry == 'y');

    return 0;
}