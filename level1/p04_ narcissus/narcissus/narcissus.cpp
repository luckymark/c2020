//### 功能要求：
//
//1. 打印出所有3位水仙花数
//
//水仙花数：n位数的每个数位的n次方之和等于该n位数本身
//
//例如：153 = 1 ^ 3 + 5 ^ 3 + 3 ^ 3
#include <stdio.h>

int main(int argc, char* argv[])
{
	for (int i = 100; i < 1000; i++)
	{
		int bai = i / 100;
		int shi = i % 100 / 10;
		int ge = i % 10;
		if (bai * bai * bai + shi * shi * shi + ge * ge * ge == i)
			printf("%d\n", i);
	}
	return 0;
}