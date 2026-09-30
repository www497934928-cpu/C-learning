/*
 * 程序名：ch_03_break_continue.c
 * 功能：break —— 跳出循环；以及它和 continue 的区别
 * 对比：break = 夺门而出（后面全不干），continue = 安检（本轮跳过，下一轮照常）
 */
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main(void)
{
    int i, sum;

    /* ===== 1. break 基本用法：累加到超过 15 就停 ===== */
    sum = 0;
    for (i = 1; i <= 10; i++) {
        sum += i;
        if (sum > 15)       // 注意是 >15，不是 >=15：sum 刚好等于 15 时不触发
            break;
    }
    printf("1) sum = %d, i = %d\n", sum, i);        // 21 6
    // 逐轮：i=1 sum=1 / i=2 sum=3 / i=3 sum=6 / i=4 sum=10 / i=5 sum=15 / i=6 sum=21 -> 触发

    /* ===== 2. break 写在前：触发那一轮，它后面的语句不执行 ===== */
    sum = 0;
    for (i = 1; i <= 8; i++) {
        if (i == 5)
            break;          // break 在 sum += 前面：i=5 这一轮直接走人
        sum += i * 2;
    }
    printf("2) A: sum = %d, i = %d\n", sum, i);     // 20 5
    // i=5 时的 10 没有被加进去，所以 sum 停在上一轮的 20

    /* ===== 3. break 写在后：触发那一轮，它前面的语句已经执行过了 ===== */
    sum = 0;
    for (i = 1; i <= 8; i++) {
        sum += i * 2;       // 先加，才判断要不要走
        if (i == 5)
            break;
    }
    printf("3) B: sum = %d, i = %d\n", sum, i);     // 30 5
    // 和第 2 段只差一个位置，sum 差了 10（就是 5*2），i 却一样
    // 结论：break 的位置不影响 i，只影响"触发那一轮的语句有没有执行完"

    /* ===== 4. break 时 i 停在哪：i++ 根本没机会执行 ===== */
    sum = 0;
    for (i = 1; i <= 10; i++) {
        if (i == 4)
            break;
        sum += i;
    }
    printf("4) sum = %d, i = %d\n", sum, i);        // 6 4
    // i 停在 4，不是 5。因为 i++ 在 for 的第三段，break 一跳，第三段就跳过了
    // 对比"正常结束"：条件是 i<=10，正常跑完的话 i 应该是 11

    /* ===== 5. break 没触发时：退化成普通的 for，i = 终点 + 1 ===== */
    sum = 0;
    for (i = 1; i <= 5; i++) {
        sum += i;
        if (sum > 1000)     // 永远不成立，break 一次都没执行
            break;
    }
    printf("5) sum = %d, i = %d\n", sum, i);        // 15 6
    // 这时候就是昨天学的规则：i = 5 + 1 = 6

    /* ===== 6. 倒序 + 步进 2 的 break ===== */
    sum = 0;
    for (i = 20; i >= 1; i -= 2) {
        if (i < 12)
            break;          // i=10 时触发，i -= 2 也被跳过，所以 i 停在 10 不是 8
        sum += i;
    }
    printf("6) sum = %d, i = %d\n", sum, i);        // 80 10
    // 加进去的是 20+18+16+14+12 = 80，i=10 的 10 没加进去

    /* ===== 7. break 的真正用途：找到就停，不用傻乎乎跑完 ===== */
    int target = 0;         // 用来记录"第一个能被 7 整除的数"
    for (i = 1; i <= 100; i++) {
        if (i % 7 == 0) {
            target = i;
            break;          // 找到了就走，1~100 后面那些不用再试
        }
    }
    printf("7) first number divisible by 7: %d, i = %d\n", target, i);   // 7 7
    // 没有 break 的话，循环会一直跑到 i=101，target 也会被改成 98（最后一个）

    /* ===== 8. break vs continue：一个走人，一个跳过本轮 ===== */
    sum = 0;
    for (i = 1; i <= 6; i++) {
        if (i == 3)
            break;          // 夺门而出：i=3 之后全不跑
        sum += i;
    }
    printf("8) break    -> sum = %d, i = %d\n", sum, i);       // 3 3
    // 1+2 = 3，i 停在 3

    sum = 0;
    for (i = 1; i <= 6; i++) {
        if (i == 3)
            continue;       // 安检没过：跳过本轮剩下的，但下一轮照常来
        sum += i;
    }
    printf("   continue -> sum = %d, i = %d\n", sum, i);       // 18 7
    // 1+2+4+5+6 = 18（3 被跳过），i 正常结束 = 7
    // 关键差别：continue 时 i++ 照常执行，所以循环能正常跑到 i=7 结束
    //           break    时 i++ 被跳过，所以 i 永远停在触发那一轮

    /* ===== 9. continue：安检没过，跳过本轮剩下的，但下一轮照常来 ===== */
    sum = 0;
    for (i = 1; i <= 6; i++) {
        if (i == 3)
            continue;       // i=3 这一轮：后面的 sum += i 不执行
        sum += i;
    }
    printf("9) sum = %d, i = %d\n", sum, i);        // 18 7
    // 1+2+4+5+6 = 18（3 被跳过），i 正常结束 = 7
    // 注意 i 是 7 不是 3：continue 时 i++ 照常执行，循环跑完了

    /* ===== 10. continue 跳过某一类值：跳过所有 3 的倍数 ===== */
    sum = 0;
    for (i = 1; i <= 10; i++) {
        if (i % 3 == 0)     // 3、6、9 会被拦下
            continue;
        sum += i;
    }
    printf("10) sum = %d, i = %d\n", sum, i);       // 37 11
    // 1+2+4+5+7+8+10 = 37

    /* ===== 11. continue 写在后面：它前面的语句已经执行过了，后面的才跳过 ===== */
    sum = 0;
    for (i = 1; i <= 6; i++) {
        sum += i;           // 这句在 continue 前面，所以每轮都执行
        if (i == 3)
            continue;
        sum += 100;         // 这句在 continue 后面，i=3 那轮被跳过
    }
    printf("11) sum = %d, i = %d\n", sum, i);       // 521 7
    // 逐轮：i=1 ->101 / i=2 ->203 / i=3 ->206(跳过+100) / i=4 ->310 / i=5 ->415 / i=6 ->521
    // 和 break 一样：位置决定"触发那一轮的语句有没有执行完"

    /* ===== 12. continue 在倒序循环里：i-- 照常执行，不会卡住 ===== */
    sum = 0;
    for (i = 5; i >= 1; i--) {
        if (i == 2)
            continue;
        sum += i;
    }
    printf("12) sum = %d, i = %d\n", sum, i);       // 13 0
    // 5+4+3+1 = 13（2 被跳过），i 正常结束 = 0

    /* ===== 13. 坑：continue 放在循环体最后，等于没写 ===== */
    sum = 0;
    for (i = 1; i <= 4; i++) {
        sum += i;
        if (i == 2)
            continue;       // 后面没有任何语句，跳过"空气"，什么也没发生
    }
    printf("13) sum = %d, i = %d\n", sum, i);       // 10 5
    // 结果跟完全不写 continue 一模一样：1+2+3+4 = 10
    // 判断方法：continue 后面如果没有语句，它就是个摆设

    return 0;
}
