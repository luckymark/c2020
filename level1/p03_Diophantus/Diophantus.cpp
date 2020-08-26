#include<stdio.h>

int main(void)
{
	int i;
	for(i = 1;;i++)
	if(1.0 / 6.0 * i + 1.0 / 12.0 * i + 1.0 / 7.0 * i + 5 + 1.0 / 2.0 * i + 4 == i)
	{
		printf("¶ù×ÓËÀÊ±¶ª·¬Í¼%dËê\n", i);
		return 0;
	}
}
