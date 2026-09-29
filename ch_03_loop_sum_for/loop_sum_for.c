/*
 * 程序名：ch_03_loop_sum_for.c
 * 功能：for 循环 —— 累加、求积、步进变化、平均值
 */
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
int main(void)
{
    int i, j;
    int sum = 0;        // 累加器：必须先赋 0，否则初始值是内存垃圾，，無法使用
    int acc = 1;        // 求积器：必须先赋 1（赋0的話，相乘結果恒為 0）

    /* ===== 1. for 三段式：初始化; 条件; 步进   注意：循環内只能有兩個分號，分號内可用多個表达式（用逗号隔开）===== */
    /* 初始化只在进入循环前执行 1 次；条件每轮开始前判断；步进在每轮循环体结束后执行 */
    for (i = 1; i <= 100; i++)      // 求 1~100 的和：起点 1，终点 100，所以条件是 i <= 100
        sum += i;
    printf("sum 1..100 = %d\n", sum);

    /* ===== 2. 等价的 while 写法：初始化在外面，步进放在循环体最后 ===== */
    sum = 0;                        // 复用累加器前，一定要重新归零
    i = 1;
    while (i <= 100) {
		sum += i;
        i++;                        // while 的步进要自己写，写在循环体最后
    }
    printf("while version = %d\n", sum);

    /* ===== 3. 循环结束后 i 的值：它在 i++ 变成 101 后才被条件拦下 ===== */
    for (i = 0; i < 3; i++)
        printf("i = %d\n", i);      // 打印 0 1 2
    printf("after loop i = %d\n", i);   // 打印 3，不是 2 —— 这个细节后面取下标要用

    /* ===== 4. 步进可以不是 i++：+=2 求奇偶，i-- 倒序，*=2 翻倍 ===== */
    sum = 0;
    for (i = 2; i <= 100; i += 2)   // 偶数：从 2 开始每次 +2
        sum += i;
    printf("sum of even = %d\n", sum);

    sum = 0;
    for (i = 1; i <= 100; i += 2)   // 奇数：从 1 开始每次 +2
        sum += i;
    printf("sum of odd  = %d\n", sum);

    /* ===== 5. 求积：初值必须是 1，起点必须是 1（起点写 0 会让结果恒为 0）===== */
    for (i = 1; i <= 10; i++)       // 10! = 3628800
        acc *= i;
    printf("10! = %d\n", acc);

    /* ===== 6. 平方和：C 没有平方符号，写成 x * x ===== */
    sum = 0;
    for (i = 1; i <= 10; i++)
        sum += i * i;               // 1+4+9+...+100
    printf("sum of squares = %d\n", sum);

    /* ===== 7. 平均值：整数除法会砍掉小数，必须在除之前转成 double ===== */
    printf("integer division = %d\n", sum / 10);
	printf("correct average  = %.2f\n", (double)sum / 10);   //需取得小数点后两位時，默認使用 %.2f和double。

    /* ===== 8. 多变量 for：初始化和步进都能放多个，用逗号隔开 ===== */
    for (i = 0, j = 9; i < j; i++, j--)   // 两头往中间夹：i 变大、j 变小，直到相遇
        printf("  i=%d j=%d\n", i, j);    // 打印 5 轮：0/9 1/8 2/7 3/6 4/5

     /* ===== 9. 坑：省略大括号时，只有第一句在循环里，最近的语句（分號結束算一句） ===== */
    sum = 0;
    for (i = 1; i <= 3; i++)
        sum += i;
	//例：sum += 10;   // 這句不在循環裡，僅會被單獨執行一次
    printf("only sum+=i is in the loop: sum = %d\n", sum);   // 6

    sum = 0;
    for (i = 1; i <= 3; i++) {
        sum += i;
        printf("  round %d: sum=%d\n", i, sum);              // 加大括号后，两句都在循环里
    }

    return 0;
}
