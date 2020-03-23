#include<stdio.h>
#include<math.h>
int main(void)
{
	for(int i = 100;i<1000;i++)
	{ 
		int hundreds, tens, ones;
		hundreds = i / 100;
		tens = (i - hundreds * 100) / 10;
		ones = (i - hundreds * 100 - tens * 10);
		if (i == pow(hundreds, 3) + pow(tens, 3) + pow(ones, 3))
			printf("%d\n", i);
	}
	return 0;
}