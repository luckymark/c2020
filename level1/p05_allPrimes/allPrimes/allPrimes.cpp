//### 功能要求：
//
//1. 打印2 - 1000以内的所有素数
//2. 打印出总的计算时间
//3. 尽可能优化算法的效率

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#define SIZE 1000
int main(int argc, char* argv[])
{
	clock_t start = clock();  //开始时间(clock_t)
	clock_t end;              //结束时间(clock_t)
	double t;                 //计算所得的时间(s)
	bool* isPrime = (bool*)malloc(sizeof(bool) * (SIZE + 1));
	if (isPrime == NULL)
		exit(-1);
	else{
		/* 先全部初始化为true（从2开始）*/
		for (int i = 2; i < SIZE + 1; i++)
			isPrime[i] = true;
		/* 推算素数 */
		for (int i = 2; i < SIZE + 1; i++) {
			if (isPrime[i] == true)
				for (int j = i + i; j < SIZE + 1; j += i)
					isPrime[j] = false;
		}
		/* 计算素数所用时间 */
		end = clock();
		t = (0.0 + end - start) / CLOCKS_PER_SEC;
		printf("计算用时：%lf(s)\n", t);

		/* 打印素数 */
		for (int i = 2; i < SIZE + 1; i++) {
			if (isPrime[i] == true)
				printf("%d ", i);//如果每个数后面都是换行，将耗费大量时间
		}

	}		
	free(isPrime);
	/* 程序总时间 */
	end = clock();
	t = (0.0 + end - start) / CLOCKS_PER_SEC;
	printf("\n总用时：%lf(s)", t);
	return 0;
}