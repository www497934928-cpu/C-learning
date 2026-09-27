/*
 * 程序名：compare_two_numbers.c
 * 功能：从键盘读取两个整数（用英文逗号隔开），
 *       若格式错误或未使用英文逗号，则提示并重新输入，
 *       最后输出两个数中的较大值。
 */

#define _CRT_SECURE_NO_WARNINGS        // 关闭 VS 对 scanf 等函数的安全警告
#include <stdio.h>                    // 提供 printf / fgets / sscanf
#include <string.h>                   // 提供 strchr，用于查找字符

 /* 自定义函数：返回两个整数中的较大值 */
int Max(int a, int b)
{
    if (a > b)                        // 若 a 大于 b
        return a;                     // 返回 a
    else                              // 否则
        return b;                     // 返回 b
}

int main()
{
    int x, y;                         // 存放用户输入的两个整数
    char line[100];                   // 字符数组，存放用户整行输入
    int ok = 0;                       // 标记：是否已成功读到两个整数（0=否，1=是）

    printf("Please enter two integers separated by an English comma\n");

    /* 只要还没成功读到两个数，就一直循环 */
    while (!ok)
    {
        printf("> ");                 // 输入提示符，提示用户在此输入

        /* fgets：从键盘(stdin)读取一整行，存入 line
         * sizeof(line) 限制最多读取的字符数，防止缓冲区溢出 */
        fgets(line, sizeof(line), stdin);

        /* strchr：在 line 中查找英文逗号 ','
         * 若返回 NULL，说明没找到英文逗号 */
        if (strchr(line, ',') == NULL)
        {
            printf("Error: no English comma ',' found. Please try again!\n");
            continue;                 // 跳过本次剩余代码，回到循环开头重新输入
        }

        /* sscanf：从字符串 line 中按 "%d,%d" 格式解析两个整数
         * 返回值等于成功读到的数据个数，期望为 2 */
        if (sscanf(line, "%d,%d", &x, &y) == 2)
        {
            ok = 1;                   // 成功读到两个，设标记为 1，跳出循环
        }
        else
        {
            printf("Error: invalid format. Enter two numbers separated by an English comma (e.g. 12,13)!\n");
        }
    }

    printf("The larger value is: %d\n", Max(x, y));   // 调用 Max 并输出结果
    return 0;                         // 程序正常结束
}