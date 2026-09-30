/*
 * 程序名：ch_04_guess_number.c
 * 游戏：电脑想一个 1~100 的数，你来猜，提示「太大」「太小」，7 次机会
 */
#define _CRT_SECURE_NO_WARNINGS      
#include <stdio.h>                   
#include <stdlib.h>              
#include <time.h>                  

int main(void)                       
{
    int secret;                    
    int guess;                      
    int count = 0;                   
    int found = 0;                 
    int max_try = 7;           
    int ch;                         
    int ret;                      

    srand((unsigned)time(NULL));     
    secret = rand() % 100 + 1;     

    printf("=== Guess the number (1-100), %d tries ===\n", max_try);
    while (count < max_try && !found) {

        printf("[%d/%d] Your guess: ", count + 1, max_try);
        ret = scanf("%d", &guess);   /* 把返回值存起来，下面判断三次 */

        if (ret == EOF) {            /* 情况一：输入没了，游戏没法继续 */
            printf("  Input closed. Game over.\n");
            break;                  
        }

        if (ret != 1) {              /* 情况二：读到了但不是整数 */
            printf("  Not a number, try again (this try is FREE)\n");

            while ((ch = getchar()) != '\n' && ch != EOF)
                ;                    
            continue;  
        }

        /* 情况三：ret == 1，输入合法，往下走 */

        count++;                     /* 走到这里说明输入合法，次数 +1 */

        /* ---- 三分支判断：小了 / 大了 / 猜中 ---- */
        if (guess < secret) {        /* 猜的比答案小 */
            printf("  Too small!\n");
        }
        else if (guess > secret) { /* 猜的比答案大 */
            printf("  Too big!\n");
        }
        else {                     /* 既不小也不大，那就是相等 */
            printf("  *** BINGO! ***\n");
            found = 1;               /* ★举旗：把「猜中了」这件事记下来 */
            break;                   
        }
    }                               

    if (found) {
        printf("You won! Answer = %d, used %d tries.\n", secret, count);
    }
    else {
        printf("You lost! Answer was %d. (used %d tries)\n", secret, count);
    }

    return 0;     
}
