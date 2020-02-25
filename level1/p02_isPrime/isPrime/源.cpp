#include <stdio.h>
#include <math.h>

int main()
{
	double number = 0;
	int s = 0;
	printf("请输入一个数字：");
	int u = scanf_s("%lf", &number); //number是不是一个数字
	int a = (int)number;             //number是不是整数
	if (u == 1 && a == number && a > 0) {
		if (a == 1)
			printf("1不是素数\n");
		else {
			int i = 2;
			s = (int)sqrt((double)a);
			for (i = 2; i <= s && a % i != 0; i++);
			if (i > s)
				printf("%d是素数\n", a);
			else
				printf("%d不是素数\n", a);
		}

	}
	else
		printf("请输入正确的值！\n");
	return 0;
}
