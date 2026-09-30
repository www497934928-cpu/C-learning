/*
 * 程序名：ch_04_if_else_nested.c
 * 内容：if 的三种形态 + 两个坑 + 嵌套循环 + break 跳出多层
 */
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main(void)
{
    int i, j, sum;
    int score = 85;

    /* ---------- 1. 单 if：条件成立才做，不成立就跳过 ---------- */
    i = 10;
    if (i > 5)
        printf("1) i > 5, printed\n");
    /* 这句没有缩进 if 里，所以无条件执行 */
    printf("   always printed\n");

    /* ---------- 2. if-else：二选一，必有且只有一个执行 ---------- */
    i = 3;
    if (i % 2 == 0)
        printf("2) %d is even\n", i);
    else
        printf("2) %d is odd\n", i);

    /* ---------- 3. else-if 链：从上往下，命中第一个就停 ---------- */
    /* 条件必须从「严」到「宽」排列，写反了会被前面截胡：
       比如把 >=60 写在 >=90 前面，90 分以上的人会全被判成及格 */
    if (score >= 90)
        printf("3) %d -> A\n", score);
    else if (score >= 80)
        printf("3) %d -> B\n", score);   /* 85 命中这里，后面不再看 */
    else if (score >= 70)
        printf("3) %d -> C\n", score);
    else
        printf("3) %d -> D\n", score);   /* else 不带条件，兜住「以上皆非」 */

    /* 这句证明：命中后只是跳出 if 链，不是结束程序 */
    printf("   chain done\n");

    /* ---------- 4. 坑一：else 就近配对 ---------- */
    /* 下面两段除了 i、j 的值完全一样，用来证明 else 到底跟谁 */
    i = 1; j = 1;
    if (i > 0)
        if (j > 0)
            printf("4) both positive\n");
        else
            printf("4) ???\n");          /* 没打印：j>0 成立，走不到这里 */

    /* 关键这组：i>0 是「成立」的 */
    i = 1; j = -1;
    if (i > 0)
        if (j > 0)
            printf("   inner\n");
        else
            printf("4) inner else taken (i=%d j=%d)\n", i, j);
    /* 它打印了 —— 如果 else 真跟外层，外层条件成立时 else 根本不该执行。
       所以 else 跟的是内层 if (j > 0)。
       gcc 会给这个警告：-Wdangling-else（悬空 else） */

       /* 根治：加大括号，归属就写死，缩排骗不了人 */
    i = 1; j = -1;
    if (i > 0) {
        if (j > 0) {
            printf("   both\n");
        }
    }
    else {                            /* 现在它真的属于外层了 */
        printf("4) outer else\n");
    }
    printf("4) braces fix it\n");

    /* ---------- 5. 坑二：= 是赋值，== 才是比较 ---------- */
    i = 0;
    if (i = 5)                          /* 危险：先把 5 塞进 i，再判断 i 的真假 */
        printf("5) entered, i becomes %d\n", i);   /* 非零即真，永远进来 */
    /* 副作用是 i 被改成 5，这就是 bug 的来源。
       gcc 警告：-Wparentheses */

    i = 0;
    if (i == 5)                         /* 正确写法 */
        printf("   i is 5\n");
    else
        printf("5) i == 5 false, i still %d\n", i);

    /* ---------- 6. 嵌套循环：外层走 1 步，内层转一整圈 ---------- */
    printf("6) nested:\n");
    for (i = 1; i <= 3; i++) {
        for (j = 1; j <= 2; j++) {      /* 外层每加 1，内层跑完 2 次 */
            printf("   i=%d j=%d\n", i, j);
        }
    }
    /* 共 3 x 2 = 6 次。口诀：外层慢、内层快，像时针和分针 */

    /* ---------- 7. break 只跳出它所在的那一层 ---------- */
    printf("7) break inner only:\n");
    for (i = 1; i <= 3; i++) {
        for (j = 1; j <= 3; j++) {
            if (j == 2)
                break;                  /* 只跳出 for(j) */
            printf("   i=%d j=%d\n", i, j);
        }
        /* 回到这里，外层继续下一轮 i */
    }
    /* 内层每次只打印 j=1，但 i 照样跑完 1、2、3 */

    /* ---------- 8. 想一次跳出多层：用 flag 当停止信号 ---------- */
    {
        int flag = 0;                   /* 0 = 继续，1 = 停 */
        int hit_i = 0, hit_j = 0;

        /* 外层条件加 !flag：内层置位后，外层下一轮判断就退出 */
        for (i = 1; i <= 5 && !flag; i++) {
            for (j = 1; j <= 5; j++) {
                if (i * j == 6) {
                    flag = 1;
                    hit_i = i;
                    hit_j = j;
                    break;              /* 先跳内层 */
                }
            }
        }
        printf("8) i*j==6 at i=%d j=%d, flag=%d\n", hit_i, hit_j, flag);
        /* i=2 j=3 命中，外层不再跑 3、4、5。
           套路和第 4 章 compare_two_numbers.c 里的 ok 标记一样 */
    }

    /* ---------- 9. 综合：嵌套 + continue ---------- */
    sum = 0;
    for (i = 1; i <= 3; i++) {
        for (j = 1; j <= 3; j++) {
            if (j == 2)
                continue;               /* 跳过本轮，但 j++ 照常执行 */
            sum += i * j;
        }
    }
    printf("9) sum=%d i=%d j=%d\n", sum, i, j);   /* 24 4 4 */
    /* i、j 都是「正常结束」的值（终点+1），因为 continue 不跳过 j++ */

    return 0;
}
