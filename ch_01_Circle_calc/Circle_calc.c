#include <stdio.h>

int main(void)//int一個整數，main為主函數，void表示無參數
{
	int r;//int一個整數，r為半徑
	float c, s;//float一個浮點數，c為圓周長，s為圓面積

	r = 5;//半徑為5
	c = 2 * 3.14159 * r;//圓周長公式為2πr
	s = 3.14159 * r * r;//圓面積公式為πr^2

	printf("r=%d,c=%.2f,s=%.2f\n", r, c, s);//輸出半徑、圓周長、圓面積，%d表示整數佔位符 %.2f表示浮點數保留兩位小數
	return 0;
}