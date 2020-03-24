#include <stdio.h>
int main()
{
	int age,i;
	for(i = 1;i <= 100;++i)
	{
		if(i % 12 == 0 && i % 6 == 0 && i % 7 == 0)
		{
			age = i - 4;
			printf("%d", age);
		}
	}
	return 0;
 } 
