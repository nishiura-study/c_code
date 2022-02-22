#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main (void) {
    int cntn;

    srand(time(NULL));
    int num;
    char *pnt_fortune;
    
    do {
        num = rand() % 11;
        
        if (num==0)
            pnt_fortune = "大吉";
        else if (num==1)
            pnt_fortune = "中吉";
        else if (num==2 || num==3)
            pnt_fortune = "小吉";
        else if (num==4 || num==5 || num==6)
            pnt_fortune = "吉";
        else if (num==7 || num==8)
            pnt_fortune = "末吉";
        else if (num==9)
            pnt_fortune = "凶";
        else
            pnt_fortune = "大凶";

        printf("\nあなたの運勢は%sです。(num = %d) \n", pnt_fortune, num);

        printf("もう一度？・・・(0) No, (1) Yes :");
        scanf("%d", &cntn);

    } while (cntn == 1);
    
}