#include <stdio.h>
#include <time.h>
clock_t start,finish;
double Total_time;
int main()
{
	int i;
	int j;
	start=clock();
	int num=0;
	printf("2 ");
	for(i=2;i<=1000;++i)
	{
		num=0; 
		if(i%2==0)
		{
			continue;
		}
		else
		{
			for(j=2;j<i/2;++j)
			{
				if(i%j==0)
					{
						num++;
						break;
						
					}
			}
		}
		if(num==0)
		{
			printf("%d ",i);
		}
	}
	finish=clock();
	Total_time = (double)(finish - start) / CLOCKS_PER_SEC;
	printf("\n %lfºÁÃë",Total_time);
	return 0;
 } 
