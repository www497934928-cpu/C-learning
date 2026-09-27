/*
 * 文件名：increment_and_compound.c
 * 功能：学习自增自减 ++ -- 与复合赋值 += -= *= /= %=
 * 学习方法：先自己在纸上算一遍结果，再编译运行核对
 */

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

int main(void)
{
    /* ========== 第一部分：复合赋值 += -= *= /= %= ========== */
    /*
     * 规律：运算符放左边，只写一个等号 =
     *   sum += i;  等价于  sum = sum + i;
     *   x   *= 2;  等价于  x = x * 2;
     */

    int sum = 0;
    sum += 3;     // sum = sum + 3;   现在 sum 是 3
    sum *= 2;     // sum = sum * 2;   现在 sum 是 6
    sum -= 1;     // sum = sum - 1;   现在 sum 是 5
    sum /= 2;     // sum = sum / 2;   现在 sum 是 2（整数除法，直接砍掉小数）
    sum %= 2;     // sum = sum % 2;   现在 sum 是 0（% 是取余，只用于整数）

    printf("=== Part 1: compound assignment ===\n");
    printf("sum = %d\n\n", sum);   // 预期输出：sum = 0


    /* ========== 第二部分：自增 ++ 与自减 -- 的基础 ========== */
    /*
     * ++ 就是 +1 的简写，-- 就是 -1 的简写
     * 单独成行时（i++;），前++ 和 后++ 完全没区别
     */

    int a = 5;
    a++;         // 等价于 a = a + 1;   a 变成 6
    int b = 5;
    ++b;         // 和上一条效果一样   b 也变成 6
    int c = 5;
    c--;         // 等价于 c = c - 1;   c 变成 4

    printf("=== Part 2: ++ and -- (standalone) ===\n");
    printf("a = %d, b = %d, c = %d\n\n", a, b, c);


    /* ========== 第三部分：前++ 与 后++ 的区别（重点）========== */
    /*
     * i++  ：先用后加。先把 i 的当前值拿去用，用完再加 1
     * ++i  ：先加后用。先把 i 加 1，再用新值
     */

    int i = 5;
    int x = i++;     // 先把 i(5) 赋给 x，然后 i 变成 6
    // 结果：x = 5, i = 6

    int j = 5;
    int y = ++j;     // 先把 j 变成 6，再把 6 赋给 y
    // 结果：y = 6, j = 6

    printf("=== Part 3: i++ vs ++i ===\n");
    printf("x = %d, i = %d\n", x, i);   // 预期：x = 5, i = 6
    printf("y = %d, j = %d\n\n", y, j); // 预期：y = 6, j = 6

    /*
     * 警告：不要在一个表达式里又用又改同一个变量，比如 i++ + ++i
     * 那种写法纯属故意考人，正常代码绝不这么写
     */


     /* ========== 第四部分：自减 -- 的前后用（和上面对称）========== */

    int m = 5;
    int p = m--;     // 先把 m(5) 赋给 p，然后 m 变成 4
    // 结果：p = 5, m = 4

    int n = 5;
    int q = --n;     // 先把 n 变成 4，再把 4 赋给 q
    // 结果：q = 4, n = 4

    printf("=== Part 4: m-- vs --m ===\n");
    printf("p = %d, m = %d\n", p, m);   // 预期：p = 5, m = 4
    printf("q = %d, n = %d\n\n", q, n); // 预期：q = 4, n = 4

    return 0;
}
