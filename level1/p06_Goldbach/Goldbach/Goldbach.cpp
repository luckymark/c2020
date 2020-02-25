//### 功能要求：
//1. 在100范围内验证哥德巴赫猜想的正确性

#include <stdio.h>
#define NUM 25  // 100以内25个素数，其中97在100以内验证哥德巴赫猜想无用
int main(int argc, char* argv[])
{
	// 创建一个素数数组
	int arr[] = { 2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97 };
	// 计算三个所需要的素数
	for (int i = 6; i <= 100; i += 2) 
	{
		int need_num = i - 2; 
		// 转而验证任意偶数可以分为两个素数之和
		for (int j = 0; j < NUM - 1; j++) 
		{
			for (int k = j; k < NUM - 1; k++) 
			{
				if (arr[j] + arr[k] == need_num) 
				{
					// 需要验证的数为偶数时
					printf("%d = 2 + %d + %d\n", i, arr[j], arr[k]); 
					if (i != 100) // 当 i == 100 时，防止打印验证的数为 101 的情况
					{
						// 需要验证的数为奇数时（只需把加2换成加3）
						printf("%d = 3 + %d + %d\n", i + 1, arr[j], arr[k]);
					}
					goto here; // 跳出内两层循环
				}
			}
		}
	here:;
	}
	return 0;
}