/*
 * 程序名：Circle_calc_double.c
 * 功能：用 double 类型计算圆的周长和面积
 * 与第 2 章的区别：把 float 换成 double，精度更高
 */

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main(void)
{
    // 关键变化 1：float 换成 double（"双精度"，能存更多位小数）
    double r;          // 半径，用 double 声明
    double c, s;       // 周长 c、面积 s，都用 double

    // 关键变化 2：读入 double 时，scanf 里必须用 %lf（l 是字母 L 的小写，f 是 float）
    //           注意是 %lf，不是 %f，也不是 %d
    printf("Please enter the radius: ");
    scanf("%lf", &r);  // &r 取地址，和第 3 章的 sscanf 一个道理

    // 计算和原来完全一样，* 还是乘号
    c = 2 * 3.14159 * r;      // 周长 = 2πr
    s = 3.14159 * r * r;      // 面积 = πr²

    // 关键变化 3：printf 里 double 用 %.2lf（也可以写 %.2f，都能用）
    //            .2 表示保留两位小数
    printf("r=%.2lf, c=%.2lf, s=%.2lf\n", r, c, s);

    return 0;
}